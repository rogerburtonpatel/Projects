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

    tripHashTable(const tripHashTable &other); 
    tripHashTable &operator =(const tripHashTable &rhs);
    
    void insert(const std::string &Key, const size_t &Fileindex, const size_t &Lineindex,
                                                             const size_t &Linenumber);
    std::vector<wordPod> get(const std::string &Key, const bool &insensitive);

    // prints the formatted value and key of a word. 
    void printWord(std::string word, std::ostream &out);
    void printTable(std::ostream &out);
    void printBuckets(std::ostream &out);
    void checkLargeBuckets(std::ostream &out);
    private: 
    // table is an array of pointers to hashNodes. These can become 
    // chained lists. 
    std::hash<std::string> my_hash_function;
// TODO: FIX TYPO IN FUNKEYTABLE CODE 'INTIAL TABLE SIZE'
    static const int INITIAL_TABLE_SIZE = 32;
    size_t currentTableSize;
    size_t numItemsInTable;
    
    void expand();

    std::unordered_set<wordPod, wordPod> *mytable;
    stringProcessing sp;
};

#endif