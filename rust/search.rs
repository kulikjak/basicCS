
fn linear_search(list: &[i32], size: i32, n: i32) -> i32 {
  for i in 0 .. size {
    if list[i as usize] == n {
      return i;
    }
  }
  return -1;
}

fn binary_search(list: &[i32], size: i32, n: i32) -> i32 {
  let mut sp = 0;
  let mut ep = size;

  while sp < ep {
    let middle = (sp + ep) / 2;
    if list[middle as usize] == n { return middle; }

    if list[middle as usize] > n {
      ep = middle;
    } else {
      sp = middle + 1;
    }
  }
  return -1;
}

fn interpolation_search(list: &[i32], size: i32, n: i32) -> i32 {
  let mut sp = 0;
  let mut ep = size - 1;

  while sp <= ep {
    let guess = ((sp as f64) + ((ep - sp) as f64) / ((list[ep as usize] - list[sp as usize]) as f64) * ((n - list[sp as usize]) as f64)) as i32;
    if list[guess as usize] == n {
      return guess;
    }

    if list[guess as usize] > n {
      ep = guess - 1;
    } else {
      sp = guess + 1;
    }
  }
  return -1;
}

fn main() {
  let random = [71, 34, 66, 33, 80, 60, 8, 55, 51, 98, 37, 45, 16, 96, 35, 78, 44, 5, 57, 6, 18, 54, 85, 95, 62, 81, 59, 63, 31, 82, 39, 77, 19,
                12, 23, 41, 25, 90, 42, 9, 75, 30, 61, 29, 43, 74, 22, 04, 69, 24, 13, 93, 53, 92, 27, 38, 50, 58, 79, 47, 28, 86, 10, 21, 20, 56,
                94, 11, 46, 88, 70, 49, 99, 67, 1, 97, 17, 15, 52, 73, 48, 65, 91, 68, 14, 32, 72, 89, 84, 64, 10, 2, 83, 7, 87, 40, 26, 36, 76, 3];
  let sorted = [1, 2, 3, 4, 5, 8, 12, 13, 15, 16, 17, 18, 20, 23, 25, 27, 30, 32, 33, 37, 38, 41, 42, 44, 45, 47, 49, 50, 52, 53, 56, 57, 58, 59, 60, 62, 65, 67,
                68, 69, 71, 73, 77, 80, 83, 84, 85, 89, 93, 96, 97, 98, 100, 101, 102, 103, 104, 106, 108, 110, 112, 114, 116, 117, 118, 122, 126, 127, 128, 129,
                136, 137, 138, 141, 145, 147, 148, 149, 150, 154, 155, 159, 163, 165, 169, 171, 172, 173, 176, 177, 180, 181, 185, 186, 189, 192, 193, 197, 199, 200];

  println!("{}", linear_search(&random, 100, 14));
  println!("{}", linear_search(&sorted, 100, 12));

  println!("{}", binary_search(&sorted, 100, 12));
  println!("{}", interpolation_search(&sorted, 100, 12));
}
