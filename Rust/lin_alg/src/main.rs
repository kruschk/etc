extern crate num;

use num::Zero;
use std::ops::{AddAssign, Mul};

fn dot_product<T>(a: &Vec<T>, b: &Vec<T>) -> Result<T, ()>
    where T: AddAssign<<T as Mul>::Output> + Copy + Mul + Zero
{
    if a.len() != b.len() || a.len() == 0 {
        Err(())
    }
    else {
        let mut result = num::zero();
        for (&x, &y) in a.iter().zip(b.iter()) {
            result += x*y;
        }
        Ok(result)
    }
}

fn main() {
    let a = vec![0, 1, 2];
    let b = vec![3, 4, 5];
    let c = vec![6.0, 7.1, 8.2];
    let d = vec![9.9, -9.9, -8.8];
    println!("{}", dot_product(&a, &b).unwrap());
    println!("{}", dot_product(&c, &d).unwrap());
}
