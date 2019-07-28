
use std::time::{SystemTime, UNIX_EPOCH};

// This is not random at all! Rust doesn't implement rand in its standard library, 
// and since this is for these simple examples, it is sufficient.
fn rand() -> u32 {
  SystemTime::now()
    .duration_since(UNIX_EPOCH)
    .unwrap()
    .subsec_nanos()
}

#[derive(Debug)]
struct Matrix {
  rows: usize,
  cols: usize,
  matrix: Vec<Vec<i32>>
}

impl Matrix {

  fn _determinant2x2(&self) -> i32 {
    self.matrix[0][0] * self.matrix[1][1] - self.matrix[0][1] * self.matrix[1][0]
  }

  fn _determinant3x3(&self) -> i32 {
    self.matrix[0][0] * self.matrix[1][1] * self.matrix[2][2] +
      self.matrix[0][1] * self.matrix[1][2] * self.matrix[2][0] +
      self.matrix[0][2] * self.matrix[1][0] * self.matrix[2][1] -
      self.matrix[0][2] * self.matrix[1][1] * self.matrix[2][0] -
      self.matrix[0][1] * self.matrix[1][0] * self.matrix[2][2] -
      self.matrix[0][0] * self.matrix[1][2] * self.matrix[2][1]
  }
}

impl Matrix {

  fn new(rows: usize, cols: usize) -> Matrix {
    Matrix { rows: rows, cols: cols, matrix: vec![vec![0; cols]; rows] }
  }

  fn set_random(&mut self, min: i32, max: i32) {
    for i in 0 .. self.rows {
      for j in 0 .. self.cols {
        self.matrix[i][j] = ((rand() as i32) % (max - min + 1)) + min;
      }
    }
  }

  fn print_matrix(&self) {
    for i in 0 .. self.rows {
      print!("| ");
      for j in 0 .. self.cols {
        print!("{:3} ", self.matrix[i][j]);
      }
      println!("|");
    }
  }

  fn print_transposed_matrix(&self) {
    for j in 0 .. self.cols {
      print!("| ");
      for i in 0 .. self.rows {
        print!("{:3} ", self.matrix[i][j]);
      }
      println!("|");
    }
  }

  fn smul(&self, scalar: i32) -> Matrix {
    let mut new = Matrix::new(self.rows, self.cols);
    for i in 0 .. self.rows {
      for j in 0 .. self.cols {
        new.matrix[i][j] = self.matrix[i][j] * scalar;
      }
    }
    new
  }

  fn mmul(&self, other: &Matrix) -> Matrix {
    let mut new = Matrix::new(self.rows, other.cols);
    for i in 0 .. self.rows {
      for j in 0 .. other.cols {
        for k in 0 .. self.cols {
          new.matrix[i][j] += self.matrix[i][k] * other.matrix[k][j];
        }
      }
    }
    new
  }

  fn madd(&self, other: &Matrix) -> Matrix {
    let mut new = Matrix::new(self.rows, self.cols);
    for i in 0 .. self.rows {
      for j in 0 .. self.cols {
        new.matrix[i][j] = self.matrix[i][j] + other.matrix[i][j];
      }
    }
    new
  }

  fn sum_matrix(&self) -> i32 {
    let mut sum = 0;
    for i in 0 .. self.rows {
      for j in 0 .. self.cols {
        sum += self.matrix[i][j];
      }
    }
    sum
  }

  fn determinant(&self) -> i32 {
    if self.rows != self.cols {
      panic!("Cannot calculate determinant of non square matrices.");
    }
    if self.rows == 2 {
      return self._determinant2x2();
    }
    if self.rows == 3 {
      return self._determinant3x3();
    }
    unimplemented!();
  }
}


fn main() {

  let mut matrix1 = Matrix::new(3, 3);
  matrix1.set_random(0, 10);
  matrix1.print_matrix();
  println!("");

  let mut matrix2 = Matrix::new(3, 3);
  matrix2.set_random(0, 10);
  matrix2.print_matrix();
  println!("");

  let temp = matrix1.smul(2);
  temp.print_matrix();
  println!("");

  let temp = matrix1.madd(&matrix2);
  temp.print_matrix();
  println!("");

  let temp = matrix1.mmul(&matrix2);
  temp.print_matrix();
  println!("");

  println!("Determinant {}", temp.determinant());
  println!("Matrix sum {}", temp.sum_matrix());

  println!("\nTransposed matrix");
  temp.print_transposed_matrix();
}
