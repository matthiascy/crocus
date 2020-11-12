//! Basic numeric class

use std::cmp::Ordering;
use std::num::Wrapping;

use std::ops::{Add, AddAssign, Div, DivAssign, Mul, MulAssign, Rem, RemAssign, Sub, SubAssign};

use std::{f32, f64};
use std::{i16, i32, i64, i8, isize};
use std::{u16, u32, u64, u8, usize};

#[cfg(has_i128)]
use std::{i128, u128};

use crate::core::identity::{One, Zero};

/// The Num class provides basic numeric operations.
pub trait Num<Rhs = Self, Output = Self>:
    Sized
    + Zero
    + One
    + PartialEq
    + PartialOrd
    + Copy
    + Clone
    + Add<Rhs, Output = Output>
    + AddAssign<Rhs>
    + Sub<Rhs, Output = Output>
    + SubAssign<Rhs>
    + Mul<Rhs, Output = Output>
    + MulAssign<Rhs>
    + Div<Rhs, Output = Output>
    + DivAssign<Rhs>
    + Rem<Rhs, Output = Output>
    + RemAssign<Rhs>
{
    fn negate(self) -> Self;
    fn signum(self) -> Self;
}

macro_rules! impl_num_signed {
    ($($t:ty)*) => {$(
        impl Num for $t {
            #[inline]
            fn negate(self) -> Self {
                -self
            }

            #[inline]
            fn signum(self) -> Self {
                if self == 0 as $t {
                    0 as $t
                } else if self > 0 as $t {
                    1 as $t
                } else {
                    -1 as $t
                }
            }
        }
    )*}
}

macro_rules! impl_num_float {
    ($($t:ty)*) => {$(
        impl Num for $t {
            #[inline]
            fn negate(self) -> Self {
                -self
            }

            #[inline]
            fn signum(self) -> Self {
                if self.is_nan() {
                    <$t>::NAN
                } else if (self - 0.0 as $t).abs() <= <$t>::EPSILON {
                    0.0 as $t
                } else if self > 0.0 as $t {
                    1 as $t
                } else {
                    -1 as $t
                }
            }
        }
    )*}
}

macro_rules! impl_num_unsigned {
    ($($t:ty)*) => {$(
        impl Num for $t {
            #[inline]
            fn negate(self) -> Self {
                panic!("Trying to negate unsigned number!");
            }

            #[inline]
            fn signum(self) -> Self {
                if self == 0 as $t {
                    0 as $t
                } else {
                    1 as $t
                }
            }
        }
    )*}
}

impl_num_signed! { i8 i16 i32 i64 isize }

impl_num_unsigned! { u8 u16 u32 u64 usize }

impl_num_float! { f32 f64 }

#[cfg(has_i128)]
impl_num_signed! { i128 }

#[cfg(has_i128)]
impl_num_unsigned! { u128 }

#[cfg(test)]
mod tests {
    use super::Num;

    macro_rules! negate_signed_number_tests {
        ($($func: ident $t:ty)*) => {$(
            #[test]
            fn $func() {
                assert_eq!(0 as $t, (123 as $t).negate() + (-123 as $t).negate());
            }
        )*}
    }

    macro_rules! sign_of_signed_number_tests {
        ($($func: ident $t:ty)*) => {$(
            #[test]
            fn $func() {
                assert_eq!(0 as $t, <$t as Num>::signum(0 as $t));
                assert_eq!(1 as $t, <$t as Num>::signum(123 as $t));
                assert_eq!(-1 as $t, <$t as Num>::signum(-123 as $t));
            }
        )*}
    }

    negate_signed_number_tests!(negate_i8 i8 negate_i16 i16 negate_i32 i32 negate_i64 i64 negate_f32 f32 negate_f64 f64 negate_isize isize);
    sign_of_signed_number_tests!(sign_of_i8 i8 sign_of_i16 i16 sign_of_i32 i32 sign_of_i64 i64 sign_of_f32 f32 sign_of_f64 f64 sign_of_isize isize);

    #[test]
    fn sign_of_nan() {
        assert!(<f32 as Num>::signum(f32::NAN).is_nan());
        assert!(<f64 as Num>::signum(f64::NAN).is_nan());
    }

    #[cfg(has_i128)]
    negate_signed_number_tests!(negate_i128 i128);

    #[cfg(has_i128)]
    sign_of_signed_number_tests!(sign_of_i128 i128);

    macro_rules! negate_unsigned_number_tests {
        ($($func: ident $t:ty)*) => {$(
            #[test]
            #[should_panic]
            fn $func() {
                (123 as $t).negate();
            }
        )*}
    }

    macro_rules! sign_of_unsigned_number_tests {
        ($($func: ident $t:ty)*) => {$(
            #[test]
            fn $func() {
                assert_eq!(0 as $t, (0 as $t).signum());
                assert_eq!(1 as $t, (123 as $t).signum());
            }
        )*}
    }

    #[test]
    fn abc() {
        println!("sign of 0.0 is {}", 0.0_f32.signum());
    }

    negate_unsigned_number_tests!(negate_u8 u8 negate_u16 u16 negate_u32 u32 negate_u64 u64 negate_usize usize);
    sign_of_unsigned_number_tests!(sign_of_u8 u8 sign_of_u16 u16 sign_of_u32 u32 sign_of_u64 u64 sign_of_usize usize);

    #[cfg(has_i128)]
    negate_unsigned_number_tests!(negate_u128 u128);

    #[cfg(has_i128)]
    sign_of_signed_number_tests!(sign_of_u128 u128);
}
