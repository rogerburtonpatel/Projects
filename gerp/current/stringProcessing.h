#ifndef STRINGPROCESSING_H
#define STRINGPROCESSING_H

/*
 * @Overview: 
 * class for: 
 * a. function stripNonAlphaNum(), which takes a string and strips 
 * all leading and trailing non-alphanumeric characters. For example, passing in
 * !@#%&^COMP-15@$ would return COMP-15. 
 * b. function str_tolower(), which takes a string and returns a lowercased
 *    version of that string. For example, passing in tEsTStrInG01 
 *    returns teststring01 .
 * 
 * @Purpose: for stripping down strings and obtaining lowercase versions 
 *           thereof.
 * @Use:     in programs that need a few helpful string-processing functions.
 * 
 * @Note:    the functions in this library are 'functional' and do not affect
 *           the original string parameters in any way.
 * 
 * @Author: rab
 * @chlog: 12/28/2021: creation and instantiation 
 *          1/18/2022: extensive documentation
 *
 */

#include <string>

class stringProcessing {

public: 
    /* takes a string s and returns a new string that is s with all leading 
        and trailing non-alpha-numeric (i.e. non a-z, 0-9) characters
        removed. This does not affect s. */
    std::string stripNonAlphaNum(std::string s);

    /* takes a string s and returns a new string which is with all of its 
       characters in lowercase form. */
    std::string str_tolower(std::string s); 
};

#endif