#include "history.h"

#include <filesystem>
#include <fstream>

int History::check_file(std::filesystem::path home) {
    this->history_dir = home/this->history_dir;
    this->file = home/this->file;
    if (!(std::filesystem::exists(this->history_dir) && std::filesystem::is_directory(this->history_dir))) {
        std::filesystem::create_directories(this->history_dir);
    }
    return std::filesystem::exists(this->file);
}

int History::load_file() {
    std::ifstream fin(this->file);
    std::string input;
    while (getline(fin, input)) {
        this->history.push_back(input);
    }

    fin.close();
    this->persisted = this->history.size();
    return 0;
}

int History::write_file() {
    std::ofstream fout(this->file, std::ios::app);
    for (std::size_t i{this->persisted}; i < this->history.size(); ++i) {
        fout << this->history[i] << std::endl;
    }

    fout.close();
    this->persisted = this->history.size();
    return 0;
}

int History::add(const std::string& cmd) {
    this->history.push_back(cmd);
    return 0;
}

std::string History::get() {
    if (history.empty()) {
        return {};
    }
    return history.back();
}

std::string History::get(size_t index) {
    if (index >= history.size()) {
        return {};
    }
    return history[index];
}

int History::size() {
    return history.size();
}
