/*
 * @Overview: 
 * class for function stripNonAlphaNum, which takes a string and strips 
 * all leading and trailing non-alphanumeric characters. For example, 
 * !@#%&^COMP-15@$ would be stripped to COMP-15. 
 * 
 * @Author: Roger A. Burtonpatel 
 * @chlog: 12/28/2021: creation and instantiation 
 *
 */

#include <string>

class stringProcessing {

public: 
    std::string stripNonAlphaNum(std::string s);
    std::string str_tolower(std::string s);
};