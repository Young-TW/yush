#include "history.h"

#include <filesystem>
#include <fstream>

int History::check_file(std::filesystem::path home) {
    this->history_dir = home/this->history_dir;
    this->file = home/this->file;
    if (!(std::filesystem::exists(this->history_dir) && std::filesystem::is_directory(this->history_dir))) {
        std::filesystem::create_directory(this->history_dir);
    }
    return std::filesystem::exists(this->file);
}

int History::load_file() {
    std::ifstream fin(this->file);
    std::string input;
    while (!fin.eof()) {
        getline(fin, input);
        this->history.push_back(input);
    }

    fin.close();
    return 0;
}

int History::write_file() {
    std::ofstream fout(this->file, std::ios::app);
    for (const auto& cmd : this->history) {
        fout << cmd << std::endl;
    }

    fout.close();
    return 0;
}

int History::add(const std::string& cmd) {
    this->history.push_back(cmd);
    return 0;
}

std::string History::get() {
    return history.back();
}

std::string History::get(size_t index) {
    return history[index];
}

int History::size() {
    return history.size();
}
