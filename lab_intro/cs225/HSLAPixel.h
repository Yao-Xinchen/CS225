//
// Created by Xinchen on 2024/1/16.
//

#ifndef HSLAPIXEL_H
#define HSLAPIXEL_H

namespace cs225
{
    class HSLAPixel
    {
    public:
        double h;
        double s;
        double l;
        double a;
        HSLAPixel();
        HSLAPixel(double hue, double saturation, double luminance);
        HSLAPixel(double hue, double saturation, double luminance, double alpha);
    };
}


#endif // HSLAPIXEL_H
