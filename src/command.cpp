#include "command.h"

#include <cctype>
#include <set>
#include <string>

#include "fmt/format.h"

#include "shell.h"

extern char** environ;
extern Shell shell;

Command::Command() {}

Command::Command(std::string_view cmd) : command{cmd} {}

int Command::assign(std::string_view cmd) {
    this->command = cmd;
    return 0;
}

int Command::assign(std::vector<std::string>& args) {
    this->args = args;
    return 0;
}

int Command::assign(Command& cmd) {
    this->command = cmd.command;
    this->args = cmd.args;
    return 0;
}

std::string Command::get() { return this->command; }

namespace {

// Read a variable reference starting just after a '$'. Supports `$NAME` and
// `${NAME}`; `i` is advanced past the reference. A lone `$` (no valid name)
// is kept literal.
std::string expand_var(const std::string& input, std::size_t& i) {
    const std::size_t n{input.size()};

    if (i < n && input[i] == '{') {
        ++i;
        const std::size_t start{i};
        while (i < n && input[i] != '}') {
            ++i;
        }
        std::string name{input.substr(start, i - start)};
        if (i < n) {
            ++i;  // skip '}'
        }
        return std::string(shell.vars.get(name));
    }

    const std::size_t start{i};
    while (i < n && (std::isalnum(static_cast<unsigned char>(input[i])) || input[i] == '_')) {
        ++i;
    }
    if (i == start) {
        return "$";  // '$' not followed by a name stays literal
    }
    return std::string(shell.vars.get(input.substr(start, i - start)));
}

// Tokenize a line into words, applying quote rules and variable expansion:
//   'single' -> literal, no expansion
//   "double" -> expansion of $, backslash escapes \" \\ \$
//   bare     -> expansion of $, backslash escapes next char
// Adjacent pieces join into one word (e.g. pre"mid"$VAR is a single arg).
std::vector<std::string> lex_and_expand(const std::string& input) {
    std::vector<std::string> result;
    std::string cur;
    bool has_token{false};
    const std::size_t n{input.size()};

    for (std::size_t i{0}; i < n;) {
        const char c{input[i]};

        if (c == ' ' || c == '\t') {
            if (has_token) {
                result.push_back(cur);
                cur.clear();
                has_token = false;
            }
            ++i;
            continue;
        }

        if (c == '#' && !has_token) {
            break;  // comment runs to end of line
        }

        if (c == '\'') {
            has_token = true;
            ++i;
            while (i < n && input[i] != '\'') {
                cur += input[i++];
            }
            if (i < n) {
                ++i;  // closing quote
            }
            continue;
        }

        if (c == '"') {
            has_token = true;
            ++i;
            while (i < n && input[i] != '"') {
                if (input[i] == '$') {
                    ++i;
                    cur += expand_var(input, i);
                } else if (input[i] == '\\' && i + 1 < n &&
                           (input[i + 1] == '"' || input[i + 1] == '\\' || input[i + 1] == '$')) {
                    cur += input[i + 1];
                    i += 2;
                } else {
                    cur += input[i++];
                }
            }
            if (i < n) {
                ++i;  // closing quote
            }
            continue;
        }

        if (c == '\\') {
            if (i + 1 < n) {
                cur += input[i + 1];
                i += 2;
                has_token = true;
            } else {
                ++i;
            }
            continue;
        }

        if (c == '$') {
            has_token = true;
            ++i;
            cur += expand_var(input, i);
            continue;
        }

        cur += c;
        has_token = true;
        ++i;
    }

    if (has_token) {
        result.push_back(cur);
    }
    return result;
}

}  // namespace

int Command::parse() {
    this->args = lex_and_expand(this->command);

    // Alias/function resolution: if the first word names an alias or function,
    // replace it with the (expanded) body and forward the remaining arguments.
    // A `seen` set guards against alias cycles (e.g. alias ls="ls --color").
    std::set<std::string> seen;
    while (!this->args.empty() && shell.functions.exist(this->args[0]) &&
           seen.find(this->args[0]) == seen.end()) {
        seen.insert(this->args[0]);
        std::vector<std::string> body{lex_and_expand(std::string(shell.functions.get(this->args[0])))};
        body.insert(body.end(), this->args.begin() + 1, this->args.end());
        this->args = std::move(body);
    }

    return 0;
}

bool Command::empty() { return this->command.empty(); }

const std::vector<std::string>& Command::arg() const { return this->args; }
