// history.rs

use std::fs;
use std::fs::File;
use std::io::{self, BufRead, BufReader, Write};
use std::path::{Path, PathBuf};

#[derive(Debug)]
pub struct History {
    history_dir: PathBuf,
    file: PathBuf,
}

impl History {
    pub fn new(history_dir: &str, file: &str) -> Self {
        History {
            history_dir: PathBuf::from(history_dir),
            file: PathBuf::from(file),
        }
    }

    pub fn check_file(&mut self, home: &Path) -> io::Result<bool> {
        self.history_dir = home.join(&self.history_dir);
        self.file = home.join(&self.file);

        if !self.history_dir.exists() {
            fs::create_dir_all(&self.history_dir)?;
        }
        Ok(self.file.exists())
    }

    pub fn load_file(&self) -> io::Result<Vec<String>> {
        let file = File::open(&self.file)?;
        let reader = BufReader::new(file);

        reader.lines().collect()
    }
}
