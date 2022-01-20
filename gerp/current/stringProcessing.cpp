/*
 * @Overview: 
 * driver for stringProcessing class, which defines functions stripNonAlphaNum()
 * and str_tolower(). Brief details of the functions can be found in the 
 * header of stringProcessing.h. 
 * 
 * 
 * @Author: rab
 * @chlog: 12/28/2021: creation and instantiation. first developed a 
 *                     recursive solution, then formed one with two 
 *                     while loops. 
 *          1/18/2022: extensive documentation
 *
 */

#include <iostream>
#include <cctype> 
#include "stringProcessing.h"

/*
 @name:    stripNonAlphaNum
 
 @args:    a string s to be functionally stripped.
 
 @returns: a string which is s stripped of all leading and trailing non-alpha-
           numeric characters. 
           
 @purpose: takes a string s and returns a new string that is s with all leading 
           and trailing non-alpha-numeric (i.e. non a-z, 0-9) characters
           removed. This does not affect s. 
*/
std::string stringProcessing::stripNonAlphaNum(std::string s)
{
        /* recursive solution. */

    if (s.empty()) return s;

    if (iswalnum(s[0]) and iswalnum(s[s.size() - 1])) return s; 
    
    if (not iswalnum(s[0])) {
        s.erase(0, 1);
        return stripNonAlphaNum(s);
    }
    else {
        s.pop_back();
        return stripNonAlphaNum(s);
    }
    /* iterative solution-- 
    this would be much better with a short circuit, but comp15 doesn't 
    alllow double &! */

    /*
    if (not s.empty()) {
        while (not iswalnum(s[0]) and not s.empty()) {
            s.erase(0, 1);
        }
        while (not iswalnum(s[s.size() -1]) and not s.empty()) {
            s.pop_back();
        }
    }
    return s;    
    */

    /* another recursive solution */

    /*  bool start = false, end = false;
        if (not iswalnum(s[0])) {
            s.erase(0, 1);
        }
        else {
            start = true;
        }

        if (not iswalnum(s[s.size() -1])) {
            s.pop_back();
        }
        else {
            end = true;
        }

        if ((not start) or (not end)) {
            return stripNonAlphaNum(s);
        }
        else return s;
    */
}

/*
 @name:     str_tolower 
 @args:     a string s to be functionally lowercase-ized.
 @returns:  a string which is s such that all of its characters are in 
            their lowercase forms.
    
 @purpose:  takes a string s and returns a new string which is with all of its 
            characters in lowercase form. this does not affect the original 
            string.
*/
std::string stringProcessing::str_tolower(std::string s)
{
    std::string lowerized = "";
    for(auto c : s) {
    lowerized += tolower(c);
    }
    return lowerized;
}