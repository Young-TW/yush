use std::collections::HashMap;
use std::env;
use std::fs;
use std::io::{self, BufRead, Write};
use std::path::PathBuf;
use std::process::{Command, exit};
use signal_hook::iterator::Signals;
use std::process::ExitStatus;

pub struct Shell {
    pub vars: HashMap<String, String>,
    pub config_dir: PathBuf,
    pub rc_file: PathBuf,
}

impl Shell {
    pub fn new() -> Self {
        let mut vars = HashMap::new();
        for (key, value) in env::vars() {
            vars.insert(key, value);
        }
        if !vars.contains_key("HOME") {
            eprintln!("Error: HOME is not set");
            exit(1);
        }
        let home = PathBuf::from(vars.get("HOME").unwrap());
        let config_dir = home.join(".yush");
        if !config_dir.exists() {
            eprintln!("Error: yush config dir path does not exist");
            println!("Auto creating config dir");
            fs::create_dir(&config_dir).expect("Failed to create config dir");
        }

        let rc_file = config_dir.join("yushrc");
        if rc_file.exists() {
            // 加載 rc 文件
            // `Shell::run_script_file` 是執行文件的函數
        }

        Shell {
            vars,
            config_dir,
            rc_file,
        }
    }

    pub fn run(&self) -> ExitStatus {
        let mut signals = Signals::new(&[signal_hook::consts::SIGINT]).expect("Failed to set up signal handler");
        let mut command_history = Vec::new();

        for signal in signals.forever() {
            match signal {
                signal_hook::consts::SIGINT => {
                    println!("\nCaught interrupt signal. Type 'exit' to leave shell.");
                }
                _ => unreachable!(),
            }
        }

        let mut status = Default::default();
        loop {
            print!("> ");
            io::stdout().flush().unwrap();

            let mut input = String::new();
            io::stdin().read_line(&mut input).unwrap();
            let input = input.trim();

            if input == "exit" {
                break;
            }

            let mut cmd = Command::new(input);
            status = cmd.spawn().expect("Failed to execute command").wait().expect("Command wasn't running");

            if !status.success() {
                eprintln!("Error executing command");
            }

            command_history.push(input.to_string());
        }

        status
    }

    pub fn exec_file(cmd: Vec<String>) -> i32 {
        let file_path = {
            let command = &cmd[0];
            if fs::metadata(command).map(|m| m.is_file()).unwrap_or(false) {
                PathBuf::from(command)
            } else {
                if let Some(paths) = env::var_os("PATH") {
                    for path in env::split_paths(&paths) {
                        let candidate = path.join(command);
                        if fs::metadata(&candidate).map(|m| m.is_file()).unwrap_or(false) {
                            return 1; // candidate;
                        }
                    }
                }
                return -1; // None;
            }
        };

        let file_path = file_path.to_str();

        match file_path {
            Some(file_path) => {
                let status = Command::new(file_path)
                    .args(&cmd[1..])
                    .status();
                match status {
                    Ok(exit_status) => exit_status.code().unwrap_or(-1),
                    Err(_) => 127,
                }
            }
            None => 127,
        }
    }
}
