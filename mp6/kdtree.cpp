/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <random>

using namespace std;

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    auto first_val = first[curDim];
    auto second_val = second[curDim];
    if (first_val == second_val) return first < second; // tie breaker
    return first_val < second_val;
}

template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    // square of the distance
    auto dist_sq = [target](const Point<Dim>& p) {
        double dist = 0; // using int would cause bugs
        for (int i = 0; i < Dim; ++i)
            dist += (p[i] - target[i]) * (p[i] - target[i]);
        return dist;
    };

    const auto current_dist = dist_sq(currentBest);
    const auto potential_dist = dist_sq(potential);
    if (potential_dist == current_dist) return potential < currentBest; // tie breaker
    return potential_dist < current_dist;
}

template<int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    // copy the points
    auto points = newPoints;

    // build the tree
    root = buildTree(points, 0, points.size() - 1, 0);
    size = points.size();
}

template<int Dim>
KDTree<Dim>::KDTree(const KDTree& other)
{
    root = nullptr; // make sure the root is null
    *this = other;
}

template<int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs)
{
    // check for self-assignment
    if (this == &rhs) return *this;
    // destroy the current tree
    destroy(root);
    root = nullptr;
    // copy the other tree
    copy(root, rhs.root);
    size = rhs.size;
    return *this;
}

template<int Dim>
KDTree<Dim>::~KDTree()
{
    destroy(root);
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    return findNearestNeighbor(root, query, 0);
}

template<int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(vector<Point<Dim>>& newPoints,
                                                         const int a, const int b, int dim)
{
    // base cases
    if (a < 0 || b >= static_cast<int>(newPoints.size())) return nullptr;
    if (a > b) return nullptr;
    if (a == b) return new KDTreeNode(newPoints[a]);

    // find the median
    auto smaller_ = [this, dim](const Point<Dim>& first, const Point<Dim>& second) {
        return smallerDimVal(first, second, dim);
    }; // cannot be called in quickSelect as a lambda, so convert it to std::function
    std::function<bool(const Point<Dim>&, const Point<Dim>&)> smaller = smaller_;
    auto m = (a + b) / 2;
    quickSelect<Point<Dim>>(newPoints, a, b, m, smaller);

    // recursively build the left and right subtrees
    auto left = buildTree(newPoints, a, m - 1, (dim + 1) % Dim);
    auto right = buildTree(newPoints, m + 1, b, (dim + 1) % Dim);

    // return the new node
    auto node = new KDTreeNode(newPoints[m]);
    node->left = left;
    node->right = right;
    return node;
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(KDTreeNode* subroot, const Point<Dim>& query, int dim) const
{
    // base cases
    if (subroot->left == nullptr && subroot->right == nullptr) return subroot->point;

    // choose the next subtree
    auto next = smallerDimVal(query, subroot->point, dim) ? subroot->left : subroot->right;
    if (subroot->left == nullptr) next = subroot->right; // choose the other subtree if one is null
    if (subroot->right == nullptr) next = subroot->left;
    auto other = (next == subroot->left) ? subroot->right : subroot->left; // the other subtree

    // find the best point from the next subtree
    auto current_best = findNearestNeighbor(next, query, (dim + 1) % Dim);
    if (shouldReplace(query, current_best, subroot->point))
        current_best = subroot->point;

    // check the other subtree
    auto dist = [query, current_best] {
        double d = 0;
        for (int i = 0; i < Dim; ++i)
            d += (query[i] - current_best[i]) * (query[i] - current_best[i]);
        return d;
    }();
    auto split = (subroot->point[dim] - query[dim]) * (subroot->point[dim] - query[dim]);
    if (split <= dist && other != nullptr)
    { // if the other subtree may contain a better point
        auto other_best = findNearestNeighbor(other, query, (dim + 1) % Dim);
        if (shouldReplace(query, current_best, other_best))
            current_best = other_best;
    }
    return current_best;
}

template<int Dim>
void KDTree<Dim>::destroy(KDTreeNode* subroot)
{
    if (subroot == nullptr) return;
    destroy(subroot->left);
    destroy(subroot->right);
    delete subroot;
}

template<int Dim>
void KDTree<Dim>::copy(KDTreeNode* & subroot, const KDTreeNode* const& other)
{
    if (other == nullptr) return;
    subroot = new KDTreeNode(other->point);
    copy(subroot->left, other->left);
    copy(subroot->right, other->right);
}

template<typename T>
T quickSelect(vector<T>& list, int left, int right, int k,
              std::function<bool(const T&, const T&)>& cmp)
{
    // base case
    if (left == right) return list[left];

    // select a pivotIndex between left and right
    auto pivotIndex = (left + right) / 2;
    pivotIndex = partition(list, left, right, pivotIndex, cmp);

    // pivot is in its final sorted position
    if (k == pivotIndex) return list[k];
    else if (k < pivotIndex) return quickSelect(list, left, pivotIndex - 1, k, cmp);
    else return quickSelect(list, pivotIndex + 1, right, k, cmp);
}

template<typename T>
int partition(vector<T>& list, int left, int right, int pivotIndex,
              std::function<bool(const T&, const T&)>& cmp)
{
    auto pivotValue = list[pivotIndex];

    // move pivot to end
    std::swap(list[pivotIndex], list[right]);
    auto storeIndex = left;
    for (auto i = left; i < right; ++i)
    {
        if (cmp(list[i], pivotValue))
        {
            std::swap(list[storeIndex], list[i]);
            ++storeIndex;
        }
    }

    // move pivot to its final place
    std::swap(list[right], list[storeIndex]);
    return storeIndex;
}
