#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class VariableManager {
public:
    VariableManager();

    // Set a value, preserving the variable's current export status.
    VariableManager& set(const std::string& name, std::string_view value);

    // Set a value and mark the variable as exported to child processes.
    VariableManager& set_exported(const std::string& name, std::string_view value);

    // Mark an existing (or new, empty) variable as exported.
    VariableManager& mark_exported(const std::string& name);

    std::string_view get(const std::string& name);

    bool exist(const std::string& name);

    // "name=value" entries for every exported variable, for building envp.
    std::vector<std::string> environment() const;

private:
    std::unordered_map<std::string, std::string> variables;
    std::unordered_set<std::string> exported;
};
