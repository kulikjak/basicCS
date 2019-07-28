/*
 * Several algorithms from high school cominatorics.
 * Author: Jakub Kulik
 */

fn variation(k: i32, n: i32) -> i32 {
  let mut result = 1;
  for i in (n - k + 1) .. (n + 1) {
    result *= i;
  }
  result
}

fn variation_with_factorial(k: i32, n: i32) -> i32 {
  factorial(n) / factorial(n - k)
}

fn binomial_coefficient_with_factorial(k: i32, n: i32) -> i32 {
  factorial(n) / (factorial(n - k) * factorial(k))
}

fn binomial_coefficient_better(k: i32, n: i32) -> i32 {
  factorial_range(n, std::cmp::max(n - k, k) + 1) / factorial(std::cmp::min(n - k, k))
}

fn binomial_coefficient_pascal(k: i32, n: i32) -> i32 {
  let mut value = 1;
  for i in 0 .. k {
    value = value * (n - i) / (i + 1);
  }
  value
}

fn factorial_range(j: i32, min: i32) -> i32 {
  let mut value = 1;
  for i in std::cmp::max(min, 1) .. j + 1 {
    value *= i;
  }
  value
}

fn factorial(i: i32) -> i32 {
  factorial_range(i, 1)
}


fn main() {
  println!("{}", variation(6, 12));
  println!("{}", variation_with_factorial(6, 12));

  println!("{}", binomial_coefficient_with_factorial(12, 12));
  println!("{}", binomial_coefficient_better(0, 12));
  println!("{}", binomial_coefficient_pascal(12, 15));
}
