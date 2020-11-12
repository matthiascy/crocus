use crate::core::{
    Bounded, EuclideanSpace, Floating, InnerProductSpace, Num, One, VectorSpace, Zero,
};
#[cfg(feature = "rand")]
use rand::{distributions::{Distribution, Standard}, Rng};

#[repr(C)]
#[derive(PartialEq, Eq, Debug, Copy, Clone)]
pub struct Vector2<T: Num> {
    pub x: T,
    pub y: T,
}

#[repr(C)]
#[derive(PartialEq, Eq, Debug, Copy, Clone)]
pub struct Vector3<T: Num> {
    pub x: T,
    pub y: T,
    pub z: T,
}

#[repr(C)]
#[derive(PartialEq, Eq, Debug, Copy, Clone)]
pub struct Vector4<T: Num> {
    pub x: T,
    pub y: T,
    pub z: T,
    pub w: T,
}

macro_rules! impl_vector {
    ($Vec:ident, { $($field:ident),+ }, $constructor:ident, $n:expr) => {
        impl<T: Num> $Vec<T> {
            #[inline]
            pub fn new( $($field: T),+ ) -> $Vec<T> {
                $Vec { $($field: $field),+ }
            }

            #[inline]
            pub fn fill(a: T) -> $Vec<T> {
                $Vec { $($field: a),+ }
            }
        }

        #[inline]
        pub fn $constructor<T: Num>( $($field: T),+ ) -> $Vec<T> {
            $Vec::new($($field),+)
        }

        impl<T: Num> Zero for $Vec<T> {
            #[inline]
            fn zero() -> $Vec<T> {
                $Vec::fill(<T as Zero>::zero())
            }

            #[inline]
            fn is_zero(&self) -> bool {
                *self == $Vec::zero()
            }
        }

        impl_vector_ops!($Vec, { $($field),+ });

        impl<T: Num + Bounded> Bounded for $Vec<T> {
            #[inline]
            fn min_bound() -> $Vec<T> {
                $Vec { $($field: T::min_bound()),+ }
            }

            #[inline]
            fn max_bound() -> $Vec<T> {
                $Vec { $($field: T::max_bound()),+ }
            }
        }

        impl_vector_approx!($Vec, { $($field),+ });

        impl_vector_random!($Vec, { $($field),+ });

        impl<T: Num> VectorSpace for $Vec<T> {
            type Scalar = T;

            #[inline]
            fn dim(&self) -> i32 {
                $n
            }
        }
    };
}

impl_vector!(Vector2, { x, y }, vec2, 2);
impl_vector!(Vector3, { x, y, z }, vec3, 3);
impl_vector!(Vector4, { x, y, z, w }, vec4, 4);

// Extra functions over Vector<T>s

impl<T: Num> Vector2<T> {
    #[inline]
    pub fn unit_x() -> Vector2<T> {
        Vector2::new(<T as One>::one(), <T as Zero>::zero())
    }

    #[inline]
    pub fn unit_y() -> Vector2<T> {
        Vector2::new(<T as Zero>::zero(), <T as One>::one())
    }

    /// The perpendicular dot product of two Vector2<T>s.
    #[inline]
    pub fn perp_dot(self, rhs: &Vector2<T>) -> T {
        (self.x * rhs.x) - (self.y * rhs.y)
    }
}

impl<T: Num> Vector3<T> {
    #[inline]
    pub fn unit_x() -> Vector3<T> {
        Vector3::new(<T as One>::one(), <T as Zero>::zero(), <T as Zero>::zero())
    }

    #[inline]
    pub fn unit_y() -> Vector3<T> {
        Vector3::new(<T as Zero>::zero(), <T as One>::one(), <T as Zero>::zero())
    }

    #[inline]
    pub fn unit_z() -> Vector3<T> {
        Vector3::new(<T as Zero>::zero(), <T as Zero>::zero(), <T as One>::one())
    }
}

impl<T: Num> Vector4<T> {
    #[inline]
    pub fn unit_x() -> Vector4<T> {
        Vector4::new(
            <T as One>::one(),
            <T as Zero>::zero(),
            <T as Zero>::zero(),
            <T as Zero>::zero(),
        )
    }

    #[inline]
    pub fn unit_y() -> Vector4<T> {
        Vector4::new(
            <T as Zero>::zero(),
            <T as One>::one(),
            <T as Zero>::zero(),
            <T as Zero>::zero(),
        )
    }

    #[inline]
    pub fn unit_z() -> Vector4<T> {
        Vector4::new(
            <T as Zero>::zero(),
            <T as Zero>::zero(),
            <T as One>::one(),
            <T as Zero>::zero(),
        )
    }

    #[inline]
    pub fn unit_w() -> Vector4<T> {
        Vector4::new(
            <T as Zero>::zero(),
            <T as Zero>::zero(),
            <T as Zero>::zero(),
            <T as One>::one(),
        )
    }
}

