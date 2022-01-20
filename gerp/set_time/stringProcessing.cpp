/*
 * @Overview: 
 * driver for stringProcessing class, which exists for function 
 * stripNonAlphaNum. Details of the function can be found in the header of 
 * stringProcessing.h. 
 * 
 * tests function in a unit-testing style using cassert library. 
 * 
 * @Author: Roger A. Burtonpatel 
 * @chlog: 12/28/2021: creation and instantiation. first developed a 
 *                     recursive solution, then formed one with two 
 *                     while loops. 
 *
 */

#include <iostream>
#include <cassert>
#include <cctype> 
#include "stringProcessing.h"

std::string stringProcessing::stripNonAlphaNum(std::string s)
{
    while (not iswalnum(s[0]) and not s.empty()) {
        s.erase(0, 1);
    }
    while (not iswalnum(s[s.size() -1]) and not s.empty()) {
        s.pop_back();
    }
    return s;    
    
    // recursive solution. 

    // bool start = false, end = false;
    //     if (not iswalnum(s[0])) {
    //         s.erase(0, 1);
    //     }
    //     else {
    //         start = true;
    //     }

    //     if (not iswalnum(s[s.size() -1])) {
    //         s.pop_back();
    //     }
    //     else {
    //         end = true;
    //     }

    //     if ((not start) or (not end)) {
    //         return stripNonAlphaNum(s);
    //     }
    //     else return s;
}

std::string stringProcessing::str_tolower(std::string s)
{
    
    std::string lowerized = "";
    for(auto c : s) {
    lowerized += tolower(c);
    }
    return lowerized;
}