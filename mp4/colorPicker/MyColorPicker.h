#ifndef MyColorPicker_H
#define MyColorPicker_H

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

class MyColorPicker : public ColorPicker
{
public:
    MyColorPicker(double amp, double freq, double hue);

    HSLAPixel getColor(unsigned x, unsigned y) override;

private:
    const double amp = 0.0; // luminance [0.5 - amp, 0.5 + amp]
    const double freq = 0.1;
    const double hue = 0.0;
};

#endif
