#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

using namespace cs225;

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
DFS::DFS(const PNG& png, const Point& start, double tolerance)
{
    auto visited = std::vector<std::vector<bool>>(png.width(), std::vector<bool>(png.height(), false));

    stack<Point> to_visit;
    to_visit.push(start);

    // keep visiting until there are no more points to visit
    while (!to_visit.empty())
    {
        // get the next point to visit
        const auto current = to_visit.top(); // not reference
        to_visit.pop();

        // visit the current point
        const auto neighbors = find_neighbors(png, current, tolerance);
        for (const auto& neighbor: neighbors)
        {
            if (!visited[neighbor.x][neighbor.y])
            {
                to_visit.push(neighbor);
            }
        }

        // move the current point to the visited list
        if (!visited[current.x][current.y])
        {
            points.push_back(current);
        }
        visited[current.x][current.y] = true;
    }
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin()
{
    return Iterator(points.begin());
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end()
{
    return Iterator(points.end());
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point& point)
{
    points.push_back(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop()
{
    const Point p = points.back();
    points.pop_back();
    return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const
{
    return points.back();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const
{
    return points.empty();
}

Point& DFS::operator[](const std::size_t index)
{
    return points[index];
}
