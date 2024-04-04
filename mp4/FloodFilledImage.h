#ifndef FLOODFILLEDIMAGE_H
#define FLOODFILLEDIMAGE_H

#include "cs225/PNG.h"
#include <list>
#include <iostream>
#include <vector>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"

using namespace cs225;
using namespace std;

class FloodFilledImage
{
public:
    FloodFilledImage(const PNG& png);

    void addFloodFill(ImageTraversal& traversal, ColorPicker& colorPicker);

    Animation animate(unsigned frameInterval) const;

private:
    PNG image;
    vector<ImageTraversal*> traversals;
    vector<ColorPicker*> pickers;
};

#endif // FLOODFILLEDIMAGE_H