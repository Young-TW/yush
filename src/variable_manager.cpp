#include "variable_manager.h"
#include <unordered_map>

VariableManager::VariableManager() = default;

VariableManager& VariableManager::set(const std::string& name, std::string_view value) {
    variables[name] = std::string(value);
    return *this;
};

VariableManager& VariableManager::set_exported(const std::string& name, std::string_view value) {
    variables[name] = std::string(value);
    exported.insert(name);
    return *this;
}

VariableManager& VariableManager::mark_exported(const std::string& name) {
    variables.try_emplace(name, "");
    exported.insert(name);
    return *this;
}

std::string_view VariableManager::get(const std::string& name) {
    if (auto it = variables.find(name); it != variables.end()) {
        return it->second;
    }
    return "";
}

bool VariableManager::exist(const std::string& name) {
    return variables.find(name) != variables.end();
}

std::vector<std::string> VariableManager::environment() const {
    std::vector<std::string> env;
    env.reserve(exported.size());
    for (const auto& name : exported) {
        if (auto it = variables.find(name); it != variables.end()) {
            env.push_back(name + "=" + it->second);
        }
    }
    return env;
}
