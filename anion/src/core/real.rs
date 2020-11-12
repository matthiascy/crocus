use crate::core::Num;
use std::ops::{Div, DivAssign, Rem, RemAssign};

use std::{f32, f64};
use std::{i16, i32, i64, i8, isize};
use std::{u16, u32, u64, u8, usize};

#[cfg(has_i128)]
use std::{i128, u128};

/// Fractional numbers, supporting real division
pub trait Fractional<Rhs = Self, Output = Self>:
    Div<Rhs, Output = Output>
    + DivAssign<Rhs>
    + Num<Rhs, Output>
    + approx::AbsDiffEq<Epsilon = Self>
    + approx::RelativeEq<Epsilon = Self>
    + approx::UlpsEq<Epsilon = Self>
{
    fn recip(self) -> Self;
}

macro_rules! impl_fractional {
    ($($t:ty)*) => {$(
        impl Fractional for $t {
            fn recip(self) -> Self {
                1.0 as $t / self
            }
        }
    )*}
}

impl_fractional!(f32 f64);

/// Integral numbers, supporting integer division.
pub trait Integral<Rhs = Self, Output = Self>:
    Num<Rhs, Output> + Rem<Rhs> + RemAssign<Rhs>
{
    fn quot(self, rhs: Self) -> Self;
    fn rem(self, rhs: Self) -> Self;
    fn div(self, rhs: Self) -> Self;
    fn modulo(self, rhs: Self) -> Self;
    fn quot_rem(self, rhs: Self) -> (Self, Self);
    fn div_mod(self, rhs: Self) -> (Self, Self);
}

macro_rules! impl_integral {
    ($($t:ty)*) => {$(
        impl Integral for $t {
            #[inline]
            fn quot(self, rhs: Self) -> Self {
                <Self as Div>::div(self, rhs)
            }

            #[inline]
            fn rem(self, rhs: Self) -> Self {
                <Self as Rem>::rem(self, rhs)
            }

            #[inline]
            fn div(self, rhs: Self) -> Self {
                <Self as Div>::div(self, rhs)
            }

            #[inline]
            fn modulo(self, rhs: Self) -> Self {
                <Self as Rem>::rem(self, rhs)
            }

            #[inline]
            fn quot_rem(self, rhs: Self) -> (Self, Self) {
                (<Self as Div>::div(self, rhs), <Self as Rem>::rem(self, rhs))
            }

            #[inline]
            fn div_mod(self, rhs: Self) -> (Self, Self) {
                (<Self as Div>::div(self, rhs), <Self as Rem>::rem(self, rhs))
            }
        }
    )*}
}

impl_integral! { i8 u8 i16 u16 i32 u32 i64 u64 isize usize }

#[cfg(has_i128)]
impl_integral! { i128 u128 }

/// Floating number supports trigonometric and hyperbolic functions and related functions.
pub trait Floating<Rhs = Self, Output = Self>: Fractional {
    fn nan() -> Self;
    fn inf() -> Self;
    fn inf_neg() -> Self;
    fn pi() -> Self;
    fn epsilon() -> Self;
    fn e() -> Self;
    fn frac_1_pi() -> Self;
    fn frac_1_sqrt_2() -> Self;
    fn frac_2_pi() -> Self;
    fn frac_2_sqrt_pi() -> Self;
    fn frac_pi_2() -> Self;
    fn frac_pi_3() -> Self;
    fn frac_pi_4() -> Self;
    fn frac_pi_6() -> Self;
    fn frac_pi_8() -> Self;
    fn ln_2() -> Self;
    fn ln_10() -> Self;
    fn log2_10() -> Self;
    fn log2_e() -> Self;
    fn log10_2() -> Self;
    fn log10_e() -> Self;
    fn sqrt2() -> Self;
}

macro_rules! impl_method {
    ($($method:ident () -> $ret:expr;)*) => {$(
        #[inline]
        fn $method() -> Self {
            $ret
        }
    )*};
}

