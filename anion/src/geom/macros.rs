// TODO: reduce redundancy of macro implementation
macro_rules! impl_vector_neg {
  ($Vec:ident, { $($field:ident),+ }) => {
      impl<T: Num + std::ops::Neg<Output=T>> std::ops::Neg for $Vec<T> {
          type Output = $Vec<T>;

          #[inline]
          fn neg(self) -> Self::Output {
              $Vec::new( $(-self.$field),+ )
          }
      }

      impl<'a, T: Num + std::ops::Neg<Output=T>> std::ops::Neg for &'a $Vec<T> {
          type Output = $Vec<T>;

          #[inline]
          fn neg(self) -> Self::Output {
              $Vec::new( $(-self.$field),+ )
          }
      }
  }
}

macro_rules! impl_vector_add {
    ($Vec:ident, { $($field:ident),+ }) => {
        impl<T: Num> std::ops::Add<$Vec<T>> for $Vec<T> {
             type Output = $Vec<T>;

             fn add(self, rhs: Self) -> Self::Output {
                 $Vec::new( $(self.$field + rhs.$field),+ )
             }
        }

        impl<'a, T: Num> std::ops::Add<&'a $Vec<T>> for $Vec<T> {
             type Output = $Vec<T>;

             fn add(self, rhs: &'a $Vec<T>) -> Self::Output {
                 $Vec::new( $(self.$field + rhs.$field),+ )
             }
        }

        impl<'a, T: Num> std::ops::Add<$Vec<T>> for &'a $Vec<T> {
             type Output = $Vec<T>;

             fn add(self, rhs: $Vec<T>) -> Self::Output {
                 $Vec::new( $(self.$field + rhs.$field),+ )
             }
        }

        impl<'a, 'b, T: Num> std::ops::Add<&'b $Vec<T>> for &'a $Vec<T> {
             type Output = $Vec<T>;

             fn add(self, rhs: &'b $Vec<T>) -> Self::Output {
                 $Vec::new( $(self.$field + rhs.$field),+ )
             }
        }
    }
}

macro_rules! impl_vector_add_assign {
    ($Vec:ident, { $($field:ident),+ }) => {
        impl<T: Num> std::ops::AddAssign<$Vec<T>> for $Vec<T> {
             fn add_assign(&mut self, rhs: Self) {
                 $(self.$field += rhs.$field);+;
             }
        }

        impl<'a, T: Num> std::ops::AddAssign<&'a $Vec<T>> for $Vec<T> {
             fn add_assign(&mut self, rhs: &'a $Vec<T>) {
                 $(self.$field += rhs.$field);+;
             }
        }
    }
}

macro_rules! impl_vector_sub {
    ($Vec:ident, { $($field:ident),+ }) => {
        impl<T: Num> std::ops::Sub<$Vec<T>> for $Vec<T> {
             type Output = $Vec<T>;

             fn sub(self, rhs: Self) -> Self::Output {
                 $Vec::new( $(self.$field - rhs.$field),+ )
             }
        }

        impl<'a, T: Num> std::ops::Sub<&'a $Vec<T>> for $Vec<T> {
             type Output = $Vec<T>;

             fn sub(self, rhs: &'a $Vec<T>) -> Self::Output {
                 $Vec::new( $(self.$field - rhs.$field),+ )
             }
        }

        impl<'a, T: Num> std::ops::Sub<$Vec<T>> for &'a $Vec<T> {
             type Output = $Vec<T>;

             fn sub(self, rhs: $Vec<T>) -> Self::Output {
                 $Vec::new( $(self.$field - rhs.$field),+ )
             }
        }

        impl<'a, 'b, T: Num> std::ops::Sub<&'b $Vec<T>> for &'a $Vec<T> {
             type Output = $Vec<T>;

             fn sub(self, rhs: &'b $Vec<T>) -> Self::Output {
                 $Vec::new( $(self.$field - rhs.$field),+ )
             }
        }
    }
}

macro_rules! impl_vector_sub_assign {
    ($Vec:ident, { $($field:ident),+ }) => {
        impl<T: Num> std::ops::SubAssign<$Vec<T>> for $Vec<T> {
             fn sub_assign(&mut self, rhs: Self) {
                 $(self.$field -= rhs.$field);+;
             }
        }

        impl<'a, T: Num> std::ops::SubAssign<&'a $Vec<T>> for $Vec<T> {
             fn sub_assign(&mut self, rhs: &'a $Vec<T>) {
                 $(self.$field -= rhs.$field);+;
             }
        }
    }
}

