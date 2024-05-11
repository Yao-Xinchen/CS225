/* Your code here! */

#include "dsets.h"

void DisjointSets::addelements(const int num)
{
    const auto len = elements.size();
    elements.resize(len + num, -1);
}

int DisjointSets::find(const int elem)
{
    if (elements[elem] < 0) return elem;
    return elements[elem] = find(elements[elem]);
}

void DisjointSets::setunion(const int a, const int b)
{
    const auto root_a = find(a);
    const auto root_b = find(b);
    if (root_a == root_b) return;

    // union-by-size
    if (elements[root_a] <= elements[root_b])
    {
        elements[root_a] += elements[root_b]; // update size
        elements[root_b] = root_a; // update parent
    }
    else // elements[root_a] >= elements[root_b]
    {
        elements[root_b] += elements[root_a];
        elements[root_a] = root_b;
    }
}

int DisjointSets::size(const int elem)
{
    return -elements[find(elem)];
}

