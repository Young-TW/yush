#[derive(Debug)]
pub struct Command {
    pub command: String,
    pub args: Vec<String>,
    pub status: i32,
}

impl Command {
    pub fn new() -> Self {
        Command {
            command: String::new(),
            args: Vec::new(),
            status: 0,
        }
    }

    pub fn from_str(cmd: &str) -> Self {
        Command {
            command: cmd.to_string(),
            args: Vec::new(),
            status: 0,
        }
    }

    pub fn assign_from_str(&mut self, cmd: &str) {
        self.command = cmd.to_string();
    }

    pub fn assign_from_vec(&mut self, args: Vec<String>) {
        self.args = args;
    }

    pub fn assign_from_command(&mut self, other: &Command) {
        self.command = other.command.clone();
        self.args = other.args.clone();
    }

    pub fn parse(&mut self) {
        // Parse command
    }

    pub fn exec(&mut self) -> i32 {
        // Execute command
        0
    }
}
