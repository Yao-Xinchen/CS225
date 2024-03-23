/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

#include "binarytree.h"

using namespace std;

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template<typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template<typename T>
int BinaryTree<T>::height(const Node *subRoot) const
{
    // Base case
    if (subRoot == nullptr)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template<typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template<typename T>
void BinaryTree<T>::printLeftToRight(const Node *subRoot) const
{
    // Base case - null node
    if (subRoot == nullptr)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template<typename T>
void BinaryTree<T>::mirror()
{
    this->mirror(root);
}

/**
 * Flips the subtree over a vertical axis, modifying the tree itself
 * @param subRoot The current node in the recursion
 */
template<typename T>
void BinaryTree<T>::mirror(Node *subRoot)
{
    if (subRoot == nullptr)
        return;

    mirror(subRoot->left);
    mirror(subRoot->right);

    swap(subRoot->left, subRoot->right);
}

/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template<typename T>
bool BinaryTree<T>::isOrdered() const
{
    return get<0>(isOrdered(root));
}

/**
 * @return <result, min, max>, where result is true if the
 * subtree is ordered, and false otherwise. min and max are the minimum and
 * maximum values in the subtree, respectively.
 * @param subRoot The current node in the recursion
 */
template<typename T>
tuple<bool, T, T> BinaryTree<T>::isOrdered(Node *subRoot) const
{
    // NOT SUPPORTED BY CPP11
    // if (subRoot->left == nullptr && subRoot->right == nullptr) // leaf node
    //     return {true, subRoot->elem, subRoot->elem};
    //
    // if (subRoot->left == nullptr) // left is empty
    // {
    //     auto [r_result, r_min, r_max] = isOrdered(subRoot->right);
    //     return {r_result && subRoot->elem < r_min, min(subRoot->elem, r_min), max(subRoot->elem, r_max)};
    // }
    //
    // if (subRoot->right == nullptr) // right is empty
    // {
    //     auto [l_result, l_min, l_max] = isOrdered(subRoot->left);
    //     return {l_result && l_max < subRoot->elem, min(subRoot->elem, l_min), max(subRoot->elem, l_max)};
    // }
    //
    // auto [l_result, l_min, l_max] = isOrdered(subRoot->left);
    // auto [r_result, r_min, r_max] = isOrdered(subRoot->right);
    //
    // return {
    //     l_result && r_result && l_max < subRoot->elem && subRoot->elem < r_min,
    //     min({subRoot->elem, l_min, r_min}),
    //     max({subRoot->elem, l_max, r_max})
    // };

    if (subRoot->left == nullptr && subRoot->right == nullptr) // leaf node
        return {true, subRoot->elem, subRoot->elem};

    if (subRoot->left == nullptr) // left is empty
    {
        auto right_tuple = isOrdered(subRoot->right);
        return {
            get<0>(right_tuple) && subRoot->elem < get<1>(right_tuple),
            min(subRoot->elem, get<1>(right_tuple)),
            max(subRoot->elem, get<2>(right_tuple))
        };
    }

    if (subRoot->right == nullptr) // right is empty
    {
        auto left_tuple = isOrdered(subRoot->left);
        return {
            get<0>(left_tuple) && get<2>(left_tuple) < subRoot->elem,
            min(subRoot->elem, get<1>(left_tuple)),
            max(subRoot->elem, get<2>(left_tuple))
        };
    }

    auto left_tuple = isOrdered(subRoot->left);
    auto right_tuple = isOrdered(subRoot->right);

    return {
        get<0>(left_tuple) && get<0>(right_tuple)
        && get<2>(left_tuple) < subRoot->elem && subRoot->elem < get<1>(right_tuple),
        min({subRoot->elem, get<1>(left_tuple), get<1>(right_tuple)}),
        max({subRoot->elem, get<2>(left_tuple), get<2>(right_tuple)})
    };
}


/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template<typename T>
void BinaryTree<T>::printPaths(vector<vector<T>> &paths) const
{
    printPaths(root, paths);
}

/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param subRoot The current node in the recursion
 * @param paths vector of vectors that contains path of nodes
 */
template<typename T>
void BinaryTree<T>::printPaths(Node *subRoot, vector<vector<T>> &paths) const
{
    if (subRoot == nullptr)
    {
        paths = {};
        return;
    }

    // If it's a leaf node, add the path to paths
    if (subRoot->left == nullptr && subRoot->right == nullptr)
    {
        paths.push_back(vector<T>{subRoot->elem});
        return;
    }

    vector<vector<T>> right_paths;

    printPaths(subRoot->left, paths);
    printPaths(subRoot->right, right_paths);

    // combine left and right paths
    paths.insert(paths.end(), right_paths.begin(), right_paths.end());

    for (auto &path: paths)
    {
        // insert the current node to the beginning of each path
        path.insert(path.begin(), subRoot->elem);
    }
}


/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template<typename T>
int BinaryTree<T>::sumDistances() const
{
    return sumDistances(root, 0);
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @param subRoot The current node in the recursion
 * @param depth The depth of the current node
 * @return The sum of the distances of all nodes to the root
 */
template<typename T>
int BinaryTree<T>::sumDistances(Node *subRoot, int depth) const
{
    if (subRoot == nullptr)
        return 0;

    return sumDistances(subRoot->left, depth + 1)
           + sumDistances(subRoot->right, depth + 1)
           + depth;
}
