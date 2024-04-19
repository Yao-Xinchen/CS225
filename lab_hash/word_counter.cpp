/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

template<template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq(const string& infile)
    : filename(infile)
{
    /* nothing */
}

template<template <class K, class V> class Dict>
vector<pair<string, int>> WordFreq<Dict>::getWords(int threshold) const
{
    TextFile infile(filename);
    Dict<string, int> freqs(0);

    // read in all the words
    while (infile.good())
    {
        auto word = infile.getNextWord();
        if (freqs.keyExists(word))
            ++freqs[word];
        else
            freqs[word] = 1;
    }

    // filter out the words that don't meet the threshold
    vector<pair<string, int>> ret(0);
    for (const auto& pair: freqs)
    {
        // pair is a pair<string, int>
        if (pair.second >= threshold)
            ret.push_back(pair);
    }
    return ret;
}
