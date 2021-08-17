/* DatumStack.cpp 
 * 
 * COMP 15 Project 1
 * by Roger A. Burtonpatel, 3/07/2021
 * 
 * Stores Datums (from Datum class) in a certain stack. Allows 
 * for addition and subtraction at the top of the stack, and referencing
 * of the top Datum. To create a new DatumStack, call the 
 * constructor, either with no arguments or with an array of Datums and 
 * its length. Then, begin adding Datums using push() and pop().
 * The stack may also be cleared. 
 * 
 * Notes: this implementation uses a stack. So, it is limited in its 
 * functionality: it can only add and remove at the front of the list
 * and reference the first element (as well as call helper functions such
 * as size()). Its limitation, however, is its strength, since it doesn't
 * need to do anything other than perform these tasks. 
 *
 */  

#include "DatumStack.h"
#include <iostream> 
#include <exception> 

/*
* Constructor for DatumStack class 
* Purpose: Instantiates an empty instance of DatumStack 
* Parameters: none 
* Returns:    none 
*/ 

DatumStack::DatumStack()
{
    len = 0;
}

/*
* Constructor for DatumStack class 
* Purpose: Instantiates an filled instance of DatumStack, based 
* on an array and length input.  
* Parameters: an array of Datums to fill the stack with and the 
* length of the array. 
* Returns: none 
*/ 

DatumStack::DatumStack(Datum *arr, int initial_size)
{
    len = initial_size; 
    for (int i = 0; i < initial_size; ++i) {
        newDatumVector.push_back(arr[i]);
    }
}

/*
* Destructor for DatumStack class 
* Purpose: Clears the DatumStack.  
* Parameters: none 
* Returns:    none 
*/ 

DatumStack::~DatumStack()
{
    clear(); 
}

/*
* Verifies emptiness of DatumStack
* Purpose: Checks if a given DatumStack is empty
* Parameters: none 
* Returns: true if the DatumStack is empty. 
*/ 
bool DatumStack::isEmpty() const
{
    return size() == 0; 
}


/*
* Clearer of a DatumStack. 
* Purpose: Removes all elements of a DatumStack and sets its length to zero.
* Parameters: none 
* Returns:    none 
*/ 
void DatumStack::clear()
{
    for (Datum d : newDatumVector)
        newDatumVector.pop_back();
    len = 0; 
}

/*
* getter function for private variable len for a DatumStack 
* Purpose: gets the length of a DatumStack 
* Parameters: none 
* Returns: len of given DatumStack
*/ 
int DatumStack::size() const
{
    return len; 
}


/*
* getter function for top element of a DatumStaack 
* Purpose: gives the Datum at the top of the stack 
* Parameters: none 
* Returns: the topmost Datum  
*/ 
Datum DatumStack::top() const 
{
    if (isEmpty())
        throw std::runtime_error("empty_stack"); // DatumStack_tests can 
                                                 // catch this error 
    else 
        return newDatumVector.at(size() - 1);
}


/*
* pop (top removal) function for DatumStack 
* Purpose: removes a given Datum from the top of the stack
* Parameters: none 
* Returns: none 
*/ 
void DatumStack::pop()
{
    if (isEmpty())
        throw std::runtime_error("empty_stack"); // DatumStack_tests can 
                                                 // catch this error 
    else {
        newDatumVector.pop_back();
        len--; 
    }
}


/*
* push (top addition) function for DatumStack 
* Purpose: adds a given Datum to the stack on the top  
* Parameters: a Datum to be pushed 
* Returns: none 
*/ 
void DatumStack::push(Datum new_top)
{
    len++; 
    newDatumVector.push_back(new_top);
}
