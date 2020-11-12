//! The Enum and Bounded classes.

#![allow(unused_macros)]

use std::char;
use std::{f32, f64};
use std::{i16, i32, i64, i8, isize};
use std::{u16, u32, u64, u8, usize};

#[cfg(has_i128)]
use std::{i128, u128};

use std::cmp::Ordering;
use std::convert::TryFrom;
use std::num::Wrapping;

/// The Bounded class names the upper and lower limits of a type.
pub trait Bounded {
    /// Upper limits of a type.
    fn min_bound() -> Self;
    /// Lower limits of a type.
    fn max_bound() -> Self;
}

impl Bounded for char {
    fn min_bound() -> Self {
        0 as char
    }

    fn max_bound() -> Self {
        char::MAX
    }
}

impl Bounded for Ordering {
    fn min_bound() -> Self {
        Ordering::Less
    }

    fn max_bound() -> Self {
        Ordering::Greater
    }
}

macro_rules! bounded_impl {
    ($($t:ty, $min:expr, $max:expr),+) => {
        $(
            impl Bounded for $t {
                #[inline]
                fn min_bound() -> $t {
                    $min
                }
                #[inline]
                fn max_bound() -> $t {
                    $max
                }
            }
        )+
    };
}

bounded_impl! { bool, false, true }
bounded_impl! { i8, i8::MIN, i8::MAX, u8, u8::MIN, u8::MAX }
bounded_impl! { i16, i16::MIN, i16::MAX, u16, u16::MIN, u16::MAX }
bounded_impl! { i32, i32::MIN, i32::MAX, u32, u32::MIN, u32::MAX }
bounded_impl! { i64, i64::MIN, i64::MAX, u64, u64::MIN, u64::MAX }
bounded_impl! { f32, f32::MIN, f32::MAX, f64, f64::MIN, f64::MAX }
bounded_impl! { isize, isize::MIN, isize::MAX, usize, usize::MIN, usize::MAX }
#[cfg(has_i128)]
bounded_impl! { i128, i128::MIN, i128::MAX, u128, u128::MIN, u128::MAX }

impl<T> Bounded for Wrapping<T>
where
    T: Bounded,
{
    fn min_bound() -> Self {
        Wrapping(T::min_bound())
    }

    fn max_bound() -> Self {
        Wrapping(T::max_bound())
    }
}

macro_rules! apply_for_each_tuple_recursively {
    ($macro:ident !!) => (
        $macro! { }
    );

    ($macro:ident !! $head:ident, $($tail:ident,)*) => (
        $macro! { $head $($tail)* }
        apply_for_each_tuple_recursively! { $macro !! $($tail,)* }
    );
}

macro_rules! impl_bounded_tuples {
    ($macro:ident) => {
        apply_for_each_tuple_recursively! { $macro !! A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, }
    };
}

macro_rules! impl_bounded_tuple {
    ($($name:ident)*) => (
        impl<$($name: Bounded,)*> Bounded for ($($name,)*) {
            #[inline]
            fn min_bound() -> Self {
                ($($name::min_bound(),)*)
            }
            #[inline]
            fn max_bound() -> Self {
                ($($name::max_bound(),)*)
            }
        }
    );
}

impl_bounded_tuples! { impl_bounded_tuple }

#[cfg(test)]
mod tests {

    use super::Bounded;
    use std::num::Wrapping;

    #[test]
    fn wrapping_bounded() {
        macro_rules! test_wrapping_bounded {
            ($($t:ty)+) => {
                $(
                    assert_eq!(<Wrapping<$t> as Bounded>::min_bound().0, <$t>::min_bound());
                    assert_eq!(<Wrapping<$t> as Bounded>::max_bound().0, <$t>::max_bound());
                )+
            };
        }
        test_wrapping_bounded!(usize u8 u16 u32 u64 isize i8 i16 i32 i64);
    }

    #[test]
    fn wrapping_is_bounded() {
        fn require_bounded<T: Bounded>(_: &T) {}
        require_bounded(&Wrapping(128_u32));
        require_bounded(&Wrapping(-128_i32));
    }
}
