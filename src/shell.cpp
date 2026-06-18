#include "shell.h"

#include <fcntl.h>
#include <cstdio>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

#include <iostream>

#include "cxxopts.hpp"
#include "fmt/color.h"
#include "fmt/format.h"

#include "common.hpp"
#include "feature/string_parser.h"

extern char** environ;

Shell::Shell() {
    vars.set_exported("SYSTEM", sys).set_exported("SHELL", "yush");

    for (char** current{environ}; *current; current++) {
        std::string current_str(*current);
        auto delimiter{current_str.find('=')};
        std::string key(current_str.substr(0, delimiter));
        std::string value(delimiter != std::string::npos ? current_str.substr(delimiter + 1) : "");
        vars.set_exported(key, value);
    }

    if (vars.get("HOME").empty()) {
        fmt::print(stderr, "Error: HOME is not set\n");
        exit(1);
    }

    if (!(std::filesystem::exists(vars.get("HOME")/this->config_dir) &&
          std::filesystem::is_directory(vars.get("HOME")/this->config_dir))) {
        fmt::print(stderr, "Error: yush config dir path is not exists\n");
        fmt::print(stdout, "Auto creating config dir\n");
        std::filesystem::create_directories(vars.get("HOME")/config_dir);
    }

    if (std::filesystem::exists(vars.get("HOME")/this->rc_file)) {
        this->run(vars.get("HOME")/this->rc_file);
    }

    this->history.check_file(vars.get("HOME"));
    this->history.load_file();
}

int Shell::run(cxxopts::ParseResult& result) {
    if (signal(SIGINT, SIG_IGN) == SIG_ERR) {
        fmt::print(stderr, "Error: signal handler failed\n");
        return 1;
    }

    do {
        std::string line;
        if (result["interactive"].as<bool>()) {
            this->reap_jobs();
            this->output();
            line = this->read();
        }

        // Keep reading lines until the statement is complete (e.g. a multi-line
        // `if` block or an unterminated quote).
        while (!std::cin.eof() && !this->read_cancelled && !statement_complete(line)) {
            line += "\n" + this->read();
        }

        // Ctrl-C discards the whole (possibly multi-line) input.
        if (this->read_cancelled) {
            continue;
        }

        runtime_status = exec_statement(line);
        if (!line.empty()) {
            this->history.add(line);
        }
        if (this->exiting) {
            break;
        }
    } while (!std::cin.eof());

    this->history.write_file();
    return this->exiting ? this->exit_code : runtime_status;
}

int Shell::run(const std::filesystem::path& file) {
    std::vector<Command> commands{read_script(file)};
    std::string statement;
    for (auto& command : commands) {
        statement = statement.empty() ? command.get() : statement + "\n" + command.get();
        if (!statement_complete(statement)) {
            continue;
        }
        runtime_status = exec_statement(statement);
        statement.clear();
        if (this->exiting) {
            break;
        }
    }
    if (!statement.empty() && !this->exiting) {
        runtime_status = exec_statement(statement);
    }

    return this->exiting ? this->exit_code : runtime_status;
}

std::vector<Command> Shell::read_script(const std::filesystem::path& file) {
    if (!std::filesystem::exists(file)) {
        fmt::print(stderr, "Error: script file `{}` not found\n", file.string());
        return {};
    }

    std::vector<Command> commands;
    std::ifstream fin(file);
    while (!fin.eof()) {
        commands.push_back(Command(this->read(fin)));
    }

    fin.close();
    return commands;
}

int Shell::output() {
    using namespace std::filesystem;
    fmt::print(fg(fmt::color::orange), "{}", vars.get("USER"));
    fmt::print("@");
    fmt::print(fg(fmt::color::cyan), "{} ", vars.get("NAME"));
    if (current_path().string().find(vars.get("HOME")) == 0) {
        fmt::print(fg(fmt::color::violet), "~{}\n", current_path().string().substr(vars.get("HOME").length()));
    } else {
        fmt::print(fg(fmt::color::violet), "{}\n", current_path().string());
    }

    if (runtime_status != 0) {
        fmt::print(fg(fmt::color::red), "{} > ", runtime_status);
        return runtime_status;
    }

    fmt::print("> ");
    return 0;
}

