// variable_manager.rs

use std::collections::HashMap;

#[derive(Debug, Default)]
pub struct VariableManager {
    variables: HashMap<String, String>,
}

impl VariableManager {
    pub fn new() -> Self {
        VariableManager {
            variables: HashMap::new(),
        }
    }

    pub fn set(&mut self, name: &str, value: &str) -> &mut Self {
        self.variables.insert(name.to_string(), value.to_string());
        self
    }

    pub fn get(&self, name: &str) -> Option<&String> {
        self.variables.get(name)
    }

    pub fn exist(&self, name: &str) -> bool {
        self.variables.contains_key(name)
    }
}
