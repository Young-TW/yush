#include "variable_manager.h"
#include <unordered_map>

VariableManager::VariableManager() = default;

VariableManager& VariableManager::set(const std::string& name, std::string_view value) {
    variables[name] = std::string(value);
    return *this;
};

std::string_view VariableManager::get(const std::string& name) {
    if (auto it = variables.find(name); it != variables.end()) {
        return it->second;
    }
    return "";
}

bool VariableManager::exist(const std::string& name) {
    return variables.find(name) != variables.end();
}
