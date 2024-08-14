#include <vector>
#include <string>
#include <filesystem>

class History {
public:
    History() = default;

    int set_file(const std::filesystem::path& file);
    int check_file();
    int load_file();
    int write_file();

    int add(const std::string& cmd);

    std::string get();
    std::string get(size_t index);

    int size();


private:
    std::vector<std::string> history;
    std::filesystem::path file;
};
