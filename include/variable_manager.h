#ifndef VARIABLE_MANAGER_H
#define VARIABLE_MANAGER_H

#include <string>
#include <string_view>
#include <unordered_map>

class VariableManager {
   public:
    VariableManager();

    VariableManager& set(const std::string& name, std::string_view value);

    std::string_view get(const std::string& name);

    bool exist(const std::string& name);

   private:
    std::unordered_map<std::string, std::string> variables;
};

#endif
