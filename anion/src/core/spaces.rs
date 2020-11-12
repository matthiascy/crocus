use crate::core::{Num, Zero};
use std::ops::{Add, Div, Mul, Sub};

pub trait VectorSpace: Copy + Clone
where
    Self: Zero
        + Add<Self, Output = Self>
        + Sub<Self, Output = Self>
        + Mul<<Self as VectorSpace>::Scalar, Output = Self>
        + Div<<Self as VectorSpace>::Scalar, Output = Self>,
{
    type Scalar: Num;

    /// The dimension of the vector space.
    fn dim(&self) -> i32;
}

/// Vector space with the inner product.
pub trait InnerProductSpace: VectorSpace {
    /// The inner product of two vectors.
    fn inner_product(&self, rhs: &Self) -> Self::Scalar;

    /// The distance between two vectors.
    fn distance(&self, rhs: &Self) -> Self::Scalar;

    /// Returns true if two vectors are orthogonal.
    fn are_orthogonal(lhs: &Self, rhs: &Self);
}

/// A finite-dimensional inner product space over the real numbers.
pub trait EuclideanSpace: InnerProductSpace {
    /// The inner product of vectors in Euclidean space.
    fn dot(&self, rhs: &Self) -> Self::Scalar;

    /// The norm of a vector in Euclidean space.
    fn norm(&self) -> Self::Scalar;

    /// The squared norm of a vector in Euclidean space.
    fn norm2(&self) -> Self::Scalar;

    /// The distance of two vectors in Euclidean space.
    fn dist(&self, rhs: &Self) -> Self::Scalar;

    /// The squared distance of two vectors in Euclidean space.
    fn dist2(&self, rhs: &Self) -> Self::Scalar;

    /// Returns true if two vectors are orthogonal in Euclidean space.
    fn is_orthogonal(&self, rhs: &Self) -> bool;

    fn normalize(&self) -> Self;

    fn normalized(&mut self);

    fn project_to(&self, other: Self) -> Self;

    /// The Chebyshev distance between two vectors.
    fn dist_chebyshev(&self, rhs: &Self) -> Self::Scalar;

    /// The Manhattan distance between two vectors.
    fn dist_manhattan(&self, rhs: &Self) -> Self::Scalar;

    /// The Minkowski distance between two vectors.
    fn dist_minkowski(&self, rhs: &Self) -> Self::Scalar;
}
