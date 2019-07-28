
fn seconds_to_time(total_seconds: i32) {
  let seconds = total_seconds % 60;
  let minutes = total_seconds / 60 % 60;
  let hours = total_seconds / 60 / 60;

  println!("{} hours, {} minutes, {} seconds", hours, minutes, seconds);
}

fn main() {
  seconds_to_time(45265);
}
