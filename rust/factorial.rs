
fn factorial(number: i32) -> i32 {
  if number < 0 { return -1; }

  let mut factorial = 1;
  for i in 2 .. number + 1 {
    factorial *= i;
  }
  factorial
}

fn rec_factorial(number: i32) -> i32 {
  if number < 0 { return -1; }
  if number == 0 { return 1; }

  number * rec_factorial(number - 1)
}


fn main() {
  println!("{}", rec_factorial(5));
  println!("{}", factorial(4));
}
