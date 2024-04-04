#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 */
double ImageTraversal::calculateDelta(const HSLAPixel& p1, const HSLAPixel& p2)
{
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt((h * h) + (s * s) + (l * l));
}

std::vector<Point> ImageTraversal::find_neighbors(const PNG& png, const Point& point, double tolerance)
{
    static auto within = [point, tolerance, png](const unsigned x, const unsigned y) {
        const auto center = png.getPixel(point.x, point.y);
        const auto p = png.getPixel(x, y);
        return calculateDelta(*center, *p) < tolerance;
    };

    std::vector<Point> neighbors;
    // right
    if (point.x + 1 < png.width()
        && within(point.x + 1, point.y))
    {
        neighbors.emplace_back(point.x + 1, point.y);
    }
    // below
    if (point.y + 1 < png.height()
        && within(point.x, point.y + 1))
    {
        neighbors.emplace_back(point.x, point.y + 1);
    }
    // left
    if (point.x > 0
        && within(point.x - 1, point.y))
    {
        neighbors.emplace_back(point.x - 1, point.y);
    }
    // above
    if (point.y > 0
        && within(point.x, point.y - 1))
    {
        neighbors.emplace_back(point.x, point.y - 1);
    }
    return neighbors;
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator()
{
    it = deque<Point>::iterator();
}

ImageTraversal::Iterator::Iterator(const deque<Point>::iterator& it)
{
    this->it = it;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator& ImageTraversal::Iterator::operator++()
{
    ++it;
    return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*()
{
    return *it;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator& other)
{
    return it != other.it;
}
