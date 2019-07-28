
fn fib(a: i32) -> i32 {
  let mut first = 0;
  let mut second = 1;

  for _i in 1 .. a {
    let temp = first + second;
    first = second;
    second = temp;
  }
  second
}

fn fib2(mut a: usize) -> i32 {
  let mut array = [0, 1];

  while a >= 2 {
    array[0] += array[1];
    array[1] += array[0];
    a -= 2;
  }
  array[a]
}

fn rec_fib(a: i32) -> i32 {
  if a < 2 { return a; }
  rec_fib(a - 1) + rec_fib(a - 2)
}


fn main() {
  println!("{}", fib(64));
  println!("{}", fib2(64));

  println!("{}", rec_fib(30));
}
