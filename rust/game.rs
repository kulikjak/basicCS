
use std::io;
use std::io::Write;
use std::time::{SystemTime, UNIX_EPOCH};

// Constants needed for colored terminal output
const GREEN: &str = "\x1b[32m";
const CYAN:  &str = "\x1b[36m";
const RESET: &str = "\x1b[0m";


// This is not random at all! Rust doesn't implement rand in its standard library, 
// and since this is just for a guessing game, it is sufficient enough.
fn rand() -> u32 {
  SystemTime::now()
    .duration_since(UNIX_EPOCH)
    .unwrap()
    .subsec_nanos()
}

fn get_user_input() -> u32 {
  loop {
    let mut input_text = String::new();
    io::stdin()
        .read_line(&mut input_text)
        .expect("failed to read from stdin");

    let trimmed = input_text.trim();
    match trimmed.parse::<u32>() {
        Ok(i) => return i,
        Err(..) => println!("this was not an integer: {}", trimmed),
    }; 
  }
}

fn guessing_game() {
  let target = rand() % 100 + 1;

  println!("{}{}{}", GREEN, "Random number is in interval <1,100> ", RESET);
  loop {
    print!("{}{}{}", GREEN, "Guess a number: ", RESET);
    io::stdout().flush().ok().expect("Could not flush stdout");
    let guess = get_user_input();

    if guess > target {
      println!("{}{}{}", CYAN, "Correct number is smaller.", RESET);
    } else if guess < target {
      println!("{}{}{}", CYAN, "Correct number is higher.", RESET);
    } else {
      println!("{}{}{}", GREEN, "You got it!!", RESET);
      break;
    }
  }
}

fn main() {
  loop {
    guessing_game();
  }
}
