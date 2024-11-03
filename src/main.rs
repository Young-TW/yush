use clap::Arg;

use yush::shell::Shell;
use yush::command::Command;

const YUSH_VERSION: &str = "v1.0.0";

fn main() {
    let matches = clap::Command::new("yush")
        .version(YUSH_VERSION)
        .author("Young")
        .about("simple and modern shell")
        .arg(
            Arg::new("o")
                .long("debug-output")
                .value_name("FILE")
                .help("Enable debug message output to a file")
        )
        .arg(
            Arg::new("c")
                .long("command")
                .value_name("COMMAND")
                .help("Execute single command")
        )
        .arg(
            Arg::new("i")
                .long("interactive")
                .help("Is interactive mode")
                .default_value("true")
        )
        .get_matches();

    let shell: Shell = Shell::new();

    if let Some(command) = matches.get_one::<String>("command") {
        let mut cmd = Command::from_str(command);
        let output = shell.exec_cmd(&mut cmd);
        println!("{}", output);
    } else {
        // Run interactive shell if no command is provided
        shell.run();
    }
}
