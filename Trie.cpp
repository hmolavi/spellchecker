///@file trie.cpp
///@author Hossein Molavi (hmolavi@uwaterloo.ca)
///@brief Function Definitions for Trie class
///@version 2.3
///@date 2023-03-07
///
///@copyright Copyright (c) 2023
///

#ifndef Trie_cpp
#define Trie_cpp

Trie::~Trie(){ delete[] children; }

bool Trie::isEmpty (){ return children == nullptr ? true : false; }

int Trie::size(){ return numWords; }

void Trie::createChildren (){
    children = new Trie [26];
    for (int i{0}; i<26; i++)
        children[i].parent = this;
}

void Trie::spellCheck(std::string constant_word , std::string word){

    if (word.length() == 0){
        if ( endLetter )
            std::cout << "correct";
        
        else { // Guranteed to not have std::endl since word.length is always > 0 initially 
            int num = numWords;
            if ( num==0 ) num++;   // WORDCOUNT
            printTrie(constant_word, num);
        }
        return;
    }

    char character = word[0];   
    word.erase(0, 1);

    if ( isEmpty() || children[character - 'A'].letterExist == false ){ 
        if (parent == nullptr){
            std::cout << std::endl;
            return;
        }

        word = character + word;
        std::string prefix = "";
        long int j = word.length() -1 ;
        for (long unsigned int i{constant_word.length()-1}; i>0; i--){
            if (word[j] == constant_word[i]) j--; 
            if (j < 0){
                prefix = constant_word.substr(0, constant_word.length() - word.length());
                break;
            }   
        }

        int num = numWords;
        if (endLetter) num++;  // WORDCOUNT  
        printTrie(prefix, num);
    }

    else children[character - 'A'].spellCheck(constant_word, word);
    
    if (parent == nullptr) std::cout << std::endl;
}

int Trie::deleteWord (std::string word){
    
    if (word.length() == 0){
        if ( endLetter == true && !isEmpty() ){
            endLetter = false;
            //numWords--; WORDCOUNT
            return 1;
        }
        else if ( isEmpty() ){ // End of the chain --> delete subtree
            return 404;
        }
        return 0; // Not word not in Trie
    }

    char character = word[0];   
    word.erase(0, 1);

    if (parent == nullptr && illegalInput(word)) return -1;   
    if (isEmpty() || children[character - 'A'].letterExist == false) return 0;


    int result = children[character - 'A'].deleteWord(word);

    if ( result < 2 ){
        numWords -= result;
        return result;
    }

    // delete subtree
    if ( numWords == 1 && parent == nullptr ){
        delete[] children;
        children = nullptr;  
        numWords --;
        return 1;
    }
    else if (numWords == 1 && !endLetter){ 
        return result;
    }
    else{
        Trie* tmp = &children[character - 'A'];
        tmp->letterExist = false;
        tmp->~Trie();
        tmp->children = nullptr;  
        numWords --;
        return 1;
    } 
}

int Trie::prefixCount(std::string word){
    if (word.length() == 0){
        if (endLetter) return numWords+1;
        return numWords;
    }
    
    if ( parent == nullptr && illegalInput(word)) 
        return -1;

    if ( !isEmpty() ){                  
        char character = word[0];
        word.erase(0, 1);
        return children[character - 'A'].prefixCount(word);
    }

    return 0;
}

void Trie::printTrie(std::string word, int& Words_in_tree){
    if (endLetter){
        std::cout << word;
        Words_in_tree--;
        if (Words_in_tree > 0)
            std::cout << " ";
    }
    
    if (!isEmpty()){
        for (int i{0}; i<26; i++){
            if (children[i].letterExist == true){
                children[i].printTrie( word + (char)(i+65), Words_in_tree );
            }
        }
    }
    
    if ( parent == nullptr && !isEmpty() ) std::cout << std::endl;
}

int Trie::insertWord (std::string word){
    if (word.length() == 1 && parent != nullptr){
        if (letterExist == false){
            letterExist = true;
            endLetter = true;
            return 1;
        }
        else if ( !endLetter ){
            endLetter = true;
            return 1;
        }
        return 0;
    }

    if (parent == nullptr && illegalInput(word)) return -1;

    if (isEmpty()) createChildren();
    char character = word[0];
    word.erase(0, 1);
    int result;
    
    if (parent != nullptr){
        if ( !letterExist ) letterExist = true;
        result = children[word[0] - 'A'].insertWord(word);
    }
    else{ 
        result = children[character - 'A'].insertWord(character + word);
    }

    numWords += result;
    return result;
}

bool Trie::illegalInput(std::string possibly_a_badly_spelled_word){
    try{
        for (int i{0}; i< possibly_a_badly_spelled_word.length(); i++) 
            if (possibly_a_badly_spelled_word[i] - 'A' > 25 || possibly_a_badly_spelled_word[i] - 'A' < 0) 
                throw illegal_exception();
    }   
    catch(illegal_exception){
        std::cout << "illegal argument" << std::endl ;
        return true;
    }
    return false;
}
#endif