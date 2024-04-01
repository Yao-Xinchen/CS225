#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
BFS::BFS(const PNG &png, const Point &start, double tolerance)
{
    auto mentioned = std::vector<std::vector<bool>>(png.width(), std::vector<bool>(png.height(), false));

    queue<Point> to_visit;
    to_visit.push(start);

    // keep visiting until there are no more points to visit
    while (!to_visit.empty())
    {
        // get the next point to visit
        const auto current = to_visit.front(); // not reference
        to_visit.pop();
        mentioned[current.x][current.y] = true;

        // visit the current point
        const auto neighbors = find_neighbors(png, current, tolerance);
        for (const auto &neighbor: neighbors)
        {
            if (!mentioned[neighbor.x][neighbor.y])
            { // neither visited nor to be visited
                to_visit.push(neighbor);
                mentioned[neighbor.x][neighbor.y] = true;
            }
        }

        // move the current point to the visited list
        points.push_back(current);
    }
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin()
{
    return Iterator(points.begin());
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end()
{
    return Iterator(points.end());
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point &point)
{
    points.push_back(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop()
{
    const Point p = points.back();
    points.pop_back();
    return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const
{
    return points.back();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const
{
    return points.empty();
}

Point &BFS::operator[](const std::size_t index)
{
    return points[index];
}
