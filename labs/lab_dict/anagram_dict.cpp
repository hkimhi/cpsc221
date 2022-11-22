/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"
#include <algorithm>
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    ifstream words(filename);
    string word;
    if (words.is_open()) {
        while (getline(words, word)) {
            add_word_to_dict(word);
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    for (const string& word : words) {
        add_word_to_dict(word);
    }
}

/**
 * @param word The word to add to the dictionary
 * Adds the word as a (key, value) pair to the dictionary.
 * NOTE: word is the value. You will need to decide an appropriate key
 * for the word.
 */
void AnagramDict::add_word_to_dict(const std::string& word)
{
    /* Your code goes here! */
    string sorted_word = word;
    sort(sorted_word.begin(), sorted_word.end());
    
    if(dict.find(sorted_word) != dict.end()) {
        // word exists, add it to dictionary
        dict[sorted_word].push_back(word);
    }
    else
    {
        //word doesn't exist, so make a new vector and add it to dictionary
        vector<string> new_vec;
        new_vec.push_back(word);

        dict[sorted_word] = new_vec;
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string sorted_word = word;
    sort(sorted_word.begin(), sorted_word.end());
    
    if(dict.find(sorted_word) != dict.end()) {
        return dict.at(sorted_word);
    }
    else {
        return vector<string>();
    }
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> all_anagrams;

    for(auto &entry : dict) {
        if(entry.second.size() >= 2) {
            all_anagrams.push_back(entry.second);
        }
    }
    
    return all_anagrams;
}
