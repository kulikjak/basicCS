
use std::time::{Instant, SystemTime, UNIX_EPOCH};

// This is not rand at all! Rust doesn't implement rand in its standard library, 
// and since this is for these simple examples, it is sufficient.
fn rand() -> u32 {
  SystemTime::now()
    .duration_since(UNIX_EPOCH)
    .unwrap()
    .subsec_nanos()
}

// Global variable for working as a comparison counter
static mut COUNTER: i64 = 0;

fn bubble_sort(list: &mut [i32], size: usize) {
  for _i in 0 .. size {
    for j in 1 .. size {
      unsafe { COUNTER += 1; }
      if list[j - 1] > list[j] {
        list.swap(j - 1, j);
      }
    }
  }
}
fn bubble_sort2(list: &mut [i32], size: usize) {
  for _i in 0 .. size {
    let mut sorted = true;
    for j in 1 .. size {
      unsafe { COUNTER += 1; }
      if list[j - 1] > list[j] {
        list.swap(j - 1, j);
        sorted = false;
      }
    }
    if sorted { break; }
  }
}

fn shaker_sort(list: &mut [i32], size: usize) {
  let rounded = ((size as f64) / 2.0).ceil();
  for _i in 0 .. rounded as usize {
    let mut sorted = true;
    for j in 1 .. size {
      unsafe { COUNTER += 1; }
      if list[j - 1] > list[j] {
        list.swap(j - 1, j);
        sorted = false;
      }
    }
    for j in (1 .. size).rev() {
      unsafe { COUNTER += 1; }
      if list[j - 1] > list[j] {
        list.swap(j - 1, j);
        sorted = false;
      }      
    }
    if sorted {
      break;
    }
  }
}
fn shaker_sort2(list: &mut [i32], size: usize) {

  // initial positions of the pointers
  let mut sp = 1;
  let mut ep = size;

  while sp < ep {
    let mut fep = sp;
    for j in sp .. ep {
      unsafe { COUNTER += 1; }
      if list[j - 1] > list[j] {
        list.swap(j - 1, j);
        fep = j;
      }
    }
    ep = fep;
    let mut fsp = ep;
    for j in (sp .. ep).rev() {
      unsafe { COUNTER += 1; }
      if list[j - 1] > list[j] {
        list.swap(j - 1, j);
        fsp = j + 1;
      }
    }
    sp = fsp;
  }
}

fn selection_sort(list: &mut [i32], size: usize) {
  for i in 0 .. size {
    let mut max = i;
    for j in i + 1 .. size {
      unsafe { COUNTER += 1; }
      if list[j] < list[max] {
        max = j;
      }
    }
    list.swap(i, max);
  }
}

fn insertion_sort(list: &mut [i32], size: usize) {
  for i in 0 .. size - 1 {
    let temp = list[i + 1];
    for j in (1 .. i + 2).rev() {
      if j < 1 || temp >= list[j - 1] {
        list[j] = temp;
        break;
      }
      unsafe { COUNTER += 1; }
      list[j] = list[j - 1];
    }
  }
}


fn generate_random_list(size: usize) -> Vec<i32> {
  let mut vec = Vec::with_capacity(size);
  for _i in 0 .. size {
    vec.push((rand() as i32) % 100);
  }
  vec
}
fn generate_ascending_list(size: usize) -> Vec<i32> {
  let mut vec = Vec::with_capacity(size);
  for i in 0 .. size {
    vec.push(i as i32);
  }
  vec
}
fn generate_descending_list(size: usize) -> Vec<i32> {
  let mut vec = Vec::with_capacity(size);
  for i in 0 .. size {
    vec.push((size as i32) - (i as i32) - 1);
  }
  vec
}

fn is_sorted(list: &[i32], size: usize) -> bool {
  for i in 1 .. size {
    if list[i - 1] > list[i] {
      return false;
    }
  }
  true
}

#[derive(Clone, Copy)]
enum Input {
  Ascending,
  Descending,
  Random,
}

fn run_examples(size: usize, itype: Input) {

  fn generate_list(size: usize, itype: Input) -> Vec<i32> {
    match itype {
      Input::Ascending => return generate_ascending_list(size),
      Input::Descending => return generate_descending_list(size),
      Input::Random => return generate_random_list(size)
    }
  }

  {
    unsafe { COUNTER = 0; }
    let mut vector = generate_list(size, itype);
    let now = Instant::now();
    bubble_sort(&mut vector, size);
    unsafe {
      println!("Bubble sort\t comparisons: {}\t time: {}s", COUNTER, now.elapsed().as_secs());
    }
    assert!(is_sorted(&vector, size), "Vector is not properly sorted.");
  }

  {
    unsafe { COUNTER = 0; }
    let mut vector = generate_list(size, itype);
    let now = Instant::now();
    bubble_sort2(&mut vector, size);
    unsafe {
      println!("Bubble sort 2\t comparisons: {}\t time: {}s", COUNTER, now.elapsed().as_secs());
    }
    assert!(is_sorted(&vector, size), "Vector is not properly sorted.");
  }

  {
    unsafe { COUNTER = 0; }
    let mut vector = generate_list(size, itype);
    let now = Instant::now();
    shaker_sort(&mut vector, size);
    unsafe {
      println!("Shaker sort\t comparisons: {}\t time: {}s", COUNTER, now.elapsed().as_secs());
    }
    assert!(is_sorted(&vector, size), "Vector is not properly sorted.");
  }

  {
    unsafe { COUNTER = 0; }
    let mut vector = generate_list(size, itype);
    let now = Instant::now();
    shaker_sort2(&mut vector, size);
    unsafe {
      println!("Shaker sort 2\t comparisons: {}\t time: {}s", COUNTER, now.elapsed().as_secs());
    }
    assert!(is_sorted(&vector, size), "Vector is not properly sorted.");
  }

  {
    unsafe { COUNTER = 0; }
    let mut vector = generate_list(size, itype);
    let now = Instant::now();
    selection_sort(&mut vector, size);
    unsafe {
      println!("Selection sort\t comparisons: {}\t time: {}s", COUNTER, now.elapsed().as_secs());
    }
    assert!(is_sorted(&vector, size), "Vector is not properly sorted.");
  }

  {
    unsafe { COUNTER = 0; }
    let mut vector = generate_list(size, itype);
    let now = Instant::now();
    insertion_sort(&mut vector, size);
    unsafe {
      println!("Insertion sort\t comparisons: {}\t time: {}s", COUNTER, now.elapsed().as_secs());
    }
    assert!(is_sorted(&vector, size), "Vector is not properly sorted.");
  }
}

fn main() {
  let size = 10000;

  println!("Ascending input");
  run_examples(size, Input::Ascending);
  println!("\nDescending input");
  run_examples(size, Input::Descending);
  println!("\nRandom input");
  run_examples(size, Input::Random);
}
