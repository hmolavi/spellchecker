///@file trie.h
///@author Hossein Molavi (hmolavi@uwaterloo.ca)
///@brief Function Declerations for Trie class
///@version 2.3
///@date 2023-03-07
///
///@copyright Copyright (c) 2023
///

#ifndef Trie_h
#define Trie_h

class Trie {
    public:
    Trie(){};
    ~Trie();

    int insertWord(std::string word_to_insert);
    int deleteWord(std::string word_to_delete);
    int prefixCount(std::string prefix_word);
    void spellCheck(std::string possibly_a_badly_spelled_word, std::string used_by_recursion);
    void printTrie(std::string used_by_recursion, int& Words_in_tree);
    int size();
    bool isEmpty();

    private:
    bool illegalInput(std::string possibly_a_badly_spelled_word);
    void createChildren();

    bool endLetter {false};
    bool letterExist {false};
    int numWords {0};
    Trie* parent {nullptr};
    Trie* children {nullptr};
};

#endif