macro_rules! impl_vector_mul {
    ($Vec:ident, { $($field:ident),+ }) => {
        impl<T: Num> std::ops::Mul<T> for $Vec<T> {
            type Output = $Vec<T>;

            fn mul(self, rhs: T) -> Self::Output {
                $Vec::new( $(self.$field * rhs),+ )
            }
        }

        impl_scalar_vector_mul!($Vec, i8, {$($field),+});
        impl_scalar_vector_mul!($Vec, u8, {$($field),+});
        impl_scalar_vector_mul!($Vec, i16, {$($field),+});
        impl_scalar_vector_mul!($Vec, u16, {$($field),+});
        impl_scalar_vector_mul!($Vec, i32, {$($field),+});
        impl_scalar_vector_mul!($Vec, u32, {$($field),+});
        impl_scalar_vector_mul!($Vec, i64, {$($field),+});
        impl_scalar_vector_mul!($Vec, u64, {$($field),+});
        impl_scalar_vector_mul!($Vec, f32, {$($field),+});
        impl_scalar_vector_mul!($Vec, f64, {$($field),+});

        #[cfg(has_i128)]
        impl_scalar_vector_mul!($Vec, i128, {$($field),+});

        #[cfg(has_i128)]
        impl_scalar_vector_mul!($Vec, u128, {$($field),+});
    };
}

// TODO: nested repetition
macro_rules! impl_scalar_vector_mul {
    ($Vec:ident, $t:ty, {$($field:ident),+}) => {
        impl std::ops::Mul<$Vec<$t>> for $t {
            type Output = $Vec<$t>;

            fn mul(self, rhs: $Vec<$t>) -> Self::Output {
                $Vec::new($(rhs.$field * self),+)
            }
        }
    };
}

macro_rules! impl_vector_div {
    ($Vec:ident, {$($field:ident),+}) => {
        impl<T: Num> std::ops::Div<T> for $Vec<T> {
            type Output = $Vec<T>;

            fn div(self, rhs: T) -> Self::Output {
                $Vec::new( $(self.$field / rhs),+ )
            }
        }
    };
}

macro_rules! impl_vector_ops {
    ($Vec:ident, {$($field:ident),+}) => {
        impl_vector_neg!($Vec, {$($field),+});
        impl_vector_add!($Vec, {$($field),+});
        impl_vector_sub!($Vec, {$($field),+});
        impl_vector_mul!($Vec, {$($field),+});
        impl_vector_div!($Vec, {$($field),+});
        impl_vector_add_assign!($Vec, {$($field),+});
        impl_vector_sub_assign!($Vec, {$($field),+});
    };
}

/// approx crate needed.
macro_rules! impl_vector_approx {
    ($Vec:ident, {$($field:ident),+}) => {
        impl<T: Floating> approx::AbsDiffEq for $Vec<T> {
            type Epsilon = T::Epsilon;

            #[inline]
            fn default_epsilon() -> Self::Epsilon {
                T::default_epsilon()
            }

            #[inline]
            fn abs_diff_eq(&self, other: &Self, epsilon: T::Epsilon) -> bool {
                $(T::abs_diff_eq(&self.$field, &other.$field, epsilon))&&+
            }
        }

        impl<T: Floating> approx::RelativeEq for $Vec<T> {
            #[inline]
            fn default_max_relative() -> T::Epsilon {
                T::default_max_relative()
            }

            #[inline]
            fn relative_eq(&self, other: &Self, epsilon: T::Epsilon, max_relative: T::Epsilon) -> bool {
                $(T::relative_eq(&self.$field, &other.$field, epsilon, max_relative))&&+
            }
        }

        impl<T: Floating> approx::UlpsEq for $Vec<T> {
            #[inline]
            fn default_max_ulps() -> u32 {
                T::default_max_ulps()
            }

            #[inline]
            fn ulps_eq(&self, other: &Self, epsilon: T::Epsilon, max_ulps: u32) -> bool {
                $(T::ulps_eq(&self.$field, &other.$field, epsilon, max_ulps))&&+
            }
        }
    };
}

macro_rules! impl_vector_random {
    ($Vec:ident, {$($field:ident),+}) => {
        #[cfg(feature = "rand")]
        impl<T: Num> Distribution<$Vec<T>> for Standard {
            fn sample<R: Rng + ?Sized>(&self, rng: &mut R) -> $Vec<T> {
                $Vec { $($field: rng.gen()),+ }
            }
        }
    }
}
