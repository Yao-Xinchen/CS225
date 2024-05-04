/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

std::string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
        IsPunct());
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++)
    {
        // get the corresponding vector of words that represents the current
        // file
        vector<string> words = file_to_vector(filenames[i]);
        /* Your code goes here! */
        for (const auto& word: words)
            file_word_maps[i][word]++;
    }
}

void CommonWords::init_common()
{
    /* Your code goes here! */
    for (auto& word_map: file_word_maps)
        for (auto& pair: word_map)
        {
            const auto word = pair.first;
            common[word]++;
        }
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    /* Your code goes here! */
    for (const auto& pair: common)
    {
        const auto word = pair.first;
        const auto count = pair.second;

        //
        if (count == file_word_maps.size())
        {
            bool is_common = true;
            // check if the word appears in each file >= n times
            for (const auto& file_map: file_word_maps)
            {
                if (file_map.find(word)->second < n)
                {
                    is_common = false;
                    break;
                }
            }
            if (is_common)
                out.push_back(word);
        }
    }

    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open())
    {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof())
        {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
