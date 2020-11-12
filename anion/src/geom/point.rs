use std::fmt::{Display, Formatter, Result};

pub struct Point2<T> {
    pub x: T,
    pub y: T,
}

pub struct Point3<T> {
    pub x: T,
    pub y: T,
    pub z: T,
}

impl<T: Display> Display for Point2<T> {
    fn fmt(&self, f: &mut Formatter<'_>) -> Result {
        write!(f, "Point<{:02.02}, {:02.02}>", self.x, self.y)
    }
}
