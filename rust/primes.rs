
use std::cmp;

fn factorization(a: i32) {
  let sqrt = (a as f64).sqrt() as i32;
  let mut remainder: i32 = a;

  for i in 2 .. (sqrt + 1) {
  	while remainder % i == 0 {
  		remainder = remainder / i;
  		print!("{:?} ", i);
  	}
  }
  if remainder > 1 {
  	print!("{:?} ", remainder);
  }
  println!("");
}

fn gcd(a: i32, b: i32) -> i32 {
  let mut min = cmp::min(a, b);
  let mut max = cmp::max(a, b);

  while min != 0 {
  	let temp = min;
  	min = max % min;
  	max = temp;
  }
  return max;
}

fn gcd2(a: i32, b: i32) -> i32 {
  if a == 0 {
  	return b;
  }
  gcd2(b % a, a)
}

fn is_perfect_number(a: i32) -> bool {
  let mut sum = 0;
  for i in 1 .. a {
  	if a % i == 0 {
      sum += i;
  	}
  }
  sum == a
}

fn perfect_numbers(max: i32) {
  for i in 2 .. max + 1 {
  	if is_perfect_number(i) {
  		print!("{:?} ", i);
  	}
  }
  println!("");
}

fn main() {
  factorization(35);
  factorization(1023);
  factorization(350);
  factorization(23453312);

  println!("{:?}", gcd(34, 32));
  println!("{:?}", gcd(38, 323));
  println!("{:?}", gcd(2, 3));
  println!("{:?}", gcd(340, 240));

  println!("{:?}", gcd2(34, 32));
  println!("{:?}", gcd2(38, 323));
  println!("{:?}", gcd2(2, 3));
  println!("{:?}", gcd2(340, 240));

  perfect_numbers(3000);
}
