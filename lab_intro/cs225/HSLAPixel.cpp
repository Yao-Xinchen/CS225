//
// Created by Xinchen on 2024/1/16.
//

#include "HSLAPixel.h"


cs225::HSLAPixel::HSLAPixel()
{
    // opaque white
    h = 0;
    s = 0;
    l = 1.0;
    a = 1.0;
}

cs225::HSLAPixel::HSLAPixel(const double hue, const double saturation, const double luminance)
{
    h = hue;
    s = saturation;
    l = luminance;
    a = 1.0;
}

cs225::HSLAPixel::HSLAPixel(const double hue, const double saturation, const double luminance, const double alpha)
{
    h = hue;
    s = saturation;
    l = luminance;
    a = alpha;
}