#[cfg(test)]
mod tests {
    use crate::core::Bounded;
    use crate::geom::vector::*;

    use crate::core::Num;
    use rand::distributions::{Distribution, Standard};
    use rand::Rng;

    /*
    macro_rules! impl_distribution {
        ($($t:ident),+) => {$(
            impl Distribution<Vector2<$t>> for Standard {
                fn sample<R: Rng + ?Sized>(&self, rng: &mut R) -> Vector2<$t> {
                    let (x, y) = rng.gen();
                    Vector2::new(x, y)
                }
            }

            impl Distribution<Vector3<$t>> for Standard {
                fn sample<R: Rng + ?Sized>(&self, rng: &mut R) -> Vector3<$t> {
                    let (x, y, z) = rng.gen();
                    Vector3::new(x, y, z)
                }
            }

            impl Distribution<Vector4<$t>> for Standard {
                fn sample<R: Rng + ?Sized>(&self, rng: &mut R) -> Vector4<$t> {
                    let (x, y, z, w) = rng.gen();
                    Vector4::new(x, y, z, w)
                }
            }
        )+}
    }

    impl_distribution!(i8, u8, i16, u16, i32, u32, i64, u64, f32, f64, isize, usize);

    #[cfg(has_i128)]
    impl_distribution!(i128, u128);
    */

    #[test]
    fn negation() {
        let mut rng = rand::thread_rng();

        macro_rules! generate_tests {
            ($($t:ty)*) => {$(
                let va: Vector2<$t> = rng.gen();
                let vb: Vector3<$t> = rng.gen();
                let vc: Vector4<$t> = rng.gen();
                assert_eq!(Vector2::new(-va.x, -va.y), -va);
                assert_eq!(Vector3::new(-vb.x, -vb.y, -vb.z), -vb);
                assert_eq!(Vector4::new(-vc.x, -vc.y, -vc.z, -vc.w), -vc);
            )*}
        }

        generate_tests!(i8 i16 i32 i64 f32 f64);

        #[cfg(has_i128)]
        generate_tests!(i128 u128);
    }

    #[test]
    fn add_and_assign() {
        let mut rng = rand::thread_rng();

        macro_rules! generate_tests {
            ($($t:ty)*) => {$(
                let min = <$t>::min_bound()/2 as $t;
                let max = <$t>::max_bound()/2 as $t;
                let a = rng.gen_range(min, max);
                let b = rng.gen_range(min, max);
                let c = rng.gen_range(min, max);
                let d = rng.gen_range(min, max);

                {
                    let va = vec2(a, b);
                    let vb = vec2(c, a);
                    let vc = vec2(a + c, b + a);

                    assert_eq!(va + vb, vc);
                    assert_eq!(&va + &vb, vc);
                    assert_eq!(&va + vb, vc);
                    assert_eq!(va + &vb, vc);

                    let mut vd = vec2(a, c);
                    let ve = vec2(b, b);
                    let vf = vec2 (a + b, b + c);
                    vd += ve;

                    assert_eq!(vd, vf);
                }

                {
                    let va = vec3(a, b, c);
                    let vb = vec3(c, a, d);
                    let vc = vec3(a + c, b + a, c + d);

                    assert_eq!(va + vb, vc);
                    assert_eq!(&va + &vb, vc);
                    assert_eq!(&va + vb, vc);
                    assert_eq!(va + &vb, vc);

                    let mut vd = vec3(a, c, d);
                    let ve = vec3(b, b, d);
                    let vf = vec3(a + b, b + c, d + d);
                    vd += ve;

                    assert_eq!(vd, vf);
                }

                {
                    let va = vec4(a, b, c, d);
                    let vb = vec4(c, a, d, b);
                    let vc = vec4(a + c, b + a, c + d, d + b);

                    assert_eq!(va + vb, vc);
                    assert_eq!(&va + &vb, vc);
                    assert_eq!(&va + vb, vc);
                    assert_eq!(va + &vb, vc);

                    let mut vd = vec4(a, c, d, b);
                    let ve = vec4(b, b, d, a);
                    let vf = vec4(a + b, b + c, d + d, b + a);
                    vd += ve;

                    assert_eq!(vd, vf);
                }
            )*}
        }

        generate_tests!(u8 i8 u16 i16 u32 i32 u64 i64 f32 f64);

        #[cfg(has_i128)]
        generate_tests!(u128 i128);
    }

