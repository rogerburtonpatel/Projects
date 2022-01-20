// TODO add header and contracts 

#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include "wordPod.h"

class tripHashTable {
    public:
    tripHashTable();
    ~tripHashTable();
    
    void insert(std::string Key, std::string Filepath, size_t Index,
                                                               int Linenumber);
    // prints the formatted value and key of a word. 
    void printWord(std::string word, std::ostream &out);
    private: 
    // table is an array of pointers to hashNodes. These can become 
    // chained lists. 
    std::hash<std::string> my_hash_function;

    static const int INTIAL_TABLE_SIZE = 32;
    int capacity; 
    int currentTableSize;
    int numItemsInTable;

    struct hashNode {

        std::string key;
        wordPod value {"", 0, 0}; // placeholder; 
                                       // value MUST be instantiated 
                                       // with hashNode constructor. 
        hashNode *next;

        hashNode(std::string Key, std::string Filepath, size_t Index, 
                                              int Linenumber, hashNode *Next) {
            key = Key;
            value = wordPod(Filepath, Index, Linenumber);
            next = Next;
        }
    };
    
    void expand();
    void deleteList(hashNode *node);
    int listLength(hashNode *node);
    std::vector<wordPod> get(std::string Key);

    hashNode **mytable;
};