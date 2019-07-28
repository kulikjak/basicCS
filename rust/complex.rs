
struct Complex {
	real: f64,
	imag: f64,
}

impl Complex {
	fn new(real: f64, imag: f64) -> Complex {
		Complex { real: real, imag: imag }
	}
	fn from_complex(other: &Complex) -> Complex {
		Complex { real: other.real, imag: other.imag }
	}

	fn print(&self) {
		println!("{}{:+}i", self.real, self.imag);
	}

	fn abs(&self) -> f64 {
		(self.real * self.real + self.imag * self.imag).sqrt()
	}

	fn add(&self, other: &Complex) -> Complex {
		Complex::new(self.real + other.real, self.imag + other.imag)
	}
	fn sub(&self, other: &Complex) -> Complex {
		Complex::new(self.real - other.real, self.imag - other.imag)
	}
	fn mul(&self, other: &Complex) -> Complex {
		Complex::new(self.real * other.real - self.imag * other.imag,
					 self.real * other.imag + self.imag * other.real)
	}
	fn div(&self, other: &Complex) -> Complex {
		Complex::new((self.real * other.real + self.imag * other.imag) /
					   (other.real * other.real + other.imag * other.imag),
					 (self.imag * other.real - self.real * other.imag) /
					   (other.real * other.real + other.imag * other.imag))
	}
}

// The behavior of this implementation is somewhat weird as it takes ownership of the original
// variables, meaning that they cannot be used afterward. It is possible to either implement 
// this for references (but then we need to write &a + &b) or to implement copy trait, which
// seems a little bit weird to me.
impl std::ops::Add for Complex {
    type Output = Complex;

    fn add(self, other: Complex) -> Complex {
        Complex {real: self.real + other.real, imag: self.imag + other.imag}
    }
}

impl std::fmt::Display for Complex {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}{:+}i", self.real, self.imag)
    }
}


fn main() {
	let mut a = Complex::new(3.0, 4.0);
	a.print();
	println!("{:?}", a.abs());
	println!("{:?}", a.real);

	a.real = 10.0;
	a.print();

	let b = Complex::from_complex(&a);
	b.print();

	a.imag = 6.0;
	a.print();
	b.print();

	let c = a.add(&b);
	c.print();

	println!("");
	a.print();
	b.print();

	let sub = a.sub(&b);
	let mul = a.mul(&b);
	let div = a.div(&b);
	println!("Sub: {}   Mul: {}   Div: {}", sub, mul, div);
}
