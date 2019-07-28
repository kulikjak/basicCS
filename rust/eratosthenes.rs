
fn sieve_of_eratosthenes(max: usize) {
  let mut sieve = vec![false; max];
  let boundary = (max as f64).sqrt() as usize + 1;

  for i in 2 .. boundary {
    if sieve[i] {
      continue;
    }
    print!("{} ", i);
    for j in ((2 * i) .. max).step_by(i) {
      sieve[j] = true;
    }
  }
  for i in boundary .. max {
    if !sieve[i] {
      print!("{} ", i);
    }
  }
  println!("");
}

fn sieve_of_eratosthenes2(max: usize) {
  let mut sieve: Vec<u8> = vec![0; max];
  let boundary = (max as f64).sqrt() as usize + 1;

  for i in 2 .. boundary {
    if sieve[i] != 0 {
      continue;
    }
    print!("{} ", i);
    for j in ((2 * i) .. max).step_by(i) {
      sieve[j] = 1;
    }
  }
  for i in boundary .. max {
    if sieve[i] == 0 {
      print!("{} ", i);
    }
  }
  println!("");
}

fn sieve_of_eratosthenes3(max: usize) {
  let size = ((max as f64) / 32.0).ceil() as usize;
  let boundary = (max as f64).sqrt() as usize + 1;

  let mut sieve: Vec<u32> = vec![0; size];

  for i in 2 .. boundary {
    if (sieve[i / 32] & (1 << (i % 32))) != 0 {
      continue;
    }

    for j in ((2 * i) .. max).step_by(i) {
      sieve[j / 32] |= 1 << (j % 32);
    }
    print!("{} ", i);
  }

  for i in boundary .. max {
    if (sieve[i / 32] & (1 << (i % 32) )) == 0 {
      print!("{} ", i);
    }
  }
  println!("");
}

fn main() {
  let max = 512;

  sieve_of_eratosthenes(max);
  sieve_of_eratosthenes2(max);
  sieve_of_eratosthenes3(max);

  // Sizes of the auxiliary data structures
  println!("(1) Array size: {}B", std::mem::size_of::<bool>() * max);
  println!("(2) Array size: {}B", std::mem::size_of::<u8>() * max);

  let size = ((max as f64) / 32.0).ceil() as usize;
  println!("(3) Array size: {}B", std::mem::size_of::<u32>() * size);
}
