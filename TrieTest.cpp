///@file trietest.cpp
///@author Hossein Molavi (hmolavi@uwaterloo.ca)
///@brief Driver and Parser
///@version 2.0
///@date 2023-03-07
///
///@copyright Copyright (c) 2023
///

#include <iostream>
#include <fstream>

#include "Trie.h"
#include "IllegalException.h"
#include "Trie.cpp"

using namespace std;

int main(){
    string cmd;
    Trie* Tree = new Trie;

    while (cin >> cmd){
        if("load" == cmd){
            ifstream file("corpus.txt");
            string addWord;
            while(file >> addWord) Tree->insertWord(addWord);
            file.close();
            if(Tree->isEmpty()) cout << "---change corpus PATH---" << endl;
            else cout << "success" << endl;
        }

        else if("i" == cmd){
            cin >> cmd;  
            int result = Tree->insertWord(cmd);
            if (result == 1)
                cout << "success" << endl;
            else if (result == 0)
                cout << "failure" << endl;
        }

        else if ("c" == cmd){
            cin >> cmd;
            int result{ Tree->prefixCount(cmd) };
            if ( result == 0) std::cout << "not found" << std::endl;
            else if (result > 0) std::cout << "count is " << result << std::endl;
        }
        
        else if ("e" == cmd){
            cin >> cmd;
            int result = Tree->deleteWord(cmd);
            if (result == 1)
                cout << "success" << endl;
            else if (result == 0)
                cout << "failure" << endl;
        }

        else if ("p" == cmd){
            int num = Tree->size();
            Tree->printTrie("", num);
        }

        else if ("spellcheck" == cmd){
            cin >> cmd;
            Tree->spellCheck(cmd, cmd);
        }

        else if ("empty" == cmd){
            cout << "empty " << Tree->isEmpty() << endl;
        }

        else if ("clear" == cmd){
            delete Tree;
            Tree = new Trie;
            cout << "success" << endl;
        }

        else if ("size" == cmd){
            cout << "number of words is " << Tree->size() << endl;
        }

        else if ("exit" == cmd){
            delete Tree;
            break;
        }
    }
}