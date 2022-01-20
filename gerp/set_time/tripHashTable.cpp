// TODO add header and contracts 

#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <cctype> // for lowercasing 
#include "tripHashTable.h"

tripHashTable::tripHashTable()
{
    currentTableSize = INTIAL_TABLE_SIZE;
    numItemsInTable  = 0;
    mytable = new std::unordered_set<wordPod, wordPod> [currentTableSize];
}

tripHashTable::~tripHashTable()
{
    // for (int i = 0; i < currentTableSize; ++i) {
    //     mytable[i].clear();
    //     }
        delete [] mytable;
}

void tripHashTable::insert(std::string Key, std::string Filepath, 
                                      size_t Index, int Linenumber)
{
    if ((double)numItemsInTable / (double)currentTableSize >= 0.7) {
            expand(); 
    }
    Key = sp.stripNonAlphaNum(Key);
    size_t index = my_hash_function(std::string(sp.str_tolower(Key)))
                                                            % currentTableSize;

    wordPod wP {Key, Filepath, Index, Linenumber};
    mytable[index].insert(wP);

    numItemsInTable++;
}

std::vector<wordPod> tripHashTable::get(std::string Key, bool insensitive)
{
    std::string lower_key = std::string(sp.str_tolower(Key)); 
    // keys are hashed and retrieved from a bucket based on their lowercase
    // forms. 
    size_t index = my_hash_function(std::string(lower_key)) % currentTableSize;
    std::vector<wordPod> wps;

    for (auto wp : mytable[index]) {
        if (insensitive ? 
            (sp.str_tolower(wp.word) == lower_key) : (wp.word == Key)) {
            wps.push_back(wp);
        }
    }

    return wps;
}
// for debugging TODO REMOVE IF NOT NEEDED 
void tripHashTable::printWord(std::string word, std::ostream &out)
{
    std::vector<wordPod> wps = get(word, false);
    for (auto wp : wps) {
        out << wp.filepath << ":" << wp.linenumber << ":" << wp.v_index << 
                                                    " " << wp.word << std::endl;
    }
}

void tripHashTable::printTable(std::ostream &out)
{
    for (size_t i = 0; i < (size_t)currentTableSize; ++i) {
        for (auto wp : mytable[i]) {
            out << wp.filepath << ":" << wp.linenumber << ":" << wp.v_index << 
                                                " " << wp.word << std::endl;
        }
    }
}

void tripHashTable::expand()
{
        // make a new array! 
        int oldsize = currentTableSize; 
        // set currentTableSize to be new array size 
        currentTableSize *= 2;

        std::unordered_set<wordPod, wordPod> *oldTable = mytable;

        mytable = new std::unordered_set<wordPod, wordPod> [currentTableSize];

        // make a new array! (done)
        // set currentTableSize to be new array size (done)
        // for item in array, go down its list until you hit nullptr (while)

        for (int i = 0; i < oldsize; ++i) {
                for (auto wp : oldTable[i]) {
                    insert(wp.word, wp.filepath, wp.v_index, wp.linenumber);
                }
        }

        // insert each of them into the new array. this handles collisions; 
        // note that chaining may be different but this shouldn't matter 

        for (int i = 0; i < oldsize; i++) {
                oldTable[i].clear();
        }       

        delete [] oldTable;
}

