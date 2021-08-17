/* DatumStack.h 
 *
 * COMP 15 Project 1
 * by Roger A. Burtonpatel, 3/07/2021
 * 
 * Purpose: Holds Datums, which can contain 
 * ints, booleans, or RPNstrings, on a stack, and allows for their access. 
 * 
 * A DatumStack class instance represents an ordered list of 
 * Datum instances. Every new DatumStack begins empty or pre-filled
 * with an array of Datums, and clients can then add and remove
 * Datums from the top of the stack using push() and pop() functions.
 * The first element of the stack may also be accessed, and the 
 * stack may be cleared.  
 * 
 * Implementer's note: This is implemented using a vector.
 */

#ifndef DATUMSTACK_H
#define DATUMSTACK_H

#include <vector>
#include "Datum.h"

class DatumStack {
public: 

        DatumStack(); 
        DatumStack(Datum arr[], int inital_size); 
        ~DatumStack(); 
        bool isEmpty()      const; 
        void clear();
        int size()          const; 
        Datum top()         const; 
        void pop();
        void push(Datum new_top); 


private:

        std::vector<Datum> newDatumVector; 
        int len; 
    
};

#endif 
