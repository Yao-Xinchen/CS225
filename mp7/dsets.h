/* Your code here! */

#ifndef DSETS_H
#define DSETS_H

/**
 * @class DisjointSets
 *
 * @brief Each DisjointSets object represents a family of disjoint sets, where each element has an integer index.
 *
 * It is implemented with the optimizations discussed in class, as up-trees stored in a single vector of ints.
 * Specifically, path compression and union-by-size are used.
 *
 * Each place in the vector represents a node. (Note that this means that the elements in our universe are indexed starting at 0.)
 * A nonnegative number is the index of the parent of the current node; a negative number in a root node is the negative of the set size.
 *
 * @note The default compiler-supplied Big Three will work flawlessly because the only member data is a vector of integers
 * and this vector should initially be empty.
 */
class DisjointSets
{
public:
    /**
     * @brief Creates n unconnected root nodes at the end of the vector.
     *
     * @param num The number of nodes to create.
     */
    void addelements(int num);

    /**
     * @brief This function should compress paths and works as described in lecture.
     *
     * @param elem The element to be found.
     * @return The index of the root of the up-tree in which the parameter element resides.
     */
    int find(int elem);

    /**
     * @brief This function should be implemented as union-by-size.
     *
     * That is, when you setunion two disjoint sets, the smaller (in terms of number of nodes) should point at the larger.
     * This function works as described in lecture, except that you should not assume that the arguments to setunion
     * are roots of existing uptrees.
     *
     * Your setunion function SHOULD find the roots of its arguments before combining the trees.
     * If the two sets are the same size, make the tree containing the second argument point to the tree containing the first.
     * (Note that normally we could break this tie arbitrarily, but in this case we want to control things for grading.)
     *
     * @param a Index of the first element to union
     * @param b Index of the second element to union
     */
    void setunion(int a, int b);

    int size(int elem);
private:
};

#endif