std::string Shell::read() {
    termios old_termios, new_termios;
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    std::string input;
    int current;
    std::size_t cursor_index{0};
    std::size_t history_index{static_cast<std::size_t>(this->history.size())};
    this->read_cancelled = false;
    while (true) {
        current = std::cin.get();
        if (current == EOF /* Ctrl-D / end of input */) {
            fmt::print("\n");
            break;
        }
        if (current == 3 /* Ctrl-C */) {
            fmt::print("^C\n");
            input.clear();
            this->read_cancelled = true;
            break;
        }
        if (current == 27 /* ESC */) {
            int key1{std::cin.get()};
            int key2{std::cin.get()};
            if (key1 != '[') continue;
            switch (key2) {
            case 'A': // Arrow up.
                if (history_index == 0) break;
                for (std::size_t i{cursor_index}; i < input.size(); i++) {
                    fmt::print("\033[C");
                }
                for (std::size_t i{0}; i < input.size(); i++) {
                    fmt::print("\b \b");
                }
                input = this->history.get(--history_index);
                cursor_index = input.size();
                fmt::print("{}", input);
                break;
            case 'B': // Arrow down.
                if (history_index == this->history.size()) break;
                for (std::size_t i{cursor_index}; i < input.size(); i++) {
                    fmt::print("\033[C");
                }
                for (std::size_t i{0}; i < input.size(); i++) {
                    fmt::print("\b \b");
                }
                if (++history_index == this->history.size()) {
                    input.clear();
                } else {
                    input = this->history.get(history_index);
                }
                cursor_index = input.size();
                fmt::print("{}", input);
                break;
            case 'C': // Arrow right.
                if (cursor_index == input.size()) break;
                fmt::print("\033[C");
                cursor_index++;
                break;
            case 'D': // Arrow left.
                if (cursor_index == 0) break;
                fmt::print("\033[D");
                cursor_index--;
                break;
            default:
                break;
            }
        } else if (current == 8 /* BS */ || current == 127 /* DEL */) {
            if (cursor_index == 0) continue;
            input.erase(--cursor_index, 1);
            fmt::print("\b{} ", input.substr(cursor_index));
            for (std::size_t i{cursor_index}; i < input.size() + 1; i++) {
                fmt::print("\033[D");
            }
        } else if (current == 10 /* LF */) {
            fmt::print("\n");
            break;
        } else {
            input.insert(cursor_index, 1, static_cast<char>(current));
            fmt::print("{}", input.substr(cursor_index++));
            for (std::size_t i{cursor_index}; i < input.size(); i++) {
                fmt::print("\033[D");
            }
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
    return input;
}

std::string Shell::read(std::istream& input_stream) {
    std::string input;
    if(!std::getline(input_stream, input)) return {};
    if (!input.empty() && input.back() == '\\') {
        input.pop_back();
        input += read(input_stream);
    }
    return input;
}

void Shell::reap_jobs() {
    int st{0};
    pid_t pid{0};
    while ((pid = waitpid(-1, &st, WNOHANG)) > 0) {
        for (auto it{this->jobs.begin()}; it != this->jobs.end(); ++it) {
            if (it->second == pid) {
                fmt::print("[{}]+ Done\t{}\n", it->first, static_cast<int>(pid));
                this->jobs.erase(it);
                break;
            }
        }
    }
}

int Shell::exec_cmd(const Command& cmd) {
    int status{0};

    if (cmd.arg().empty()) {
        return status;
    }

    if (functions.exist(cmd.arg()[0])) {
        for (const auto& cmd_str : string_parser(functions.get(cmd.arg()[0]), '\n')) {
            Command command(cmd_str);
            status = exec_cmd(command);
        }
        return status;
    }

    status = exec_shell_builtin(cmd);
    if (status != 127) {
        return status;
    }

    return exec_file(cmd);
}

namespace {

enum class Connector { Seq, And, Or };

struct Segment {
    std::string text;
    Connector conn;          // connector that precedes this segment
    bool background{false};  // segment is followed by `&` (run asynchronously)
};

// Split a line into segments at top-level `;`, `&&`, `||` and `&`, honoring
// single/double quotes and backslash escapes so separators inside quotes are
// left untouched. Empty segments (e.g. from a trailing `;`) are dropped.
std::vector<Segment> split_line(const std::string& line) {
    std::vector<Segment> segments;
    std::string cur;
    Connector pending{Connector::Seq};
    bool in_single{false};
    bool in_double{false};

    auto flush = [&](bool background) {
        std::size_t start{cur.find_first_not_of(" \t")};
        if (start != std::string::npos) {
            std::size_t end{cur.find_last_not_of(" \t")};
            segments.push_back({cur.substr(start, end - start + 1), pending, background});
        }
        cur.clear();
    };

    for (std::size_t i{0}; i < line.size(); ++i) {
        char c{line[i]};

        if (c == '\\' && !in_single && i + 1 < line.size()) {
            cur += c;
            cur += line[++i];
            continue;
        }
        if (c == '\'' && !in_double) {
            in_single = !in_single;
            cur += c;
            continue;
        }
        if (c == '"' && !in_single) {
            in_double = !in_double;
            cur += c;
            continue;
        }

        if (!in_single && !in_double) {
            if (c == ';') {
                flush(false);
                pending = Connector::Seq;
                continue;
            }
            if (c == '&' && i + 1 < line.size() && line[i + 1] == '&') {
                flush(false);
                pending = Connector::And;
                ++i;
                continue;
            }
            if (c == '&') {  // single `&`: run the preceding command in background
                flush(true);
                pending = Connector::Seq;
                continue;
            }
            if (c == '|' && i + 1 < line.size() && line[i + 1] == '|') {
                flush(false);
                pending = Connector::Or;
                ++i;
                continue;
            }
        }

        cur += c;
    }
    flush(false);

    return segments;
}

}  // namespace

int Shell::exec_line(const std::string& line) {
    int status{runtime_status};

    for (const auto& segment : split_line(line)) {
        if (segment.conn == Connector::And && status != 0) {
            continue;
        }
        if (segment.conn == Connector::Or && status == 0) {
            continue;
        }

        Command probe(segment.text);
        probe.parse();
        if (probe.arg().empty()) {
            continue;
        }

        if (probe.arg()[0] == "exit") {
            this->exiting = true;
            this->exit_code =
                probe.arg().size() > 1 ? atoi(probe.arg()[1].c_str()) : status;
            return this->exit_code;
        }

        if (segment.background) {
            fflush(stdout);
            pid_t pid{fork()};
            if (pid == 0) {
                signal(SIGINT, SIG_IGN);  // background jobs are not killed by Ctrl-C
                int st{exec_pipeline(segment.text)};
                fflush(stdout);
                _exit(st & 0xff);
            }
            if (pid > 0) {
                this->jobs.push_back({++this->job_count, pid});
                fmt::print("[{}] {}\n", this->job_count, static_cast<int>(pid));
            }
            status = 0;
            continue;
        }

        status = exec_pipeline(segment.text);
    }

    return status;
}

namespace {

std::string trim(const std::string& s) {
    std::size_t a{s.find_first_not_of(" \t")};
    if (a == std::string::npos) {
        return {};
    }
    std::size_t b{s.find_last_not_of(" \t")};
    return s.substr(a, b - a + 1);
}

std::string first_word(const std::string& s) {
    std::string t{trim(s)};
    std::size_t sp{t.find_first_of(" \t")};
    return sp == std::string::npos ? t : t.substr(0, sp);
}

// The text after the first whitespace-delimited word (e.g. drop a leading
// `then`/`else`/`if` keyword), trimmed.
std::string rest_after_first_word(const std::string& s) {
    std::string t{trim(s)};
    std::size_t sp{t.find_first_of(" \t")};
    return sp == std::string::npos ? std::string{} : trim(t.substr(sp));
}

bool quotes_balanced(const std::string& text) {
    bool in_single{false};
    bool in_double{false};
    for (std::size_t i{0}; i < text.size(); ++i) {
        char c{text[i]};
        if (c == '\\' && !in_single && i + 1 < text.size()) {
            ++i;
        } else if (c == '\'' && !in_double) {
            in_single = !in_single;
        } else if (c == '"' && !in_single) {
            in_double = !in_double;
        }
    }
    return !in_single && !in_double;
}

// Split a statement into clauses at top-level `;` and newlines (quote-aware),
// dropping empty pieces. Connectors `&&`/`||`/`|` are left inside the clauses
// so exec_line can handle them.
std::vector<std::string> split_statements(const std::string& text) {
    std::vector<std::string> out;
    std::string cur;
    bool in_single{false};
    bool in_double{false};

    for (std::size_t i{0}; i < text.size(); ++i) {
        char c{text[i]};
        if (c == '\\' && !in_single && i + 1 < text.size()) {
            cur += c;
            cur += text[++i];
            continue;
        }
        if (c == '\'' && !in_double) {
            in_single = !in_single;
        } else if (c == '"' && !in_single) {
            in_double = !in_double;
        } else if ((c == ';' || c == '\n') && !in_single && !in_double) {
            std::string t{trim(cur)};
            if (!t.empty()) {
                out.push_back(t);
            }
            cur.clear();
            continue;
        }
        cur += c;
    }
    std::string t{trim(cur)};
    if (!t.empty()) {
        out.push_back(t);
    }
    return out;
}

}  // namespace

bool Shell::statement_complete(const std::string& text) {
    if (!quotes_balanced(text)) {
        return false;
    }
    int depth{0};
    for (const auto& clause : split_statements(text)) {
        std::string word{first_word(clause)};
        if (word == "if") {
            ++depth;
        } else if (word == "fi" && depth > 0) {
            --depth;
        }
    }
    return depth <= 0;
}

int Shell::exec_statement(const std::string& text) {
    if (first_word(text) == "if") {
        return exec_if(text);
    }
    return exec_line(text);
}

int Shell::exec_if(const std::string& text) {
    std::vector<std::string> clauses{split_statements(text)};
    std::size_t idx{0};

    // Run a list of clauses, returning the status of the last one. Stops early
    // if a clause requests shell exit.
    auto run_clauses = [&](const std::vector<std::string>& list) {
        int status{0};
        for (const auto& clause : list) {
            status = exec_line(clause);
            if (this->exiting) {
                break;
            }
        }
        return status;
    };

    while (idx < clauses.size()) {
        std::string keyword{first_word(clauses[idx])};
        if (keyword != "if" && keyword != "elif") {
            fmt::print(stderr, "if: syntax error near `{}`\n", clauses[idx]);
            return 2;
        }

        // Condition: the remainder of this clause plus clauses up to `then`.
        std::vector<std::string> condition;
        std::string head{rest_after_first_word(clauses[idx])};
        if (!head.empty()) {
            condition.push_back(head);
        }
        ++idx;
        while (idx < clauses.size() && first_word(clauses[idx]) != "then") {
            condition.push_back(clauses[idx]);
            ++idx;
        }
        if (idx >= clauses.size()) {
            fmt::print(stderr, "if: missing `then`\n");
            return 2;
        }

        // Body: the remainder after `then` plus clauses up to elif/else/fi.
        std::vector<std::string> body;
        std::string body_head{rest_after_first_word(clauses[idx])};
        if (!body_head.empty()) {
            body.push_back(body_head);
        }
        ++idx;
        while (idx < clauses.size() && first_word(clauses[idx]) != "elif" &&
               first_word(clauses[idx]) != "else" && first_word(clauses[idx]) != "fi") {
            body.push_back(clauses[idx]);
            ++idx;
        }
        if (idx >= clauses.size()) {
            fmt::print(stderr, "if: missing `fi`\n");
            return 2;
        }

        int condition_status{run_clauses(condition)};
        if (this->exiting) {
            return this->exit_code;
        }
        if (condition_status == 0) {
            return run_clauses(body);
        }

        std::string terminator{first_word(clauses[idx])};
        if (terminator == "elif") {
            continue;  // re-enter the loop treating this clause as a new test
        }
        if (terminator == "else") {
            std::vector<std::string> else_body;
            std::string else_head{rest_after_first_word(clauses[idx])};
            if (!else_head.empty()) {
                else_body.push_back(else_head);
            }
            ++idx;
            while (idx < clauses.size() && first_word(clauses[idx]) != "fi") {
                else_body.push_back(clauses[idx]);
                ++idx;
            }
            if (idx >= clauses.size()) {
                fmt::print(stderr, "if: missing `fi`\n");
                return 2;
            }
            return run_clauses(else_body);
        }
        // terminator == "fi": no branch taken.
        return 0;
    }

    return 0;
}

namespace {

struct Redir {
    enum class Type { In, Out, Append } type;
    std::string target;
};

// Quote-aware split of a pipeline segment into its commands at top-level `|`.
std::vector<std::string> split_pipe(const std::string& segment) {
    std::vector<std::string> parts;
    std::string cur;
    bool in_single{false};
    bool in_double{false};

    for (std::size_t i{0}; i < segment.size(); ++i) {
        char c{segment[i]};
        if (c == '\\' && !in_single && i + 1 < segment.size()) {
            cur += c;
            cur += segment[++i];
            continue;
        }
        if (c == '\'' && !in_double) {
            in_single = !in_single;
        } else if (c == '"' && !in_single) {
            in_double = !in_double;
        } else if (c == '|' && !in_single && !in_double) {
            parts.push_back(cur);
            cur.clear();
            continue;
        }
        cur += c;
    }
    parts.push_back(cur);
    return parts;
}

// Pull `<`, `>` and `>>` redirections (attached or space-separated) out of a
// command, returning the command text with them removed. Targets are expanded
// through the normal parser so variables and quotes are honored.
std::string extract_redirs(const std::string& text, std::vector<Redir>& redirs) {
    std::string cleaned;
    bool in_single{false};
    bool in_double{false};
    const std::size_t n{text.size()};

    auto read_target = [&](std::size_t& i) -> std::string {
        while (i < n && (text[i] == ' ' || text[i] == '\t')) {
            ++i;
        }
        std::string raw;
        bool s{false};
        bool d{false};
        while (i < n) {
            char c{text[i]};
            if (!s && !d && (c == ' ' || c == '\t' || c == '<' || c == '>' || c == '|')) {
                break;
            }
            if (c == '\'' && !d) {
                s = !s;
            } else if (c == '"' && !s) {
                d = !d;
            }
            raw += c;
            ++i;
        }
        Command t(raw);
        t.parse();
        return t.arg().empty() ? std::string{} : t.arg()[0];
    };

    for (std::size_t i{0}; i < n;) {
        char c{text[i]};
        if (c == '\\' && !in_single && i + 1 < n) {
            cleaned += c;
            cleaned += text[i + 1];
            i += 2;
            continue;
        }
        if (c == '\'' && !in_double) {
            in_single = !in_single;
            cleaned += c;
            ++i;
            continue;
        }
        if (c == '"' && !in_single) {
            in_double = !in_double;
            cleaned += c;
            ++i;
            continue;
        }

        if (!in_single && !in_double && c == '<') {
            ++i;
            redirs.push_back({Redir::Type::In, read_target(i)});
            cleaned += ' ';
            continue;
        }
        if (!in_single && !in_double && c == '>') {
            ++i;
            Redir::Type type{Redir::Type::Out};
            if (i < n && text[i] == '>') {
                type = Redir::Type::Append;
                ++i;
            }
            redirs.push_back({type, read_target(i)});
            cleaned += ' ';
            continue;
        }

        cleaned += c;
        ++i;
    }

    return cleaned;
}

// Open each redirection target and dup2 it onto the right fd. Returns 0 on
// success, -1 (after printing an error) on the first failure.
int apply_redirs(const std::vector<Redir>& redirs) {
    for (const auto& r : redirs) {
        int fd{-1};
        int target_fd{r.type == Redir::Type::In ? 0 : 1};
        switch (r.type) {
        case Redir::Type::In:
            fd = open(r.target.c_str(), O_RDONLY);
            break;
        case Redir::Type::Out:
            fd = open(r.target.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            break;
        case Redir::Type::Append:
            fd = open(r.target.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
            break;
        }
        if (fd < 0) {
            fmt::print(stderr, "yush: {}: cannot open\n", r.target);
            return -1;
        }
        dup2(fd, target_fd);
        close(fd);
    }
    return 0;
}

}  // namespace

int Shell::exec_simple(const std::string& text) {
    std::vector<Redir> redirs;
    std::string cleaned{extract_redirs(text, redirs)};

    Command cmd(cleaned);
    cmd.parse();

    if (redirs.empty()) {
        return exec_cmd(cmd);
    }

    int saved_in{dup(0)};
    int saved_out{dup(1)};
    int status{1};
    if (apply_redirs(redirs) == 0) {
        status = exec_cmd(cmd);
    }
    fflush(stdout);  // flush builtin output to the redirected fd before restoring
    dup2(saved_in, 0);
    dup2(saved_out, 1);
    close(saved_in);
    close(saved_out);
    return status;
}

int Shell::exec_pipeline(const std::string& segment) {
    std::vector<std::string> commands{split_pipe(segment)};
    if (commands.size() == 1) {
        return exec_simple(commands[0]);
    }

    fflush(stdout);  // keep parent's buffered output ahead of child output

    const std::size_t n{commands.size()};
    int prev_read{-1};
    std::vector<pid_t> pids;

    for (std::size_t i{0}; i < n; ++i) {
        int pipefd[2]{-1, -1};
        if (i + 1 < n && pipe(pipefd) == -1) {
            fmt::print(stderr, "yush: pipe failed\n");
            break;
        }

        pid_t pid{fork()};
        if (pid == -1) {
            fmt::print(stderr, "yush: fork failed\n");
            break;
        }

        if (pid == 0) {
            if (prev_read != -1) {
                dup2(prev_read, 0);
                close(prev_read);
            }
            if (i + 1 < n) {
                dup2(pipefd[1], 1);
                close(pipefd[0]);
                close(pipefd[1]);
            }

            std::vector<Redir> redirs;
            std::string cleaned{extract_redirs(commands[i], redirs)};
            if (apply_redirs(redirs) != 0) {
                _exit(1);
            }
            Command cmd(cleaned);
            cmd.parse();
            signal(SIGINT, SIG_DFL);
            int st{exec_cmd(cmd)};
            fflush(stdout);  // _exit does not flush stdio buffers
            _exit(st & 0xff);
        }

        if (prev_read != -1) {
            close(prev_read);
        }
        if (i + 1 < n) {
            close(pipefd[1]);
            prev_read = pipefd[0];
        }
        pids.push_back(pid);
    }

    if (prev_read != -1) {
        close(prev_read);
    }

    int status{0};
    for (std::size_t i{0}; i < pids.size(); ++i) {
        int st{0};
        waitpid(pids[i], &st, 0);
        if (i + 1 == pids.size()) {
            if (WIFEXITED(st)) {
                status = WEXITSTATUS(st);
            } else if (WIFSIGNALED(st)) {
                status = 128 + WTERMSIG(st);
            }
        }
    }
    return status;
}

int Shell::exec_file(const Command& cmd) {
    std::unique_ptr<char*[]> argv = std::make_unique<char*[]>(cmd.arg().size() + 1);
    for (size_t i{0}; i < cmd.arg().size(); i++) {
        argv[i] = const_cast<char*>(cmd.arg()[i].c_str());
    }

    std::string file_path_str;
    if (std::filesystem::exists(cmd.arg()[0]) && std::filesystem::is_regular_file(cmd.arg()[0])) {
        file_path_str = cmd.arg()[0];
    } else {
        std::vector<std::string> paths = string_parser(this->vars.get("PATH"), ':');
        for (const auto& path : paths) {
            std::filesystem::path file_path = path / std::filesystem::path(cmd.arg()[0]);
            if (std::filesystem::exists(file_path) && std::filesystem::is_regular_file(file_path)) {
                file_path_str = file_path.lexically_normal().string();
                break;
            }
        }
    }
    if (file_path_str.empty()) {
        return 127;
    }

    std::vector<std::string> env_strings{this->vars.environment()};
    std::unique_ptr<char*[]> envp = std::make_unique<char*[]>(env_strings.size() + 1);
    for (size_t i{0}; i < env_strings.size(); i++) {
        envp[i] = const_cast<char*>(env_strings[i].c_str());
    }

    fflush(stdout);  // keep buffered builtin output ahead of the child's output

    pid_t pid{fork()};
    if (pid == -1) {
        return -1;
    }
    if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
        if (WIFSIGNALED(status)) {
            return 128 + WTERMSIG(status);
        }
        return -1;
    }
    signal(SIGINT, SIG_DFL);
    execve(file_path_str.c_str(), argv.get(), envp.get());
    unreachable();
}

int Shell::exec_shell_builtin(const Command& cmd) {
    using CommandType = int (Shell::*)(const std::vector<std::string>&);

    static const std::unordered_map<std::string, CommandType> command_map{
        {"alias", &Shell::cmd_alias},   {"cd", &Shell::cmd_cd},
        {"echo", &Shell::cmd_echo},     {"export", &Shell::cmd_export},
        {"function", &Shell::cmd_function}, {"ls", &Shell::cmd_ls},
        {"pwd", &Shell::cmd_pwd},       {"set", &Shell::cmd_set},
    };

    auto command_it{command_map.find(cmd.arg()[0])};
    if (command_it != command_map.cend()) {
        return (this->*(command_it->second))(cmd.arg());
    }

    return 127;
}
