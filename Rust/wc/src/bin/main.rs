use std::env;
use std::fs;

fn main() -> std::io::Result<()> {
    // Get the command-line arguments; each contains a filename.
    let mut args = env::args();
    // Skip the 0th argument, which is just the program name.
    args.next();
    let mut files       = 0usize;
    let mut total_lines = 0;
    let mut total_words = 0;
    let mut total_chars = 0;
    // Get line, word, and char counts for each file.
    for argument in args {
        // Open the file and read it into a String.
        let contents = fs::read_to_string(&argument)?;
        // Count lines, words, and chars (not bytes!).
        let lines = contents.lines().count();
        let words = contents.split_whitespace().count();
        let chars = contents.chars().count();
        // Print results.
        println!("{} {} {} {}", lines, words, chars, argument);
        files += 1;
        total_lines += lines;
        total_words += words;
        total_chars += chars;
    }
    if 1 < files {
        println!("{} {} {} total", total_lines, total_words, total_chars);
    }
    Ok(())
}
