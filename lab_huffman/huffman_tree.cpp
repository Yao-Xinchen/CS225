/**
 * @file huffman_tree.cpp
 * Implementation of a Huffman Tree class.
 *
 * @author Chase Geigle - Created
 * @author Nathan Walters - Modified
 * @date Summer 2012
 * @date Fall 2017
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>

#include "huffman_tree.h"

using namespace std;

HuffmanTree::HuffmanTree(vector<Frequency> frequencies)
{
    std::stable_sort(frequencies.begin(), frequencies.end());
    buildTree(frequencies);
    vector<bool> path;
    buildMap(root_, path);
}

HuffmanTree::HuffmanTree(const HuffmanTree &other)
{
    copy(other);
}

HuffmanTree::HuffmanTree(BinaryFileReader &bfile)
{
    root_ = readTree(bfile);
    vector<bool> path;
    buildMap(root_, path);
}

HuffmanTree::~HuffmanTree()
{
    clear(root_);
}

const HuffmanTree &HuffmanTree::operator=(const HuffmanTree &rhs)
{
    if (this != &rhs)
    {
        clear(root_);
        copy(rhs);
    }
    return *this;
}

void HuffmanTree::clear(TreeNode *current)
{
    if (current == nullptr)
        return;
    clear(current->left);
    clear(current->right);
    delete current;
}

void HuffmanTree::copy(const HuffmanTree &rhs)
{
    root_ = copy(rhs.root_);
}

HuffmanTree::TreeNode *HuffmanTree::copy(const TreeNode *current)
{
    if (current == nullptr)
        return nullptr;
    TreeNode *node = new TreeNode(current->freq);
    node->left = copy(current->left);
    node->right = copy(current->right);
    return node;
}

HuffmanTree::TreeNode *
HuffmanTree::removeSmallest(queue<TreeNode *> &singleQueue,
                            queue<TreeNode *> &mergeQueue)
{
    TreeNode *smallest = nullptr;
    // your code!
    if (singleQueue.empty())
    {
        smallest = mergeQueue.front();
        mergeQueue.pop();
    } else if (mergeQueue.empty())
    {
        smallest = singleQueue.front();
        singleQueue.pop();
    } else
    {
        if (singleQueue.front()->freq.getFrequency() <= mergeQueue.front()->freq.getFrequency())
        {
            smallest = singleQueue.front();
            singleQueue.pop();
        } else
        {
            smallest = mergeQueue.front();
            mergeQueue.pop();
        }
    }
    return smallest;
}

void HuffmanTree::buildTree(const vector<Frequency> &frequencies)
{
    queue<TreeNode *> singleQueue; // Queue containing the leaf nodes
    queue<TreeNode *> mergeQueue; // Queue containing the inner nodes

    auto sorted = frequencies;
    std::sort(sorted.begin(), sorted.end());

    // for (auto it = sorted.end(); it != sorted.begin(); --it)
    // {
    //     auto *node = new TreeNode(*it);
    //     singleQueue.push(node);
    // }

    for (auto freq : sorted)
    {
        auto *node = new TreeNode(freq);
        singleQueue.push(node);
    }

    while (!singleQueue.empty() || mergeQueue.size() > 1)
    {
        const auto left = removeSmallest(singleQueue, mergeQueue);
        const auto right = removeSmallest(singleQueue, mergeQueue);
        auto parent = new TreeNode(left->freq.getFrequency() + right->freq.getFrequency());
        parent->left = left;
        parent->right = right;
        mergeQueue.push(parent);
    }

    root_ = mergeQueue.front();
}

string HuffmanTree::decodeFile(BinaryFileReader &bfile)
{
    stringstream ss;
    decode(ss, bfile);
    return ss.str();
}

void HuffmanTree::decode(stringstream &ss, BinaryFileReader &bfile)
{
    TreeNode *current = root_;
    while (bfile.hasBits())
    {
        if (current->left == nullptr && current->right == nullptr) // leaf node
        {
            ss << current->freq.getCharacter();
            current = root_;
        } else
        { // internal node
            const auto bit = bfile.getNextBit();
            if (bit)
                current = current->right;
            else
                current = current->left;
        }
    }
    ss << current->freq.getCharacter();
}

void HuffmanTree::writeTree(BinaryFileWriter &bfile)
{
    writeTree(root_, bfile);
}

void HuffmanTree::writeTree(TreeNode *current, BinaryFileWriter &bfile)
{
    if (current->left == nullptr && current->right == nullptr)
    { // leaf node
        bfile.writeBit(true);
        bfile.writeByte(current->freq.getCharacter());
        return;
    }

    // internal node
    bfile.writeBit(false);
    if (current->left != nullptr) writeTree(current->left, bfile);
    if (current->right != nullptr) writeTree(current->right, bfile);
}

HuffmanTree::TreeNode *HuffmanTree::readTree(BinaryFileReader &bfile)
{
    // no more bits
    if (!bfile.hasBits()) return nullptr;

    const auto bit = bfile.getNextBit();
    if (bit == 1)
    {
        const auto ch = bfile.getNextByte();
        const auto node = new TreeNode(Frequency(ch, 0));
        node->left = nullptr;
        node->right = nullptr;
        return node;
    } else // bit == 0
    {
        const auto left = readTree(bfile);
        const auto right = readTree(bfile);
        const auto node = new TreeNode(0);
        node->left = left;
        node->right = right;
        return node;
    }
}

void HuffmanTree::buildMap(TreeNode *current, vector<bool> &path)
{
    // Base case: leaf node.
    if (current->left == nullptr && current->right == nullptr)
    {
        bitsMap_[current->freq.getCharacter()] = path;
        return;
    }

    // Move left
    path.push_back(false);
    buildMap(current->left, path);
    path.pop_back();

    // Move right
    path.push_back(true);
    buildMap(current->right, path);
    path.pop_back();
}

void HuffmanTree::printInOrder() const
{
    printInOrder(root_);
    cout << endl;
}

void HuffmanTree::printInOrder(const TreeNode *current) const
{
    if (current == nullptr)
        return;
    printInOrder(current->left);
    cout << current->freq.getCharacter() << ":" << current->freq.getFrequency()
            << " ";
    printInOrder(current->right);
}

void HuffmanTree::writeToFile(const string &data, BinaryFileWriter &bfile)
{
    for (auto it = data.begin(); it != data.end(); ++it)
        writeToFile(*it, bfile);
}

void HuffmanTree::writeToFile(char c, BinaryFileWriter &bfile)
{
    vector<bool> bits = getBitsForChar(c);
    for (auto it = bits.begin(); it != bits.end(); ++it)
        bfile.writeBit(*it);
}

vector<bool> HuffmanTree::getBitsForChar(char c)
{
    return bitsMap_[c];
}

// class for generic printing

template<typename TreeNode>
class HuffmanTreeNodeDescriptor
        : public GenericNodeDescriptor<HuffmanTreeNodeDescriptor<TreeNode>>
{
public:
    HuffmanTreeNodeDescriptor(const TreeNode *root) : subRoot_(root)
    { /* nothing */
    }

    string key() const
    {
        std::stringstream ss;
        char ch = subRoot_->freq.getCharacter();
        int freq = subRoot_->freq.getFrequency();

        // print the sum of the two child frequencies
        if (ch == '\0')
            ss << freq;
        // print the leaf containing a character and its count
        else
        {
            if (ch == '\n')
                ss << "\\n";
            else
                ss << ch;
            ss << ":" << freq;
        }
        return ss.str();
    }

    bool isNull() const
    {
        return subRoot_ == nullptr;
    }

    HuffmanTreeNodeDescriptor left() const
    {
        return HuffmanTreeNodeDescriptor(subRoot_->left);
    }

    HuffmanTreeNodeDescriptor right() const
    {
        return HuffmanTreeNodeDescriptor(subRoot_->right);
    }

private:
    const TreeNode *subRoot_;
};

int HuffmanTree::height(const TreeNode *subRoot) const
{
    if (subRoot == nullptr)
        return -1;
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

void HuffmanTree::print(std::ostream &out) const
{
    int h = height(root_);
    if (h > _max_print_height)
    {
        out << "Tree is too big to print. Try with a small file (e.g. "
                "data/small.txt)"
                << endl;
        return;
    }

    printTree(HuffmanTreeNodeDescriptor<TreeNode>(root_), out);
}
