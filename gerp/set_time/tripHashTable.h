#ifndef TRIPHASHTABLE_H
#define TRIPHASHTABLE_H

// TODO add header and contracts 

#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include "wordPod.h"
#include "stringProcessing.h"

class tripHashTable {
    public:
    tripHashTable();
    ~tripHashTable();
    
    void insert(std::string Key, std::string Filepath, size_t Index,
                                                               int Linenumber);
    std::vector<wordPod> get(std::string Key, bool insensitive);

    // prints the formatted value and key of a word. 
    void printWord(std::string word, std::ostream &out);
    void printTable(std::ostream &out);
    private: 
    // table is an array of pointers to hashNodes. These can become 
    // chained lists. 
    std::hash<std::string> my_hash_function;

    static const int INTIAL_TABLE_SIZE = 32;
    int currentTableSize;
    int numItemsInTable;
    
    void expand();

    std::unordered_set<wordPod, wordPod> *mytable;
    stringProcessing sp;
};

#endif