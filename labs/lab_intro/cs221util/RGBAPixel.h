#ifndef RGBAPIXEL_H
#define RGBAPIXEL_H

namespace cs221util
{
    class RGBAPixel
    {
    public:
        unsigned char r, g, b; // RGB
        double a;              // alpha

        RGBAPixel();
        RGBAPixel(unsigned char, unsigned char, unsigned char);
        RGBAPixel(unsigned char, unsigned char, unsigned char, double);
    };
}

#endif