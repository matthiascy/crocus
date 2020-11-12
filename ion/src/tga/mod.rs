mod args;
mod commands;

pub struct TgaHeader {
    id_length: u8,
    colormap_type: u8,
    datatype_code: u8,
    colormap_origin: u8,
    colormap_depth: u8,
    x_origin: i32,
    y_origin: i32,
    width: i32,
    height: i32,
    bits_per_pixel: u8,
    image_descriptor: u8,
}

#[derive(Debug, PartialEq, Copy, Clone)]
pub struct TgaColor {
    r: u8,
    g: u8,
    b: u8,
    a: u8,
    bytes_per_pixel: i32,
}

impl TgaColor {
    fn new(r: u8, g: u8, b: u8, a: u8) -> TgaColor {
        TgaColor {
            r,
            g,
            b,
            a,
            bytes_per_pixel: 4,
        }
    }

    fn from_u32(val: u32, bpp: i32) -> TgaColor {
        let [r, g, b, a] = val.to_be_bytes();
        TgaColor {
            r,
            g,
            b,
            a,
            bytes_per_pixel: bpp,
        }
    }

    fn to_u32(&self) -> u32 {
        u32::from_be_bytes([self.r, self.g, self.b, self.a])
    }

    fn from_hex(hex: &str, bpp: i32) -> TgaColor {
        match u32::from_str_radix(&hex.replace("#", "+"), 16) {
            Ok(v) => {
                println!("Num we have: {}", v);
                TgaColor::from_u32(v, bpp)
            }
            _ => panic!("Invalid hex form!"),
        }
    }

    fn to_hex(&self) -> String {
        format!("#{:02x}{:02x}{:02x}{:02x}", self.r, self.g, self.b, self.a)
    }
}

enum TgaFormat {
    GrayScale,
    RGB,
    RGBA,
}

struct TgaImage {
    data: Vec<u8>,
    width: i32,
    height: i32,
    bytes_per_pixel: i32,
}

impl TgaImage {
    fn new(width: i32, height: i32, bpp: i32) -> TgaImage {
        unimplemented!()
    }

    fn read_tga_file(&self, filename: &str) -> bool {
        unimplemented!()
    }

    fn write_tag_file(&self, filename: &str) -> bool {
        unimplemented!()
    }

    fn flip_horizontally(&mut self) -> bool {
        unimplemented!()
    }

    fn flip_vertically(&mut self) -> bool {
        unimplemented!()
    }

    fn scale(&mut self, width: i32, height: i32) -> bool {
        unimplemented!()
    }

    fn get(&self, x: i32, y: i32) -> TgaColor {
        unimplemented!()
    }

    fn set(&mut self, x: i32, y: i32, color: TgaColor) -> bool {
        unimplemented!()
    }

    fn width(&self) -> i32 {
        self.width
    }

    fn height(&self) -> i32 {
        self.height
    }

    fn bytes_per_pixel(&self) -> i32 {
        self.bytes_per_pixel
    }
}

#[cfg(test)]
mod tests {
    use super::TgaColor;

    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }

    #[test]
    fn tga_color_construction() {
        let color = TgaColor::new(235, 64, 52, 10);
        assert_eq!(
            TgaColor {
                r: 235,
                g: 64,
                b: 52,
                a: 10,
                bytes_per_pixel: 4
            },
            color
        );
    }

    #[test]
    fn tga_color_u32() {
        let num = 3946853386;
        let color = TgaColor::from_u32(num, 4);
        let hex = color.to_hex();
        println!("Num: {}", num);
        println!("Color: {:?}", color);
        println!("Hex: {}", hex);
        println!("Color.to_u32: {}", color.to_u32());
        assert_eq!(color.to_u32(), num);
    }

    #[test]
    fn tga_color_hex() {
        let [r, g, b, a] = u32::to_ne_bytes(3946853386);
        let num = u32::from_ne_bytes([10, 52, 64, 235]);
        println!("r: {}, g: {}, b: {}, a: {}", r, g, b, a);
        println!("num: {}", num);

        let color = TgaColor::new(235, 64, 52, 10);
        let hex = color.to_hex();

        println!("Color: {:?} with hex: {:?}", color, hex);
        let color_from_hex = TgaColor::from_hex(&hex, 4);

        println!("Color from hex: {:?}", color_from_hex);
        assert_eq!(color_from_hex, color);
    }
}
