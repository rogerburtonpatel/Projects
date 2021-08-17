/* DatumStack_tests.cpp
 * 
 * COMP 15 Project 1
 * by Roger A. Burtonpatel, 3/09/2021
 *
 * Uses Matt Russell's unit_test framework to test the DatumStack. 
 */

#include "DatumStack.h"
#include <iostream> 
#include <cassert>

/*
* Creates an instance of the DatumStack class. 
* Tests the nullary constructor. 
* Parameters: none 
* Returns:    none 
* 
* Tester's note: should pass with no output 
*/ 

void DS_construct()
{
    DatumStack newDS; 
}

/*
* Creates an instance of the DatumStack class with parameters. 
* Tests the multi-Datum constructor. 
* Parameters: none 
* Returns:    none 
* 
* Tester's note: should pass with no output 
*/ 

void DS_construct_params()
{
    Datum d1(5);
    Datum d2(true);
    Datum(d3)("{ 1 2 }");

    Datum arr[3] = {d1, d2, d3}; 

        DatumStack newDS(arr, 3); 
}

/*
* Creates an instance of the DatumStack class. 
* Tests the destructor.  
* Parameters: none 
* Returns:    none 
* 
* Tester's note: should pass with no output 
*/ 
void DS_destruct()
{
    DatumStack newDS; 
}

/*
* Creates two instances of the DatumStack class and runs 
* isEmpty() on them (one empty and one not), using assert to 
* verify expected outputs. 
* Tests isEmpty(). 
* Parameters: none 
* Returns:    none 
* 
* Tester's note: should pass with no output 
*/ 
void DS_isEmpty()
{   
    Datum d1(5);
    Datum d2(true);
    Datum(d3)("{ 1 2 }");

    Datum arr[3] = {d1, d2, d3}; 

    DatumStack newDS; 
    DatumStack newDS2(arr, 3);

    assert(newDS.isEmpty());
    assert(not newDS2.isEmpty()); 

}

/*
* Creates two instances of the DatumStack class and calls clear on them. 
* Asserts they are empty. 
* Tests clear(). 
* Parameters: none 
* Returns:    none 
* 
* Tester's note: should pass with no output 
*/ 

void DS_clear()
{
    Datum d1(5);
    Datum d2(true);
    Datum(d3)("{ 1 2 }");

    Datum arr[3] = {d1, d2, d3}; 

    DatumStack newDS; 
    DatumStack newDS2(arr, 3);

    newDS.clear();
    newDS2.clear();
    assert(newDS.isEmpty());
    assert(newDS2.isEmpty()); 
}

/*
* Creates two instances of the DatumStack class and asserts their size. 
* Then clears them and reassesses their size. 
* Tests size(). 
* Parameters: none 
* Returns:    none 
* 
* Tester's note: should pass with no output 
*/ 

void DS_size()
{
    Datum d1(5);
    Datum d2(true);
    Datum(d3)("{ 1 2 }");

    Datum arr[3] = {d1, d2, d3}; 

    DatumStack newDS; 
    DatumStack newDS2(arr, 3);

    assert(newDS.size() == 0);
    assert(newDS2.size() == 3); 
    newDS.clear();
    newDS2.clear();
    assert(newDS.size() == 0);
    assert(newDS2.size() == 0); 
}

/*
* Creates two instances of the DatumStack class and calls top() on each. Then 
* clears them and calls top() again on each. Asserts top is expected "d3" for 
* the multi-Datum instance. Catches thrown errors when called on an empty 
* stack. 
* Tests top(). 
* Parameters: none 
* Returns:    none 
* 
* Tester's note: should pass with three "Error: empty_stack" messages. 
*/ 
void DS_top()
{
    Datum d1(5);
    Datum d2(true);
    Datum(d3)("{ 1 2 }");
    Datum arr[3] = {d1, d2, d3}; 
    DatumStack newDS; 
    DatumStack newDS2(arr, 3);
    try {
        newDS.top();  // will print an error message and continue 
    }
    catch(std::runtime_error error_message) {
        std::cerr << "Error: " << error_message.what() << std::endl; 
    }
    assert(newDS2.top() == d3); 
    newDS.clear();
    newDS2.clear();
    
    try {
        newDS.top();  // will print an error message and continue 
    }
    catch(std::runtime_error error_message) {
        std::cerr << "Error: " << error_message.what() << std::endl; 
    }
    try {
        newDS2.top();  // will print an error message and continue 
    }
    catch(std::runtime_error error_message) {
        std::cerr << "Error: " << error_message.what() << std::endl; 
    }
}


/*
* Creates two instances of the DatumStack class and calls pop() on each.
* Asserts top() and size() are expected values when popping from a 
* multi-Datum stack. 
* Catches thrown errors when called on an empty stack. 
* Tests pop(). 
* Parameters: none 
* Returns:    none 
* 
* Tester's note: should pass with two "Error: empty_stack" messages. 
*/ 
void DS_pop()
{
    Datum d1(5);
    Datum d2(true);
    Datum(d3)("{ 1 2 }");
    Datum arr[3] = {d1, d2, d3}; 
    DatumStack newDS; 
    DatumStack newDS2(arr, 3);
    try {
        newDS.pop();  // will print an error message and continue 
    }
    catch(std::runtime_error error_message) {
        std::cerr << "Error: " << error_message.what() << std::endl; 
    }
    newDS2.pop();
    assert(newDS2.top() == d2);
    assert(newDS2.size() == 2);  
    newDS2.pop();
    assert(newDS2.top() == d1);
    assert(newDS2.size() == 1); 
    newDS2.pop();
    assert(newDS2.isEmpty()); 

    try {
        newDS2.pop();  // will print an error message and continue 
    }
    catch(std::runtime_error error_message) {
        std::cerr << "Error: " << error_message.what() << std::endl; 
    }
}


/*
* Creates two instances of the DatumStack class and calls push() on each
* Asserts top and size are expected values after each call in the 
* multi-Datum instance. Also calls pop() to test edge interactions with 
* push(). Catches thrown errors when calling pop() on an empty stack. 
* Tests push(). 
* Parameters: none 
* Returns:    none 
* 
* Tester's note: should pass with one "Error: empty_stack" messages. 
*/ 
void DS_push()
{
    Datum d1(5);
    Datum d2(true);
    Datum(d3)("{ 1 2 }");
    Datum arr[3] = {d1, d2, d3}; 
    DatumStack newDS; 
    DatumStack newDS2(arr, 3);

    newDS.push(d1);
    assert(newDS.size() == 1);
    assert(newDS.top() == d1);
    newDS.pop(); 

    newDS2.pop();
    newDS2.pop();
    newDS2.push(d3);
    assert(newDS2.top() == d3);
    assert(newDS2.size() == 2);
    newDS2.pop();
    assert(not newDS2.isEmpty()); 
    newDS2.pop();

    try {
        newDS2.pop();  // will print an error message and continue 
    }
    catch(std::runtime_error error_message) {
        std::cerr << "Error: " << error_message.what() << std::endl; 
    }    
}
