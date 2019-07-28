
use std::time::Instant;

const STUDENT_LIST_SIZE: usize = 10;

#[derive(Clone)]
struct Student {
  grade: i32,
  name: String,
}

impl Student {
  fn new(grade: i32, name: &str) -> Student {
    Student {grade: grade, name: String::from(name)}
  }
}

/*
 * Counting sort.
 * Complexity: O(n*m)
 */
fn counting_sort(students: &mut [Student; STUDENT_LIST_SIZE]) {

  let mut min = students[0].grade;
  let mut max = students[0].grade;

  for student in students.iter() {
    if student.grade < min { min = student.grade; }
    if student.grade > max { max = student.grade; }
  }

  let mut counts = vec![0; (max - min + 1) as usize];
  for student in students.iter() {
    counts[(student.grade - min) as usize] += 1;
  }

  let mut positions = vec![0; (max - min + 1) as usize];
  for i in 1 .. (max - min + 1) as usize {
    positions[i] = positions[i - 1] + counts[i - 1];
  }

  // This is not very efficient way of doing this as we are cloning
  // entire vactor rather than working with pointers.
  let mut students_copy = students.to_vec();

  for i in 0 .. STUDENT_LIST_SIZE {
    let mut new_position = positions[(students_copy[i].grade - min) as usize];
    positions[(students_copy[i].grade - min) as usize] += 1;
    std::mem::swap(&mut students[new_position], &mut students_copy[i]);
  }
}

fn print_students(students: &[Student; STUDENT_LIST_SIZE]) {
  for i in 0 .. STUDENT_LIST_SIZE {
    println!("Name: {}\tGrade: {}", students[i].name, students[i].grade);
  }
}

fn main() {
  // student names from: http://fantasynamegenerators.com/
  let mut students = [
    Student::new(1, "Demosios"),
    Student::new(3, "Tyrosmus"),
    Student::new(2, "Agamexus"),
    Student::new(3, "Thaulix"),
    Student::new(1, "Acamedes"),
    Student::new(4, "Bryron"),
    Student::new(5, "Icopheus"),
    Student::new(1, "Tyrorus"),
    Student::new(4, "Coryneus"),
    Student::new(1, "Lonius")
  ];

  println!("Initial list:");
  print_students(&students);

  let now = Instant::now();
  counting_sort(&mut students);
  let duration = now.elapsed().as_secs();

  println!("\nSorted list:");
  print_students(&students);

  println!("\nCounting sort\t time: {}s", duration);
}
