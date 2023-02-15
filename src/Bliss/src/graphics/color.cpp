#include <graphics/color.h>

COLOR convertRGB(rgb _rgb_) {
    return COLOR {
        {
            (uint8_t)_rgb_.r,
            (uint8_t)_rgb_.g,
            (uint8_t)_rgb_.b
        }
    };
}

rgb _rgb(int red, int green, int blue) {
    return rgb { red, green, blue };
}