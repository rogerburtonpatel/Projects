/* parser.cpp 
 * 
 * COMP 15 Project 1
 * by Roger A. Burtonpatel, 3/07/2021
 * 
 * Parses an rstring from a given input (either cin or a file read)
 * and returns it as a string. 
 * 
 * Called after the first open brace ("{") is read by the CalcYouLater
 * program. 
 *  
 * Notes: this implementation uses an iterative method, but was originally 
 * written using recursion. I'd like to be graded for Phase 1 on the iterative 
 * technique (included code), but the recursive code is included, commented-
 * out, if you wish to look at it. My choice is explained in further detail 
 * below. 
 * 
 */ 

#include <iostream>
using namespace std; 


string parseRString(istream &input)
{
    int num_open = 1; 
    int num_close = 0; 
    string myRString = "{ "; 
    string newChunk; 
    while (num_open != num_close and not input.fail()) {
        input >> newChunk; 
        myRString += newChunk + " "; 
        if (newChunk == "{") 
            num_open++; 
        if (newChunk == "}")
            num_close++; 
    }
    return myRString; 
}
    // string myRString = "{ "; 
    // string newChunk; 
    // while (newChunk != "}" and not input.fail()) {
    //     input >> newChunk; 
    //     if (newChunk == "{") {
    //         myRString += parseRString(input); 
    //     }
    //     else {
    //         myRString += newChunk + " "; 
    //     }
    // }
//     return myRString; 
// }

// Above is my original solution to parseRString, which uses recursion. 
// Please see the parser.cpp description in the README Files section 
// on why I chose to use iteration for this submission. If you would
// like to test it out, comment out lines  26-39 and comment in lines 40-52.
 
// If you would like to see the (potential) problem with recursion, 
// change the target filename for the file stream in main.cpp 
// from "rStringTest.cyl" to "rStringTestExtraBrace.cyl." 
// Then make and run the program with both forms of parser.cpp. 
// It is clear that the iterative solution is functional, albeit 
// verbose, while the recursive solution does not work at all. 
// I know this may not matter at all, since we won't DIRECTLY 
// read from a file into the function but rather call it after
// reading after the first { in a file, but I wanted to be sure.  

// Please feel free to test either solution with either file. 

// Lastly, it is stated in the README, but I would like to be graded on 
// the iterative (top) solution. 
