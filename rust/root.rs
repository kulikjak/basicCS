
// Float comparison precision
const PRECISION: f64 = 0.000001;

fn compare(a: f64, b: f64) -> i32 {
  if (a - b).abs() < PRECISION { return 0; }
  if (a - b) < 0.0 { return -1; }
  return 1;
}

fn get_root(square: f64) {
  let mut jump = square;
  let mut guess = 0.0;
  let mut steps = 0;
  let mut direction = true;

  loop {
    println!("{:4} {:.20}", steps, guess);

    let cmp = compare(guess * guess, square);
    if cmp == -1 {
      if !direction {
        jump *= 0.5;
        direction = true;
      }
      guess += jump;
    } else if cmp == 1 {
      if direction {
        jump *= 0.5;
        direction = false;
      }
      guess -= jump;
    }
    steps += 1;

    if cmp == 0 { break; }
  }
  println!("real {:.20}", square.sqrt());
}

fn main() {
  get_root(126.0);
}
