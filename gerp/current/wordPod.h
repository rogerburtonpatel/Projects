#ifndef WORDPOD_H
#define WORDPOD_H

/*
 * @Overview: 
 *          Hashable container for a couple of values related to words stored 
 *          in a data structure. Really just a holder for 3 size_t's, though 
 *          the comparision operator is of some interest to make comparison
 *          cheaper for the particular implementation in which this 
 *          container is used.
 * 
 * @Purpose: Store lineindex, linenumber, and fileindex of words in the 
 *           tripHashTable.  
 * @Use: within unordered_sets contained in the hashNodes of the tripHashTable.
 * 
 * @implementation-note: Comparison only compares lineindex since within 
 *                       we can exclude duplicates based on this parameter 
 *                       only. Within a hashNode, there is a word an a set of
 *                       wordPods. For duplicate-checking within the set, 
 *                       duplicates only concern themselves within lineindex,
 *                       since linenumber and fileindex will always be the same
 *                       in that case. 
 * 
 * @Author: rab
 * 
 * @chlog: 1/3/2022:  creation and initialization for modularity 
 *         1/18/2022: extensive documentation and 2 major changes: 
 *                     1. == operator now only checks lineindeces
 *                     2. because of this, hash operator () need only 
 *                        use lineindex as the hash value, since these values
 *                        are guarenteed to be unique within the set. 
 *                      
 * 
 */


#include <functional>
#include "stringProcessing.h"

struct wordPod {
    size_t fileindex;
    size_t lineindex; 
    size_t linenumber; 

    bool operator==(const wordPod& wp) const {
        return (this->lineindex == wp.lineindex);
    }
    
    /* since there can never be duplicate lineindeces within the set
        of wordPods, we don't even need to hash. The raw value is fast,
        consistant, and unique, making it the perfect hash value. */
    size_t operator()(const wordPod& wp) const {
        return wp.lineindex;
    }
};

#endif