use std::num::Wrapping;

use std::{f32, f64};
use std::{i16, i32, i64, i8, isize};
use std::{u16, u32, u64, u8, usize};

#[cfg(has_i128)]
use std::{i128, u128};

/// Definition of additive identity.
/// ```text
/// x + 0 = x for all x ∈ 𝑭ⁿ
/// ```
pub trait Zero: Sized {
    /// Returns additive identity of type `Self`.
    fn zero() -> Self;

    /// Returns `true` if `self` is equal to the additive identity.
    fn is_zero(&self) -> bool;

    /// Sets `self` to the additive identity of type `Self`.
    fn set_to_zero(&mut self) {
        *self = Zero::zero();
    }
}

macro_rules! impl_zero {
    ($($t:ty)*, $val:expr) => {$(
        impl Zero for $t {
            #[inline]
            fn zero() -> $t {
                $val
            }

            #[inline]
            fn is_zero(&self) -> bool
                where Self: PartialEq
            {
                *self == $val
            }
        }
    )*};
}

impl_zero!(u8 i8 u16 i16 u32 i32 u64 i64 usize isize, 0);
impl_zero!(f32 f64, 0.0);

#[cfg(has_i128)]
impl_zero!(u128 i128, 0);

impl<T: Zero> Zero for Wrapping<T> {
    fn zero() -> Self {
        Wrapping(T::zero())
    }

    fn is_zero(&self) -> bool {
        self.0.is_zero()
    }

    fn set_to_zero(&mut self) {
        self.0.set_to_zero();
    }
}

/// Definition of multiplicative identity.
/// ```text
/// x * 1 = x for all x ∈ 𝑭ⁿ
/// ```
pub trait One: Sized {
    /// Returns multiplicative identity of type `Self`.
    fn one() -> Self;

    /// Sets `self` to the multiplicative identity.
    fn set_to_one(&mut self) {
        *self = One::one();
    }

    /// Returns `true` if `self` equals to the multiplicative identity.
    #[inline]
    fn is_one(&self) -> bool
    where
        Self: PartialEq,
    {
        *self == Self::one()
    }
}

macro_rules! impl_one {
    ($($t:ty)+, $val:expr) => {$(
        impl One for $t {
            #[inline]
            fn one() -> $t {
                $val
            }

            #[inline]
            fn is_one(&self) -> bool {
                *self == $val
            }
        }
    )+};
}

impl_one!(u8 i8 u16 i16 u32 i32 u64 i64 usize isize, 1);
impl_one!(f32 f64, 1.0);

#[cfg(has_i128)]
impl_one!(u128 i128, 1);

#[inline(always)]
pub fn zero<T: Zero>() -> T {
    Zero::zero()
}

#[inline(always)]
pub fn one<T: One>() -> T {
    One::one()
}

impl<T: One> One for Wrapping<T> {
    fn one() -> Self {
        Wrapping(T::one())
    }

    fn set_to_one(&mut self) {
        self.0.set_to_one();
    }
}

#[test]
fn wrapping_number_identity() {
    macro_rules! test_wrapping_identity {
        ($($t:ty)+) => {$(
            assert_eq!(zero::<$t>(), zero::<Wrapping<$t>>().0);
            assert_eq!(one::<$t>(), one::<Wrapping<$t>>().0);
            assert_eq!((0 as $t).is_zero(), Wrapping(0 as $t).is_zero());
            assert_eq!((1 as $t).is_zero(), Wrapping(1 as $t).is_zero());
        )+}
    }

    test_wrapping_identity!(isize usize i8 u8 i16 u16 i32 u32 i64 u64);
}
