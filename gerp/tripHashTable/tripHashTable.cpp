// TODO add header and contracts 

#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include "tripHashTable.h"

tripHashTable::tripHashTable() {
    currentTableSize = INTIAL_TABLE_SIZE;
    numItemsInTable  = 0;

    mytable = new hashNode *[currentTableSize];
    for (int i = 0; i < currentTableSize; i++) {
            mytable[i]        = nullptr;
    }
}

tripHashTable::~tripHashTable() {
            for (int i = 0; i < currentTableSize; ++i) {
                deleteList(mytable[i]);
                mytable[i]        = nullptr;
        }       

        delete [] mytable;
}

void tripHashTable::deleteList(hashNode *node) {
    if (node == nullptr) return;
        deleteList(node->next);
        delete node;
}

void tripHashTable::insert(std::string Key, std::string Filepath, 
                                      size_t Index, int Linenumber) {
    if ((double)numItemsInTable / currentTableSize >= 0.7) {
            expand(); 
    }
    size_t index = my_hash_function(std::string(Key)) % currentTableSize;
    
    // this sets hn->next to mytable[index] within the constructor
    hashNode *hn = new hashNode(Key, Filepath, Index, 
                                                    Linenumber, mytable[index]);

    mytable[index] = hn;
}

std::vector<wordPod> tripHashTable::get (std::string Key) {
    size_t index = my_hash_function(std::string(Key)) % currentTableSize;
    std::vector<wordPod> wps; 
    hashNode *curr = mytable[index];

    while (curr != nullptr) {
        if (curr->key == Key) {
            wps.push_back(curr->value);
            curr = curr->next;
        }
    }
    return wps;
}
// prints the formatted value and key of a word. NOT USED, TODO DELETE IF DEAD
// void tripHashTable::printWord(std::string word, std::ostream &out) {
//     std::vector<wordPod> wps = get(word);
//     for (auto wp : wps) {
//         out << wp.filepath << ":" << wp.linenumber << ":" << wp.index << std::endl;
//     }

// }

void tripHashTable::expand() {
        // make a new array! 
        int oldsize = currentTableSize; 
        // set currentTableSize to be new array size 
        currentTableSize *= 2;

        hashNode **oldTable = mytable;

        mytable = new hashNode *[currentTableSize];

        for (int i = 0; i < currentTableSize; ++i) {
                mytable[i]         = nullptr;
        }

        // make a new array! (done)
        // set currentTableSize to be new array size (done)
        // for item in array, go down its list until you hit nullptr (while)

        for (int i = 0; i < oldsize; ++i) {
                hashNode *curr = oldTable[i];
                while (curr != nullptr) {
                        insert(curr->key, curr->value.filepath, 
                        curr->value.index, curr->value.linenumber);
                        curr = curr->next;
                }
        }

        // insert each of them into the new array. this handles collisions; 
        // note that chaining may be different but this shouldn't matter 

        for (int i = 0; i < currentTableSize; i++) {
                deleteList(oldTable[i]);
                oldTable[i]        = nullptr;
        }       

        delete [] oldTable;
}