    #[test]
    fn sub_and_assign() {
        let mut rng = rand::thread_rng();

        macro_rules! generate_tests {
            ($($t:ty)*) => {$(
                let min = <$t>::min_bound()/2 as $t;
                let max = <$t>::max_bound()/2 as $t;
                let a = rng.gen_range(min + ((max - min) as f64 * 0.75) as $t, max);
                let b = rng.gen_range(min + ((max - min) as f64 * 0.50) as $t, min + ((max - min) as f64 * 0.75) as $t);
                let c = rng.gen_range(min + ((max - min) as f64 * 0.25) as $t, min + ((max - min) as f64 * 0.50) as $t);
                let d = rng.gen_range(min,  min + ((max - min) as f64 * 0.25) as $t);

                {
                    let va = vec2(a, b);
                    let vb = vec2(c, b);
                    let vc = vec2(a - c, b - b);

                    assert_eq!(va - vb, vc);
                    assert_eq!(&va - &vb, vc);
                    assert_eq!(&va - vb, vc);
                    assert_eq!(va - &vb, vc);

                    let mut vd = vec2(a, b);
                    let ve = vec2(c, d);
                    let vf = vec2 (a - c, b - d);
                    vd -= ve;

                    assert_eq!(vd, vf);
                }

                {
                    let va = vec3(a, b, c);
                    let vb = vec3(c, d, c);
                    let vc = vec3(a - c, b - d, c - c);

                    assert_eq!(va - vb, vc);
                    assert_eq!(&va - &vb, vc);
                    assert_eq!(&va - vb, vc);
                    assert_eq!(va - &vb, vc);

                    let mut vd = vec3(a, b, a);
                    let ve = vec3(b, c, d);
                    let vf = vec3(a - b, b - c, a - d);
                    vd -= ve;

                    assert_eq!(vd, vf);
                }

                {
                    let va = vec4(a, b, a, c);
                    let vb = vec4(c, d, b, d);
                    let vc = vec4(a - c, b - d, a - b, c - d);

                    assert_eq!(va - vb, vc);
                    assert_eq!(&va - &vb, vc);
                    assert_eq!(&va - vb, vc);
                    assert_eq!(va - &vb, vc);

                    let mut vd = vec4(b, c, b, a);
                    let ve = vec4(c, c, d, c);
                    let vf = vec4(b - c, c - c, b - d, a - c);
                    vd -= ve;

                    assert_eq!(vd, vf);
                }
            )*}
        }

        generate_tests!(u8 i8 u16 i16 u32 i32 u64 i64 f32 f64);

        #[cfg(has_i128)]
        generate_tests!(u128 i128);
    }

    #[test]
    fn mul_and_assign() {
        let mut rng = rand::thread_rng();

        macro_rules! generate_tests {
            ($($t:ty)*) => {$(
                let va: Vector2<$t> = rng.gen();
                let vb: Vector3<$t> = rng.gen();
                let vc: Vector4<$t> = rng.gen();
                let s = 1.7 as $t;
                assert_eq!(Vector2::new(va.x * s, va.y * s), va * s);
                assert_eq!(Vector2::new(va.x * s, va.y * s), s * va);
                assert_eq!(Vector3::new(vb.x * s, vb.y * s, vb.z * s), vb * s);
                assert_eq!(Vector3::new(vb.x * s, vb.y * s, vb.z * s), s * vb);
                assert_eq!(Vector4::new(vc.x * s, vc.y * s, vc.z * s, vc.w * s), vc * s);
                assert_eq!(Vector4::new(vc.x * s, vc.y * s, vc.z * s, vc.w * s), s * vc);
            )*}
        }

        generate_tests!(u8 i8 u16 i16 u32 i32 u64 i64 f32 f64);

        #[cfg(has_i128)]
        generate_tests!(i128 u128);
    }

    #[test]
    fn div_and_assign() {
        let mut rng = rand::thread_rng();

        macro_rules! generate_tests {
            ($($t:ty)*) => {$(
                let va: Vector2<$t> = rng.gen();
                let vb: Vector3<$t> = rng.gen();
                let vc: Vector4<$t> = rng.gen();
                let s = rng.gen();
                assert_eq!(Vector2::new(va.x / s, va.y / s), va / s);
                assert_eq!(Vector3::new(vb.x / s, vb.y / s, vb.z / s), vb / s);
                assert_eq!(Vector4::new(vc.x / s, vc.y / s, vc.z / s, vc.w / s), vc / s);
            )*}
        }

        generate_tests!(u8 i8 u16 i16 u32 i32 u64 i64 f32 f64);

        #[cfg(has_i128)]
        generate_tests!(i128 u128);
    }

    #[test]
    fn vector_space() {
        let mut rng = rand::thread_rng();

        macro_rules! generate_tests {
            ($($t:ty)*) => {$(
                let va: Vector2<$t> = rng.gen();
                let vb: Vector3<$t> = rng.gen();
                let vc: Vector4<$t> = rng.gen();
                assert_eq!(va.dim(), 2);
                assert_eq!(vb.dim(), 3);
                assert_eq!(vc.dim(), 4);
            )*}
        }

        generate_tests!(u8 i8 u16 i16 u32 i32 u64 i64 f32 f64);

        #[cfg(has_i128)]
        generate_tests!(i128 u128);
    }
}
