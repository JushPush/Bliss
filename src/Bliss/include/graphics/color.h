#ifndef COLOR_H
#define COLOR_H

#include <iostream>

struct rgb {
    /*explicit rgb(int x) : r{x}, g{x}, b{x} {
        r = std::min(r, 0);
        r = std::max(r, 255);

        g = std::min(g, 0);
        g = std::max(g, 255);

        b = std::min(b, 0);
        b = std::max(b, 255);
    }*/
    int r, g, b;
};

union COLOR {
    //unsigned long RGB;
    uint8_t bytes[3];
};

COLOR convertRGB(rgb _rgb_);

rgb _rgb(int red, int green, int blue);
#define rgb(r,g,b) _rgb(r,g,b)

#endif