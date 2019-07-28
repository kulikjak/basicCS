
fn day_name(day: i32) {
  match day {
    1 => println!("Monday"),
    2 => println!("Tuesday"),
    3 => println!("Wednesday"),
    4 => println!("Thursday"),
    5 => println!("Friday"),
    6 => println!("Saturday"),
    7 => println!("Sunday"),
    _ => println!("error - today is no day!!!")
  }
}

fn check_leap_year(year: i32) {
  if year < 1584 {
    println!("There were no leap years before 1584...");
  } else if year % 400 == 0 {
    println!("{} is a leap year (divisible by 400)", year);
  } else if year % 100 == 0 {
    println!("{} is not a leap year (divisible by 100)", year);
  } else if year % 4 == 0 {
    println!("{} is a leap year (divisible by 4)", year);
  } else {
    println!("{} is not a leap year.", year);
  }
}

fn print_interval(a: i32, b: i32) {
	for i in a .. b + 1 {
    print!("{} ", i);
	}
  println!("");
}

fn print_even_interval(a: i32, b: i32) {
	for i in a .. b + 1 {
		if i % 2 == 0 {
    	print!("{} ", i);
    }
	}
  println!("");
}

fn print_odd_interval(a: i32, b: i32) {
	for i in a .. b + 1 {
		if i % 2 == 1 {
    	print!("{} ", i);
    }
	}
  println!("");
}

/* Vypisuje cisla v intervalu delitelna zadanym faktorem */
fn print_interval_with_factor(a: i32, b: i32, factor: i32) {
	for i in a .. b + 1 {
		if i % factor == 0 {
    	print!("{} ", i);
    }
	}
  println!("");
}

fn print_interval_with_factor2(a: i32, b: i32, factor: i32) {
  for i in a .. b + 1 {
  	if i % factor == 0 {
  		for j in (i .. b + 1).step_by(factor as usize) {
  			print!("{} ", j);
  		}
  		break;
  	}
  }
  println!("");
}

fn check_triangle(a: f64, b: f64, c: f64) {
  println!("Strana a: {}", a);
  println!("Strana b: {}", b);
  println!("Strana c: {}", c);

  if ((a + b) <= c) || ((c + b) <= a) || ((a + c) <= b) {
    println!("trojuhelnik nelze sestrojit");
  } else {
    println!("trojuhelnik lze sestrojit");
  }

  if (a == b) && (b == c) {
    println!("trojuhelnik je rovnostranny");
  } else {
    println!("trojuhelnik neni rovnostranny");
  }

  if ((a == b) && a != c) || ((c == b) && c != a) || ((a == c) && a != b) {
    println!("trojuhelnik je rovnoramenny");
  } else {
    println!("trojuhelnik neni rovnoramenny");
  }

  if (a * a + b * b == c * c) || (a * a + c * c == b * b) || (c * c + b * b == a * a) {
    println!("trojuhelnik je pravouhly");
  } else {
    println!("trojuhelnik neni pravouhly");
  }
}

fn print_triangle(size: i32) {
  for i in 1 .. size + 1 {
  	for _j in 1 .. i + 1 {
  		print!("*");
  	}
  	println!("");
  }
}

fn intersection_of_intervals(a1: i32, a2: i32, b1: i32, b2: i32) {
  if a1 < b1 {
    if a2 > b1 {
      print!("<{},", b1);
    } else {
      print!("<0,0>");
      return;
    }
  }
  if b1 < a1 {
    if b2 > a1 {
      print!("<{},", a1);
    } else {
      print!("<0,0>");
      return;
    }
  }
  if a2 > b2 {
    if a1 < b2 {
      print!("{}>", b2);
    } else {
      print!("<0,0>");
      return;
    }
  }
  if b2 > a2 {
    if b1 < a2 {
      print!("{}>", a2);
    } else {
      print!("<0,0>");
      return;
    }
  }
  println!("");
}

fn main() {
  day_name(3);
  day_name(6);
  day_name(8);

  println!("");

  check_leap_year(2000);
  check_leap_year(2004);
  check_leap_year(2005);

  println!("");

  print_interval(6, 18);
  print_even_interval(2, 21);
  print_odd_interval(2, 21);
  print_interval_with_factor(23, 84, 7);
  print_interval_with_factor2(23, 84, 7);

  println!("");

  check_triangle(4.0, 7.0, 6.0);

  println!("");

  print_triangle(8);

  println!("");
  intersection_of_intervals(1, 20, 12, 19);
}
