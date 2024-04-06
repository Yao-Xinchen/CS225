/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template<class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template<class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == nullptr)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else
    {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template<class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.emplace_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    const auto mid = t->right->left;
    t->right->left = t;
    t = t->right;
    t->left->right = mid;
    // update height
    t->left->height = 1 + std::max(heightOrNeg1(t->left->left), heightOrNeg1(t->left->right)); // left
    t->height = 1 + std::max(t->left->height, heightOrNeg1(t->right)); // right
}

template<class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.emplace_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template<class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.emplace_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    const auto mid = t->left->right;
    t->left->right = t;
    t = t->left;
    t->right->left = mid;
    // update height
    t->right->height = 1 + std::max(heightOrNeg1(t->right->left), heightOrNeg1(t->right->right)); // right
    t->height = 1 + std::max(heightOrNeg1(t->left), t->right->height); // left
}

template<class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.emplace_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template<class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == nullptr)
        return;

    if (heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right) == 2) // left heavy
    {
        if (heightOrNeg1(subtree->left->left) - heightOrNeg1(subtree->left->right) == 1) // left-left heavy
        {
            rotateRight(subtree);
        } else // left-right heavy
        {
            rotateLeftRight(subtree);
        }
    } else if (heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left) == 2) // right heavy
    {
        if (heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left) == 1) // right-right heavy
        {
            rotateLeft(subtree);
        } else // right-left heavy
        {
            rotateRightLeft(subtree);
        }
    }

    // update height
    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}

template<class K, class V>
void AVLTree<K, V>::insert(const K& key, const V& value)
{
    insert(root, key, value);
}

template<class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == nullptr)
    {
        subtree = new Node(key, value);
    } else if (key < subtree->key)
    {
        insert(subtree->left, key, value);
    } else if (key > subtree->key)
    {
        insert(subtree->right, key, value);
    }

    rebalance(subtree);
}

template<class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template<class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == nullptr)
        return;

    if (key < subtree->key)
    {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key)
    {
        // your code here
        remove(subtree->right, key);
    } else
    { // subtree is the node to remove
        if (subtree->left == nullptr && subtree->right == nullptr)
        {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = nullptr;
        } else if (subtree->left != nullptr && subtree->right != nullptr)
        {
            /* two-child remove */
            // your code here
            auto iop = [subtree] {
                auto temp = subtree->left;
                while (temp->right != nullptr) temp = temp->right;
                return temp;
            }();
            swap(subtree, iop);
            remove(subtree->left, key);
        } else
        {
            /* one-child remove */
            // your code here
            auto temp = subtree;
            if (subtree->left != nullptr)
            {
                subtree = subtree->left;
                delete temp;
            } else
            {
                subtree = subtree->right;
                delete temp;
            }
        }
        // your code here
    }

    if (subtree != nullptr) rebalance(subtree);
}
