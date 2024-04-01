#ifndef BFS_H
#define BFS_H

#include <iterator>
#include <cmath>
#include <list>
#include <queue>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 */
class BFS : public ImageTraversal
{
public:
    BFS(const PNG &png, const Point &start, double tolerance);

    Iterator begin() override;

    Iterator end() override;

    void add(const Point &point) override;

    Point pop() override;

    Point peek() const override;

    bool empty() const override;

    Point &operator[](std::size_t index);

private:
    vector<Point> points;
};

#endif
