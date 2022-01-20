// TODO add header and contracts

#include "tripHashTable.h"
#include <functional>
#include <iostream>
#include <string>
#include <vector>

tripHashTable::tripHashTable() {
    currentTableSize = INITIAL_TABLE_SIZE;
    numItemsInTable  = 0;

    mytable = new hashNode *[currentTableSize];
    for (size_t i = 0; i < currentTableSize; i++) {
        mytable[i] = nullptr;
    }
}

tripHashTable::~tripHashTable() {
    for (size_t i = 0; i < currentTableSize; ++i) {
        deleteList(mytable[i]);
        mytable[i] = nullptr;
    }

    delete[] mytable;
}

void tripHashTable::deleteList(hashNode *node) {
    if (node == nullptr) return;
    deleteList(node->next);
    delete node;
}

void tripHashTable::insert(std::string Key, size_t Fileindex, size_t Lineindex,
                           size_t Linenumber) {
    if ((double)numItemsInTable / (double)currentTableSize >= 0.8) { expand(); }
    Key = sp.stripNonAlphaNum(Key);
    size_t index =
        my_hash_function(std::string(sp.str_tolower(Key))) % currentTableSize;

    wordPod wP{Fileindex, Lineindex, Linenumber};
    insert(Key, wP, index);
    numItemsInTable++;
}

void tripHashTable::insert(std::string &Key, const wordPod &wp, size_t index) {
    hashNode *node = mytable[index];
    // first check if it's in an existing list
    while (node != nullptr) {
        if (node->key == Key) {
            node->podset.insert(wp);
            return;
        }
        node = node->next;
    }

    // if no list or not in existing list, make a new node and push to front.
    hashNode *hn = new hashNode(Key);
    hn->podset.insert(wp);
    hn->next       = mytable[index];
    mytable[index] = hn;
}


void tripHashTable::get(std::string Key, bool insensitive,
                        std::vector<wordPod> &wps) {
    std::string lower_key = std::string(sp.str_tolower(Key));

    size_t index = my_hash_function(std::string(lower_key)) % currentTableSize;
    hashNode *curr = mytable[index];

    while (curr != nullptr) {
        if (insensitive ? (sp.str_tolower(curr->key) == lower_key)
                        : (curr->key == Key)) {
            for (auto &wp : curr->podset)
                wps.push_back(wp);
        }
        curr = curr->next;
    }
}

// prints the formatted table. NOT USED, TODO DELETE IF DEAD
void tripHashTable::printTable(std::ostream &out) {
    (void)out;
}
void tripHashTable::expand() {
    // make a new array!
    size_t oldsize  = currentTableSize;
    numItemsInTable = 0;
    // set currentTableSize to be new array size
    currentTableSize *= 2;

    hashNode **oldTable = mytable;

    mytable = new hashNode *[currentTableSize];

    for (size_t i = 0; i < currentTableSize; ++i) {
        mytable[i] = nullptr;
    }

    // make a new array! (done)
    // set currentTableSize to be new array size (done)
    // for item in array, go down its list until you hit nullptr (while)

    for (size_t i = 0; i < oldsize; ++i) {
        hashNode *curr = oldTable[i];
        while (curr != nullptr) {
            for (auto &wp : curr->podset) {
                insert(curr->key, wp.fileindex, wp.lineindex, wp.linenumber);
            }
            curr = curr->next;
        }
    }

    // insert each of them into the new array. this handles collisions;
    // note that chaining may be different but this shouldn't matter

    for (size_t i = 0; i < oldsize; i++) {
        deleteList(oldTable[i]);
        oldTable[i] = nullptr;
    }

    delete[] oldTable;
}
