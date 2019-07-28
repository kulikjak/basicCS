
use std::env;
use std::process::exit;

fn naive_matching(string: &str, pattern: &str) {
  let size = string.len();
  let psize = pattern.len();

  for i in 0 .. (size - psize + 1) {
    if &string[i..i+psize] == pattern {
      print!("{} ", i);
    }
  }
  println!("");
}

fn naive_matching2(string: &str, pattern: &str) {
  let size = string.len();
  let psize = pattern.len();

  for i in 0 .. (size - psize + 1) {
    let mut ok = true;
    for j in 0 .. psize {
      if string.chars().nth(i + j) != pattern.chars().nth(j) {
        ok = false;
        break;
      }
    }
    if ok {
      print!("{} ", i);
    }
  }
  println!("");
}

fn main() {
  let args: Vec<String> = env::args().collect();
  if args.len() != 3 {
    eprintln!("Program needs exactly two arguments (haystack and needle)");
    exit(1);
  }

  naive_matching(&args[1], &args[2]);
  naive_matching2(&args[1], &args[2]);
}
