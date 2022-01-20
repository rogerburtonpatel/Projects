// TODO add header and contracts 

#include <functional>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include "tripHashTable.h"

tripHashTable::tripHashTable()
{
    currentTableSize = INITIAL_TABLE_SIZE;
    numItemsInTable  = 0;
    mytable = new std::unordered_set<wordPod, wordPod> [currentTableSize];
}

tripHashTable::~tripHashTable()
{
    // for (size_t i = 0; i < currentTableSize; ++i) {
    //     mytable[i].clear();
    //     }
        delete [] mytable;
}

// tripHashTable::tripHashTable(const tripHashTable &other) 
// {
//     currentTableSize = INITIAL_TABLE_SIZE;
//     numItemsInTable  = 0;
//     mytable = nullptr; 
    
//     if (not (other.numItemsInTable == 0)) {
//         mytable = new std::unordered_set<wordPod, wordPod>; 
//         *mytable = *other.mytable; 

//         // push each item from the other list onto this one
//         for (size_t i = 0; i < other.currentTableSize; ++i) {
//                 for (auto wp : other.mytable[i]) {
//                     insert(wp.word, wp.fileindex, wp.lineindex, wp.linenumber);
//                 }
//         }
//     }
// }

// tripHashTable &tripHashTable::operator =(const tripHashTable &rhs) 
// {
//     if (this != &rhs) {
//         for (size_t i = 0; i < currentTableSize; ++i) {
//         mytable[i].clear(); // clear all cells
//         }
//         currentTableSize = rhs.currentTableSize;
//         numItemsInTable = 0;
//         // add each element from the other table into this one
//         for (size_t i = 0; i < rhs.currentTableSize; i++) {
//             for (auto wp : rhs.mytable[i]) {
//             insert(wp.word, wp.fileindex, 
//                    wp.lineindex, wp.linenumber);
//             }
//         }
//     }
//     return *this;
// }

void tripHashTable::insert(const std::string &Key, const size_t &Fileindex, 
                                      const size_t &Lineindex, const size_t &Linenumber)
{
    if ((double)numItemsInTable / (double)currentTableSize >= 0.8) {
            expand(); 
    }
    std::string temp_Key = sp.stripNonAlphaNum(Key);
    size_t index = my_hash_function(std::string(sp.str_tolower(temp_Key)))
                                                            % currentTableSize;

    wordPod wP {temp_Key, Fileindex, Lineindex, Linenumber};
    mytable[index].insert(wP);

    numItemsInTable++;
}

std::vector<wordPod> tripHashTable::get(const std::string &Key, const bool &insensitive)
{
    std::string lower_key = std::string(sp.str_tolower(Key)); 
    // keys are hashed and retrieved from a bucket based on their lowercase
    // forms. 
    size_t index = my_hash_function(std::string(lower_key)) % currentTableSize;
    std::vector<wordPod> wps;

    for (const auto & wp : mytable[index]) {
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
    for (const auto & wp : wps) {
        out << "WORD: " << wp.word 
            << ". LINEINDEX: " << wp.lineindex 
            << ". LINENUMBER: " << wp.linenumber 
            << ". FILEINDEX: " << wp.fileindex 
            << "\n";
    }
}

void tripHashTable::printTable(std::ostream &out)
{
    for (size_t i = 0; i < currentTableSize; ++i) {
        for (const auto & wp : mytable[i]) {
            out << "WORD: " << wp.word 
                << ". LINEINDEX: " << wp.lineindex 
                << ". LINENUMBER: " << wp.linenumber 
                << ". FILEINDEX: " << wp.fileindex 
                << "\n";
        }
    }
}

// void tripHashTable::printBuckets(std::ostream &out)
// {
//     for (size_t i = 0; i < currentTableSize; ++i) {
//         out << "BUCKETCOUNT AT INDEX " << i << " = " 
//             << mytable[i].bucket_count() << "\n";
//         for (size_t j = 0; j < mytable[i].bucket_count(); ++j) {
//             out << "MAXBUCKETSIZE AT BUCKET " << j << " = " 
//                 << mytable[i].bucket_size(j)  << "\n";
//         }
//     }
// }

// void tripHashTable::checkLargeBuckets(std::ostream &out)
// {
//     for (size_t i = 0; i < currentTableSize; ++i) {
//         // if (mytable[i].bucket_count() > 13) {
//         // out << "BUCKETCOUNT AT INDEX " << i << " = " 
//         //     << mytable[i].bucket_count() << "\n";
//         // }

//         for (size_t j = 0; j < mytable[i].bucket_count(); ++j) {
//             if (mytable[i].bucket_size(j) > 80) {
//             out << "MAXBUCKETSIZE AT BUCKET " << j << " = " 
//                 << mytable[i].bucket_size(j)  << "\n";
//             // out << "LOADFACTOR = " << mytable[i].load_factor() << "\n";
//             }

//         }
//     }
// }

void tripHashTable::expand()
{
        // make a new array! 
        size_t oldsize = currentTableSize; 
        // set currentTableSize to be new array size 
        currentTableSize += (currentTableSize / 2);

        std::unordered_set<wordPod, wordPod> *oldTable = mytable;
        // try {
            mytable = 
                new std::unordered_set<wordPod, wordPod> [currentTableSize];

        // }
        // catch (std::bad_alloc e)
        // {
        //     std::cerr << e.what() << "\n";
        //     std::cerr << "currentTableSize = " << currentTableSize << "\n";
        //     std::cerr << "oldsize = " << oldsize << "\n";
        //     std::cerr << "currentTableSize + oldsize = "
        //      << (currentTableSize + oldsize) << "\n";

        //     delete [] oldTable; 
        //     exit(EXIT_FAILURE);
        // }

        // make a new array! (done)
        // set currentTableSize to be new array size (done)
        // for item in array, go through the set and re-insert it into the 
        // new table 

        // insert each of them into the new array. this handles collisions 
        // since everything is a set. 
        for (size_t i = 0; i < oldsize; ++i) {
                for (const auto & wp : oldTable[i]) {
                    insert(wp.word, wp.fileindex, wp.lineindex, wp.linenumber);
                }
        }
        delete [] oldTable;
}
