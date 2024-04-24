/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template<class T, class Compare>
size_t heap<T, Compare>::root() const
{
    return 0;
}

template<class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    return 2 * currentIdx + 1;
}

template<class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    return 2 * currentIdx + 2;
}

template<class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    return (currentIdx - 1) / 2;
}

template<class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    return leftChild(currentIdx) < _elems.size();
}

template<class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    auto left = leftChild(currentIdx);
    auto right = rightChild(currentIdx);
    if (right >= _elems.size() || higherPriority(_elems[left], _elems[right]))
        return left;
    return right;
}

template<class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // if the current index has no children, return
    if (!hasAChild(currentIdx)) return;
    // get the index of the child with the highest priority
    auto maxChild = maxPriorityChild(currentIdx);
    // if the child has higher priority than the current index, swap them and heapify down the child
    if (higherPriority(_elems[maxChild], _elems[currentIdx]))
    {
        std::swap(_elems[currentIdx], _elems[maxChild]);
        heapifyDown(maxChild);
    }
}

template<class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx]))
    {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template<class T, class Compare>
heap<T, Compare>::heap()
{
    // empty heap
    _elems = {};
}

template<class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    // copy the elements into the vector
    _elems = {};
    std::copy(elems.begin(), elems.end(), std::back_inserter(_elems));
    // heapify the elements
    for (auto i = parent(_elems.size() - 1); i < _elems.size(); --i) heapifyDown(i);
}

template<class T, class Compare>
T heap<T, Compare>::pop()
{
    // store the top element
    auto top = _elems[root()];
    // swap the top element with the last element and remove it
    std::swap(_elems[root()], _elems[_elems.size() - 1]);
    _elems.pop_back();
    // heapify down the root
    heapifyDown(root());
    return top;
}

template<class T, class Compare>
T heap<T, Compare>::peek() const
{
    return _elems[root()];
}

template<class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // add the element to the end of the vector
    _elems.push_back(elem);
    // heapify up the element
    heapifyUp(_elems.size() - 1);
}

template<class T, class Compare>
bool heap<T, Compare>::empty() const
{
    return _elems.empty();
}

template<class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T>& heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++)
    {
        heaped.push_back(_elems[i]);
    }
}
