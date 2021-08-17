/* RPNCalc.h 
 *
 * COMP 15 Project 1
 * by Roger A. Burtonpatel, 3/12/2021
 * 
 * Purpose: Main class for CalcYouLater program. 
 * Does simple integer calculations. 
 * Contains a private instance of the DatumStack class, which serves 
 * as the "storage" of the CalcYouLater. This class is an excellent
 * choice for anyone looking to perform Reverse Polish Notation (RPN)
 * calculations through the command line and doesn't want to use dc, 
 * or wants to read in files of RPN commands as well as hold them 
 * in custom strings. 
 * 
 * An RPNCalc class instance represents an interactive RPN calculator. Every 
 * new RPNCalc begins as an empty stack of Datums (which may contain ints,  
 * booleans, or rstrings), and clients can then add and remove
 * Datums from the top of the stack using a list of functions.
 * The first element of the stack may also be accessed, and the 
 * stack may be cleared. Files may be opened and read from from rstrings, 
 * and several 'special' commands may be performed. (See: RPNCalc.cpp).
 * 
 * Implementer's note: This is implemented using a stack and a while loop. 
 */

#ifndef RPNCALC_H
#define RPNCALC_H

#include <iostream>
#include "Datum.h"
#include "DatumStack.h"

class RPNCalc {
public: 
        RPNCalc();
        ~RPNCalc(); 
        void run();


private: 
        void run_stream(std::istream &input_stream); 
        void rpn_num(int value); 
        void rpn_t(); 
        void rpn_f(); 
        void rpn_not();
        void rpn_print();
        void rpn_clear();
        void rpn_drop();
        void rpn_dup();
        void rpn_swap();
        void rpn_quit();
        void rpn_math(std::string symbol);
        void rpn_plus();
        void rpn_minus();
        void rpn_mult();
        void rpn_div();
        void rpn_mod();
        void rpn_inequality(std::string symbol); 
        void rpn_lessThan();
        void rpn_greaterThan();
        void rpn_lessEquals();
        void rpn_greaterEquals();
        void rpn_equals();
        void rpn_rstring(std::string rstring); 
        void rpn_exec();
        void rpn_file();
        void rpn_if();
        // free functions created previously in .cpp files 
        std::string parseRString(std::istream &input_stream); 
        std::size_t max_length(char *c_strs[], int len);
        bool got_int(std::string s, int *resultp);

        bool full_stop;
        
        DatumStack newDatumStack; 
};


#endif
