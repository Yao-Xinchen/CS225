#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"
#include <cmath>

using namespace cs225;

MyColorPicker::MyColorPicker(const double amp, const double freq, const double hue)
    : amp(amp), freq(freq), hue(hue) {}

/**
 * Picks the color for pixel (x, y).
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y)
{
    const auto lumi = 0.5 + amp * std::sin(freq * x + freq * y);
    const auto pixel = HSLAPixel(hue, 1.0, lumi);
    return pixel;
}
