#include "history.h"

#include <fstream>

int History::set_file(const std::filesystem::path& file) {
    this->file = file;
    return 0;
}

int History::check_file() {
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
