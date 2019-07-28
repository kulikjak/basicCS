
fn list_mersenne_primes(max: i32) {
  for i in 1 .. max {
    let candidate = (2 << i) - 1;
    if is_prime(candidate) {
      println!("2^{}-1 = {}", i + 1, candidate);
    }
  }
}

fn is_mersenne_prime(prime: i32) -> bool {
  let power = ((prime + 1) as f64).log2();
  power == power.floor()
}

fn is_prime(a: i32) -> bool {
  let root = (a as f64).sqrt() as i32;
  for i in 2 .. root + 1 {
    if a % i == 0 { return false; }
  }
  true
}

fn main() {
  list_mersenne_primes(31);

  println!("{}", is_mersenne_prime(7) as i32);
  println!("{}", is_mersenne_prime(8) as i32);
  println!("{}", is_mersenne_prime(30) as i32);
  println!("{}", is_mersenne_prime(127) as i32); 
}
