#ifndef TRIPHASHTABLE_H
#define TRIPHASHTABLE_H

// TODO add header and contracts

#include "stringProcessing.h"
#include "wordPod.h"
#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

class tripHashTable {
    public:
    tripHashTable();
    ~tripHashTable();

    void insert(std::string Key, size_t Fileindex, size_t Lineindex,
                size_t Linenumber);
    void get(std::string Key, bool insensitive, std::vector<wordPod> &wps);

    // prints the formatted value and key of a word.
    void printTable(std::ostream &out);

    private:
    // table is an array of pointers to hashNodes. These can become
    // chained lists.
    std::hash<std::string> my_hash_function;

    static const int INITIAL_TABLE_SIZE = 32;
    size_t           capacity;
    size_t           currentTableSize;
    size_t           numItemsInTable;

    struct hashNode {

        std::string                          key;
        std::unordered_set<wordPod, wordPod> podset;
        hashNode *                           next = nullptr;

        hashNode(std::string Key) { key = Key; }
    };

    void expand();
    void deleteList(hashNode *node);
    int  listLength(hashNode *node);
    void insert(std::string &Key, const wordPod &wp, size_t index);

    hashNode **      mytable;
    stringProcessing sp;
};

#endif