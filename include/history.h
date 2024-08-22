#include <vector>
#include <string>
#include <filesystem>

class History {
public:
    History() = default;

    int check_file(std::filesystem::path home);
    int load_file();
    int write_file();

    int add(const std::string& cmd);

    std::string get();
    std::string get(size_t index);

    int size();


private:
    std::vector<std::string> history;
    std::filesystem::path history_dir = ".local/share/yush";
    std::filesystem::path file = ".local/share/yush/history";
};
