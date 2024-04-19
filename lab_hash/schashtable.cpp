/**
 * @file schashtable.cpp
 * Implementation of the SCHashTable class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#include "schashtable.h"

using hashes::hash;
using std::list;
using std::pair;

template<class K, class V>
SCHashTable<K, V>::SCHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new list<pair<K, V>>[size];
    elems = 0;
}

template<class K, class V>
SCHashTable<K, V>::~SCHashTable()
{
    delete[] table;
}

template<class K, class V>
SCHashTable<K, V> const& SCHashTable<K, V>::
operator=(SCHashTable<K, V> const& rhs)
{
    if (this != &rhs)
    {
        delete[] table;
        table = new list<pair<K, V>>[rhs.size];
        for (size_t i = 0; i < rhs.size; i++)
            table[i] = rhs.table[i];
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template<class K, class V>
SCHashTable<K, V>::SCHashTable(SCHashTable<K, V> const& other)
{
    table = new list<pair<K, V>>[other.size];
    for (size_t i = 0; i < other.size; i++)
        table[i] = other.table[i];
    size = other.size;
    elems = other.elems;
}

template<class K, class V>
void SCHashTable<K, V>::insert(K const& key, V const& value)
{
    ++elems;
    if (shouldResize())
        resizeTable();
    pair<K, V> p(key, value);
    size_t idx = hash(key, size);
    table[idx].push_front(p);
}

template<class K, class V>
void SCHashTable<K, V>::remove(K const& key)
{
    // find the key in the table
    auto idx = hash(key, size);
    auto iterator = std::find_if(table[idx].begin(), table[idx].end(),
                                 [key](pair<K, V> p) { return p.first == key; });
    // erase it if it exists
    if (iterator != table[idx].end()) table[idx].erase(iterator);
    // decrement the number of elements
    --elems;
}

template<class K, class V>
V SCHashTable<K, V>::find(K const& key) const
{
    size_t idx = hash(key, size);
    typename list<pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++)
    {
        if (it->first == key)
            return it->second;
    }
    return V();
}

template<class K, class V>
V& SCHashTable<K, V>::operator[](K const& key)
{
    size_t idx = hash(key, size);
    typename list<pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++)
    {
        if (it->first == key)
            return it->second;
    }

    ++elems;
    if (shouldResize())
        resizeTable();

    idx = hash(key, size);
    pair<K, V> p(key, V());
    table[idx].push_front(p);
    return table[idx].front().second;
}

template<class K, class V>
bool SCHashTable<K, V>::keyExists(K const& key) const
{
    size_t idx = hash(key, size);
    typename list<pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++)
    {
        if (it->first == key)
            return true;
    }
    return false;
}

template<class K, class V>
void SCHashTable<K, V>::clear()
{
    delete[] table;
    table = new list<pair<K, V>>[17];
    size = 17;
    elems = 0;
}

template<class K, class V>
void SCHashTable<K, V>::resizeTable()
{
    // create a new table with double the size
    auto new_size = findPrime(size * 2);
    auto new_table = new list<pair<K, V>>[new_size];

    for (size_t i = 0; i < size; ++i)
    {
        for (auto& pair : table[i])
        {
            auto idx = hash(pair.first, new_size);
            new_table[idx].push_front(pair);
        }
    }

    // replace the table with the new one
    delete[] table;
    table = new_table;
    size = new_size;
}