macro_rules! impl_floating {
    ($($t:ty, $p:path),*) => {$(
        impl Floating for $t {
            impl_method! {
                nan() -> <$t>::NAN;
                inf() -> <$t>::INFINITY;
                inf_neg() -> <$t>::NEG_INFINITY;
                epsilon() -> <$t>::EPSILON;
                pi() -> { use $p as base; base::PI };
                e() -> { use $p as base; base::E };
                frac_1_pi() -> { use $p as base; base::FRAC_1_PI };
                frac_1_sqrt_2() -> { use $p as base; base::FRAC_1_SQRT_2 };
                frac_2_pi() -> { use $p as base; base::FRAC_2_PI };
                frac_2_sqrt_pi() -> {use $p as base; base::FRAC_2_SQRT_PI };
                frac_pi_2() -> { use $p as base; base::FRAC_PI_2 };
                frac_pi_3() -> { use $p as base; base::FRAC_PI_3 };
                frac_pi_4() -> { use $p as base; base::FRAC_PI_4 };
                frac_pi_6() -> { use $p as base; base::FRAC_PI_6 };
                frac_pi_8() -> { use $p as base; base::FRAC_PI_8 };
                ln_2() -> { use $p as base; base::LN_2 };
                ln_10() -> { use $p as base; base::LN_10 };
                log2_10() -> { use $p as base; base::LOG2_10 };
                log2_e() -> { use $p as base; base::LOG2_E };
                log10_2() -> { use $p as base; base::LOG10_2 };
                log10_e() -> { use $p as base; base::LOG10_E };
                sqrt2() -> { use $p as base; base::SQRT_2 };
           }
        }
    )*}
}

impl_floating! { f32, std::f32::consts, f64, std::f64::consts }

#[cfg(test)]
mod tests {
    use super::{Floating, Integral};

    #[test]
    fn floating_tests() {
        macro_rules! floating_func_tests {
            ($($t:ty, $p:path),*) => {$(
                {
                    use $p as base;
                    assert!(<$t as Floating>::nan().is_nan());
                    assert!(<$t as Floating>::inf().is_infinite());
                    assert_eq!(<$t as Floating>::inf_neg(), <$t>::NEG_INFINITY);
                    assert_eq!(<$t as Floating>::epsilon(), <$t>::EPSILON);
                    assert_eq!(<$t as Floating>::pi(), base::PI);
                    assert_eq!(<$t as Floating>::e(), base::E);
                    assert_eq!(<$t as Floating>::frac_1_pi(), base::FRAC_1_PI);
                    assert_eq!(<$t as Floating>::frac_1_sqrt_2(), base::FRAC_1_SQRT_2);
                    assert_eq!(<$t as Floating>::frac_2_pi(), base::FRAC_2_PI);
                    assert_eq!(<$t as Floating>::frac_2_sqrt_pi(), base::FRAC_2_SQRT_PI);
                    assert_eq!(<$t as Floating>::frac_pi_2(), base::FRAC_PI_2);
                    assert_eq!(<$t as Floating>::frac_pi_3(), base::FRAC_PI_3);
                    assert_eq!(<$t as Floating>::frac_pi_4(), base::FRAC_PI_4);
                    assert_eq!(<$t as Floating>::frac_pi_6(), base::FRAC_PI_6);
                    assert_eq!(<$t as Floating>::frac_pi_8(), base::FRAC_PI_8);
                    assert_eq!(<$t as Floating>::ln_2(), base::LN_2);
                    assert_eq!(<$t as Floating>::ln_10(), base::LN_10);
                    assert_eq!(<$t as Floating>::log2_10(), base::LOG2_10);
                    assert_eq!(<$t as Floating>::log2_e(), base::LOG2_E);
                    assert_eq!(<$t as Floating>::log10_2(), base::LOG10_2);
                    assert_eq!(<$t as Floating>::log10_e(), base::LOG10_E);
                    assert_eq!(<$t as Floating>::sqrt2(), base::SQRT_2);
                }
            )*};
        }

        floating_func_tests! { f32, std::f32::consts, f64, std::f64::consts }
    }

    #[test]
    fn integral_tests() {
        macro_rules! integral_func_tests {
            ($($t:ty)*) => {$(
                let quot = <$t as Integral>::quot(11, 3);
                let div = <$t as Integral>::div(11, 3);

                let rem = <$t as Integral>::rem(11, 3);
                let modulo = <$t as Integral>::modulo(11, 3);

                let quot_rem = <$t as Integral>::quot_rem(11, 3);
                let div_mod = <$t as Integral>::div_mod(11, 3);

                assert_eq!(quot, 3);
                assert_eq!(div, quot);
                assert_eq!(rem, 2);
                assert_eq!(rem, modulo);
                assert_eq!(quot_rem, div_mod);
            )*};
        }

        integral_func_tests! { i8 u8 i16 u16 i32 u32 i64 u64 isize usize }

        #[cfg(has_i128)]
        integral_func_tests! { u128 i128 }
    }
}
