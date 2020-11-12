pub mod bounded;
pub mod identity;
pub mod num;
pub mod real;
pub mod spaces;

pub use bounded::Bounded;
pub use identity::{One, Zero};
pub use num::Num;
pub use real::{Floating, Fractional, Integral};
pub use spaces::{EuclideanSpace, InnerProductSpace, VectorSpace};
