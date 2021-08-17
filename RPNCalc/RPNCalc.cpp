/* RPNCalc.cpp 
 * 
 * COMP 15 Project 1
 * by Roger A. Burtonpatel, 3/12/2021
 * 
 * Simulates a basic calculator that uses Reverse Polish Notation (RPN). 
 * Can perform integer calculation, compare values (including integers, 
 * booleans, and "rstrings"), and execute file commands. Does so by taking
 * commands from the command line. 
 * 
 * 
 * To create a new RPNCalc, call the constructor with no arguments. 
 * Then, begin executing commands as displayed in run_stream() below. 
 * 
 * Example commands: 
 * 
 * "5": pushes 5 onto the calculator stack 
 * "#t": pushes "true" onto the calculator stack
 * "{ 6 3 / print }": pushes an rstring onto the calculator stack 
 * "exec", "file", "if": perform special commands based on 
 * rstrings on the calculator stack. 
 * 
 * 
 * To quit, type "quit."
 * 
 * Notes: this calculator implementation uses a stack. So, it is limited in its
 * functionality: it can only add and remove at the front of the list
 * and reference the first element (as well as call helper functions such
 * as size()). Its limitation, however, is its strength, since it doesn't
 * need to do anything other than perform these tasks. 
 * 
 * Enjoy your CalcYouLations! 
 *
 */  

#include "RPNCalc.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <exception> 
#include <sstream> 
using namespace std;


/* 
 * Default constructor for RPNCalc
 * Purpose: Initializes an RPNCalc and runs. 
 * Parameters: none 
 * Returns:    none 
 */ 
RPNCalc::RPNCalc()
{
    run(); 
}


/* 
 * Destructor for RPNCalc
 * Purpose: Clears the RPNCalc after use. 
 * Parameters: none 
 * Returns:    none 
 */ 
RPNCalc::~RPNCalc()
{
    rpn_clear(); 
}


/* 
 * Public run function of RPNCalc. 
 * Purpose: Executes private run loop using cin as an input. 
 * Parameters: none 
 * Returns:    none 
 */ 
void RPNCalc::run()
{
    run_stream(cin); 
}

/* 
 * Run engine of an RPNCalc instance
 * Purpose: Takes in commands from an input stream and excecutes RPNCalc
 * functions based on input. If user inputs "quit," quits the program. 
 * Parameters: none 
 * Returns:    none 
 */ 
void RPNCalc::run_stream(istream &input_stream)
{
    string input; 
    int value; 
    bool bracket_stop = false; 
    full_stop = false; 

    input_stream >> input; 

    while (not full_stop and not bracket_stop and not input_stream.fail()) {

        if (got_int(input, &value)) 
            rpn_num(value);

        else if (input == "#t")
            rpn_t(); 

        else if (input == "#f")
            rpn_f(); 

        else if (input == "not")
            rpn_not();

        else if (input == "print")
            rpn_print();

        else if (input == "clear")
            rpn_clear();

        else if (input == "drop")
            rpn_drop(); 

        else if (input == "dup")
            rpn_dup();

        else if (input == "swap")
            rpn_swap();

        else if (input == "+" or input == "-" or input == "*" 
           or input == "/" or input == "mod")
           rpn_math(input); // shortens the while loop somewhat 

        else if (input == "<" or input == ">" or input == "<=" or input == ">=")
           rpn_inequality(input); // shortens the while loop somewhat 
        
        else if (input == "==")
            rpn_equals(); 

        else if (input == "{") 
            rpn_rstring(parseRString(input_stream));
 
        else if (input == "exec")
           rpn_exec(); 

        else if (input == "}")
            bracket_stop = true; // edge case- so the program knows to stop 
                                 // reading from an input stream in 
                                 // parseRString (not including this results in
                                 // an extra bracket being added to the stack.)
        else if (input == "file")
           rpn_file(); 

        else if (input == "if")
           rpn_if();

        else if (input == "quit")
            rpn_quit();

        else // tells the user they shouldn't get clever with the CalcYouLater.
            cerr << input << ": unimplemented" << endl; 

    if (not full_stop)      // edge case - quitting within a file 
    input_stream >> input;  // caused one more input to be read. 
                            // with this guard, this no longer occurs. 

    } // end of while loop 

    // for special case of redirection of a text file into the program
    // such that the program reads input from the file (not using
    // implemented "file" command but rather the > operator in the 
    // command line). The reference prints the ending message to cerr
    // when the end of such a file is reached or cin is exited using
    // Ctrl + D. This is described in Piazza post @711 (The Slurpee 
    // capital of the world). 

    if (cin.fail())
        cerr << "Thank you for using CalcYouLater.\n";

}

/* 
 * Number pusher for RPNCalc
 * Purpose: Takes in a number and pushes it onto the stack as a Datum.
 * Parameters: an integer value to be pushed onto the stack as a Datum.
 * Returns:    none 
 */ 
void RPNCalc::rpn_num(int value) 
{
    Datum d(value);
    newDatumStack.push(d);
}

/* 
 * Boolean "true" pusher for RPNCalc
 * Purpose: Creates a "true" Datum and pushes it onto the stack.
 * Parameters: none
 * Returns:    none 
 */ 
void RPNCalc::rpn_t()
{
    Datum d(true);
    newDatumStack.push(d);
}

/* 
 * Boolean "false" pusher for RPNCalc
 * Purpose: Creates a "false" Datum and pushes it onto the stack.
 * Parameters: none
 * Returns:    none 
 */ 
void RPNCalc::rpn_f()
{
    Datum d(false);
    newDatumStack.push(d);
}

/* 
 * "not" operator for RPNCalc
 * Purpose: Reads top of stack and pops it. If boolean, pushes its 
 * inverse as a Datum. Otherwise, prints an error. If stack is empty, 
 * prints an error and continues having done nothing. 
 * Parameters: none
 * Returns:    none 
 */ 
void RPNCalc::rpn_not()
{  
    try {
        if (not newDatumStack.top().isBool()) {
            newDatumStack.pop();
            cerr << "Error: datum_not_bool\n"; 
            // will print an error message and continue 
            // if top Datum does not contain a boolean.
            // Will stil pop the Datum off the stack. 
        }

        else {
            if (newDatumStack.top().getBool() == true) {
                newDatumStack.pop();
                rpn_f();
            }
            else if (newDatumStack.top().getBool() == false) {
                newDatumStack.pop();
                rpn_t();
            }
        }
    }
    catch (runtime_error &error_message) {
        cerr << "Error: " << error_message.what() << endl; 
        // will print an error message and continue 
        // if stack is empty 
    }
}
/* 
 * "print" operator for RPNCalc
 * Purpose: Prints the top Datum of the stack. If stack is empty, 
 * prints an error and continues. 
 * Parameters: none
 * Returns:    none 
 */ 
void RPNCalc::rpn_print()
{
    try {

        if (newDatumStack.top().isInt()) {
            cout << newDatumStack.top().getInt() << endl; 
        }

        if (newDatumStack.top().isBool()) {
            if (newDatumStack.top().getBool() == true) {
                cout << "#t" << endl; 
            }
            if (newDatumStack.top().getBool() == false) {
                cout << "#f" << endl; 
            }
        }
            if (newDatumStack.top().isRString()) {
                cout << newDatumStack.top().getRString() << endl; 
            }
    }
    catch (runtime_error &error_message) {
        cerr << "Error: " << error_message.what() << endl; 
    }
}

/* 
 * "clear" operator for RPNCalc
 * Purpose: Clears the stack. 
 * Parameters: none
 * Returns:    none 
 */ 
void RPNCalc::rpn_clear()
{
    newDatumStack.clear(); 
}

/* 
 * "drop" operator for RPNCalc
 * Purpose: Pops the top Datum from the stack. If empty, prints an error and 
 * continues having done nothing. 
 * Parameters: none
 * Returns:    none 
 */ 
void RPNCalc::rpn_drop()
{
    try {
        newDatumStack.pop();  // will print an error message and continue 
                              // if stack is empty 
    }
    catch (runtime_error &error_message) {
        cerr << "Error: " << error_message.what() << endl; 
    }
}

/* 
 * "dup" operator for RPNCalc
 * Purpose: Duplicates the top Datum from the stack and pushes it.
 * If stack is empty, prints an error and continues having done nothing.
 * Parameters: none
 * Returns:    none 
 */ 
void RPNCalc::rpn_dup()
{
    try {
        newDatumStack.push(newDatumStack.top());
    }
    catch (runtime_error &error_message) {
        cerr << "Error: " << error_message.what() << endl; 
    }
}

/* 
 * "swap" operator for RPNCalc
 * Purpose: Swaps the top two Datums on the stack. 
 * If stack is empty or contains only one Datum, prints an error and 
 * continues. Still pops a singular Datum if called on a stack with one
 * Datum.  
 * Parameters: none
 * Returns:    none 
 */ 
void RPNCalc::rpn_swap()
{
    try {
        Datum d = newDatumStack.top();
        newDatumStack.pop(); 
        Datum d2 = newDatumStack.top(); 
        newDatumStack.pop();
        newDatumStack.push(d);  
        newDatumStack.push(d2); 
    }

    catch (runtime_error &error_message) {
        cerr << "Error: " << error_message.what() << endl; 
    }
}

/* 
 * math operators for RPNCalc
 * Purpose: Decides which math operation to perform on the stack 
 * based on input. Modularizes run loop somewhat. 
 * Parameters: a symbol- either "+", "-", "*", "/", or "mod".
 * Returns:    none 
 */ 
void RPNCalc::rpn_math(string symbol)
{
    if (symbol == "+")
        rpn_plus(); 

    if (symbol == "-")
        rpn_minus(); 

    if (symbol == "*")
        rpn_mult(); 

    if (symbol == "/")
        rpn_div(); 

    if (symbol == "mod")
        rpn_mod(); 

}
/* 
 * "+" operator for RPNCalc
 * Purpose: Pops the top two Datums from the stack. If both contain 
 * integers, adds the two integers and pushes a new Datum containing 
 * their sum. If stack is empty or contains only one item, prints an error and 
 * continues. (Will pop the solo item.) If one or more do not contain integers,
 * prints an error. 
 * Parameters: none
 * Returns:    none 
 */ 
void RPNCalc::rpn_plus()
{
    try {
        Datum d = newDatumStack.top();
        newDatumStack.pop();
        Datum d2 = newDatumStack.top();
        newDatumStack.pop();

        if (d.isInt() and d2.isInt())
            rpn_num(d2.getInt() + d.getInt()); 

        else 
            cerr << "Error: datum_not_int" << endl; 
    }
    catch (runtime_error &error_message) {
        cerr << "Error: " << error_message.what() << endl; 
    }
}

/* 
 * "-" operator for RPNCalc
 * Purpose: Pops the top two Datums from the stack. If both contain 
 * integers, subtracts the two integers and pushes a new Datum containing 
 * their difference. If stack is empty or contains only one item, 
 * prints an error and continues. (Will pop the solo item.) 
 * If one or more do not contain integers, prints an error. 
 * Parameters: none
 * Returns:    none 
 */ 
void RPNCalc::rpn_minus()
{
    try {
        Datum d = newDatumStack.top();
        newDatumStack.pop();
        Datum d2 = newDatumStack.top();
        newDatumStack.pop();

        if (d.isInt() and d2.isInt())
            rpn_num(d2.getInt() - d.getInt());

        else 
            cerr << "Error: datum_not_int" << endl; 
    }
    catch (runtime_error &error_message) {
        cerr << "Error: " << error_message.what() << endl; 
    }
}

/* 
 * "*" operator for RPNCalc
 * Purpose: Pops the top two Datums from the stack. If both contain 
 * integers, multiplies the two integers and pushes a new Datum containing 
 * their product. If stack is empty or contains only one item, 
 * prints an error and continues. (Will pop the solo item.) 
 * If one or more do not contain integers, prints an error. 
 * Parameters: none 
 * Returns:    none 
 */ 
void RPNCalc::rpn_mult()
{
    try {
        Datum d = newDatumStack.top();
        newDatumStack.pop();
        Datum d2 = newDatumStack.top();
        newDatumStack.pop();

        if (d.isInt() and d2.isInt())
            rpn_num(d2.getInt() * d.getInt());

        else 
            cerr << "Error: datum_not_int" << endl; 

    }
    catch (runtime_error &error_message) {
        cerr << "Error: " << error_message.what() << endl; 
    }
}

/* 
 * "/" operator for RPNCalc
 * Purpose: Pops the top two Datums from the stack. If both contain 
 * integers, divides the two integers and pushes a new Datum containing 
 * their quotient. If stack is empty or contains only one item, 
 * prints an error and continues. (Will pop the solo item.) 
 * If one or more do not contain integers, prints an error. 
 * If the denominator is zero, prints an error. 
 * Parameters: none
 * Returns:    none 
 */ 
void RPNCalc::rpn_div()
{
    try {
        Datum d = newDatumStack.top();
        newDatumStack.pop();
        Datum d2 = newDatumStack.top();
        newDatumStack.pop();

        if (d.isInt() and d2.isInt()) {
            if (d.getInt() == 0) 
                cerr << "Error: division by 0." << endl; 

            else 
                rpn_num(d2.getInt() / d.getInt()); 
        }

        else 
            cerr << "Error: datum_not_int" << endl; 

    }
    catch (runtime_error &error_message) {
        cerr << "Error: " << error_message.what() << endl; 
    }
}

/* 
 * "mod" operator for RPNCalc 
 * Purpose: Pops the top two Datums from the stack. If both contain 
 * integers, divides the two integers and pushes a new Datum containing 
 * their remainder. If stack is empty or contains only one item, 
 * prints an error and continues. (Will pop the solo item.)
 * If one or more do not contain integers, prints an error. 
 * If the denominator is zero, prints an error. 
 * Parameters: none
 * Returns:    none 
 */ 
void RPNCalc::rpn_mod()
{
    try {
        Datum d = newDatumStack.top();
        newDatumStack.pop();
        Datum d2 = newDatumStack.top();
        newDatumStack.pop();

        if (d.isInt() and d2.isInt()) {
            if (d.getInt() == 0) 
                cerr << "Error: division by 0." << endl; 

            else 
                rpn_num(d2.getInt() % d.getInt());
        }

        else 
            cerr << "Error: datum_not_int" << endl; 
    }
    catch (runtime_error &error_message) {
        cerr << "Error: " << error_message.what() << endl; 
    }
}

/* 
 * inequality operators for RPNCalc
 * Purpose: Decides which inequality operation to perform on the stack 
 * based on input. Modularizes run loop somewhat. 
 * Parameters: a symbol- either "<", ">", "<=", or ">=".
 * Returns:    none 
 * NOTE: I understand helper operators are included in Datum.h, such as
 * "<". This being said, I found it easier to do it my way using getInt().
 */ 
void RPNCalc::rpn_inequality(string symbol)
{
    if (symbol == "<")
        rpn_lessThan(); 

    if (symbol == ">")
        rpn_greaterThan(); 

    if (symbol == "<=")
        rpn_lessEquals(); 

    if (symbol == ">=")
        rpn_greaterEquals(); 

}

/* 
 * "<" operator for RPNCalc 
 * Purpose: Pops the top two Datums from the stack. If both contain 
 * integers, checks if the top is greater than the bottom. If so, pushes 
 * a "true" Datum. If not, pushes a "false" Datum. 
 * If stack is empty or contains only one item, prints an error and continues.
 * (Will pop the solo item.)
 * If one or more do not contain integers, prints an error. 
 * Parameters: none
 * Returns:    none 
 * 
 */ 
void RPNCalc::rpn_lessThan()
{
    try {
        Datum d = newDatumStack.top();
        newDatumStack.pop();
        Datum d2 = newDatumStack.top();
        newDatumStack.pop();

        if (d.isInt() and d2.isInt()) {
            if (d2.getInt() < d.getInt()) 
                rpn_t();
            
            else 
                rpn_f(); 
        }

        else 
            cerr << "Error: datum_not_int" << endl; 
    }
    catch (runtime_error &error_message) {
        cerr << "Error: " << error_message.what() << endl; 
    }
}
/* 
 * ">" operator for RPNCalc 
 * Purpose: Pops the top two Datums from the stack. If both contain 
 * integers, checks if the top is lesser than the bottom. If so, pushes 
 * a "true" Datum. If not, pushes a "false" Datum. 
 * If stack is empty or contains only one item, prints an error and continues.
 * (Will pop the solo item.)
 * If one or more do not contain integers, prints an error. 
 * Parameters: none
 * Returns:    none 
 */ 
void RPNCalc::rpn_greaterThan()
{
    try {
        Datum d = newDatumStack.top();
        newDatumStack.pop();
        Datum d2 = newDatumStack.top();
        newDatumStack.pop();

        if (d.isInt() and d2.isInt()) {
            if (d2.getInt() > d.getInt()) 
                rpn_t();
            
            else 
                rpn_f();
        }

        else 
            cerr << "Error: datum_not_int" << endl; 
    }
    catch (runtime_error &error_message) {
        cerr << "Error: " << error_message.what() << endl; 
    }
}

/* 
 * "<=" operator for RPNCalc 
 * Purpose: Pops the top two Datums from the stack. If both contain 
 * integers, checks if the top is greater than or equal to the bottom. 
 * If so, pushes a "true" Datum. If not, pushes a "false" Datum. 
 * If stack is empty or contains only one item, prints an error and continues.
 * (Will pop the solo item.)
 * If one or more do not contain integers, prints an error. 
 * Parameters: none
 * Returns:    none 
 */ 
void RPNCalc::rpn_lessEquals()
{
    try {
        Datum d = newDatumStack.top();
        newDatumStack.pop();
        Datum d2 = newDatumStack.top();
        newDatumStack.pop();

        if (d.isInt() and d2.isInt()) {
            if (d2.getInt() <= d.getInt()) 
                rpn_t();
            
            else 
                rpn_f();
        }

        else 
            cerr << "Error: datum_not_int" << endl; 
    }
    catch (runtime_error &error_message) {
        cerr << "Error: " << error_message.what() << endl; 
    }
}

/* 
 * ">=" operator for RPNCalc 
 * Purpose: Pops the top two Datums from the stack. If both contain 
 * integers, checks if the top is lesser than or equal to the bottom. 
 * If so, pushes a "true" Datum. If not, pushes a "false" Datum. 
 * If stack is empty or contains only one item, prints an error and continues.
 * (Will pop the solo item.)
 * If one or more do not contain integers, prints an error. 
 * Parameters: none
 * Returns:    none 
 */ 
void RPNCalc::rpn_greaterEquals()
{
    try {
        Datum d = newDatumStack.top();
        newDatumStack.pop();
        Datum d2 = newDatumStack.top();
        newDatumStack.pop();

        if (d.isInt() and d2.isInt()) {
            if (d2.getInt() >= d.getInt()) 
                rpn_t();
            
            else
                rpn_f();
        }

        else 
            cerr << "Error: datum_not_int" << endl; 
    }
    catch (runtime_error &error_message) {
        cerr << "Error: " << error_message.what() << endl; 
    }  
}


/* 
 * "==" operator for RPNCalc 
 * Purpose: Pops the top two Datums from the stack. If both contain 
 * equivalent values, be they ints, bools or rstrings, pushes a "true" Datum. 
 * If not, pushes a "false" Datum. 
 * If stack is empty or contains only one item, prints an error and continues.
 * (Will pop the solo item.)
 * Parameters: none
 * Returns:    none 
 */ 
void RPNCalc::rpn_equals()
{
    try {
        Datum d = newDatumStack.top();
        newDatumStack.pop();
        Datum d2 = newDatumStack.top();
        newDatumStack.pop();

        if (d == d2) 
            rpn_t();
            
        else
            rpn_f();
    }
    catch (runtime_error &error_message) {
        cerr << "Error: " << error_message.what() << endl; 
    }  
}

/* 
 * rstring pusher for RPNCalc
 * Purpose: Takes in an rstring (the return of parseRString)
 * and pushes it onto the stack as a Datum.
 * Parameters: an rstring string value to be pushed onto the stack as a Datum.
 * Returns:    none 
 */ 
void RPNCalc::rpn_rstring(string rstring)
{
    // cerr << "here" << endl; 
    Datum d(rstring); 
    newDatumStack.push(d); 
}


/* 
 * "exec" operator for RPNCalc 
 * Purpose: Pops the top Datum from the stack. If it contains an rstring, 
 * excecutes the commands in the rstring as if they were taken from the 
 * command line. 
 * If the top Datum is not an rstring, prints an error and continues.  
 * If stack is empty, prints an error and continues.
 * Parameters: none
 * Returns:    none 
 */ 
void RPNCalc::rpn_exec()
{
    try {
        if (not newDatumStack.top().isRString()) {
            newDatumStack.pop();
            cerr << "Error: cannot execute non rstring\n"; 
        }

        else {
            string erase_bracket = "";
            string exec_string = newDatumStack.top().getRString(); 
            istringstream rstringstream; 
            rstringstream.str(exec_string); 
            rstringstream >> erase_bracket; // gets rid of first character   
            newDatumStack.pop();            // (a bracket)
            run_stream(rstringstream);
        }

    }
    catch (runtime_error &error_message) {
        cerr << "Error: " << error_message.what() << endl; 
    }
}

/* 
 * "file" operator for RPNCalc 
 * Purpose: Pops the top Datum from the stack. If it contains an rstring, 
 * attempts to open a file whose name is the contents of the rstring. 
 * If such a file is successfully opened, executes the commands in the file
 * as if they were taken from the command line. 
 * If the rstring does not contain a valid file name, prints and error 
 * and continues.   
 * If the top Datum is not an rstring, prints an error and continues.  
 * If stack is empty, prints an error and continues.
 * Parameters: none
 * Returns:    none 
 */
void RPNCalc::rpn_file()
{
    try {
        if (not newDatumStack.top().isRString()) {
            newDatumStack.pop();
            cerr << "Error: file operand not rstring\n"; 
        }

        else {
            string filename = newDatumStack.top().getRString(); 
            if (filename.length() < 4) {
                newDatumStack.pop(); 
                cerr << "Unable to read" << endl; 
            } 

            else {
                filename = filename.substr(2, filename.length() - 4);
                ifstream filestream;
                filestream.open(filename);
                newDatumStack.pop(); 
                if (not filestream.is_open())
                    cerr << "Unable to read " << filename << endl; 
                else {
                    run_stream(filestream);
                    filestream.close(); 
                }
            }
        }
    }
    catch (runtime_error &error_message) {
        cerr << "Error: " << error_message.what() << endl; 
    }
}

/* 
 * "if" operator for RPNCalc 
 * Purpose: Pops the top three Datums from the stack. If the bottom 
 * contains a boolean, the second an rstring, and the third an rstring, 
 * reads the boolean. 
 * If it is "true," executes the second item 
 * (the first, or bottom, of the two rstrings) as exec() would. 
 * If it is "false," executes the first item 
 * (the second, or bottom, of the two rstrings) as exec() would. 
 *
 * If the rstring does not contain a valid file name, prints and error 
 * and continues.   
 * If any of the conditions on lines 796-797 are not met, prints an error
 * and continues. 
 * Parameters: none
 * Returns:    none 
 */
void RPNCalc::rpn_if()
{
    try {
        Datum rfalse = newDatumStack.top();
        newDatumStack.pop();
        Datum rtrue = newDatumStack.top();
        newDatumStack.pop();
        Datum rbool = newDatumStack.top();
        newDatumStack.pop();

        if (not rbool.isBool()) 
            cerr << "Error: expected boolean in if test\n"; 

        else {
            
            if (not rtrue.isRString())
                cerr << "Error: expected rstring in if branch\n";
            
            else {

                if (not rfalse.isRString())
                cerr << "Error: expected rstring in if branch\n";

                else {

                    if (rbool.getBool() == true) {
                        newDatumStack.push(rtrue);
                        rpn_exec();
                    }

                    if (rbool.getBool() == false) {
                        newDatumStack.push(rfalse);
                        rpn_exec();
                    }
                }
            }
        }
    }
    catch (runtime_error &error_message) {
        cerr << "Error: " << error_message.what() << endl;
    }
}

/*
 * rstring parser for RPNCalc 
 * Purpose: Allows for reading of an rstring and processing of one as
 * a C++ std::string to be put into a Datum (or another rstring). 
 * Called after the program reads an "{".
 * Parameters: an istream from which the rstring will be parsed 
 * Returns: an rstring std::string to be used in the program 
 */ 
string RPNCalc::parseRString(istream &input)
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

    myRString = myRString.substr(0, myRString.length() - 1);
    return myRString; 
}

/*
 * test of whether a string is int + int modifier for RPNCalc 
 * 
 * Purpose: Return true if the string s can be interpreted as an integer
 * number, placing the associated integer into the location pointed to by
 * resultp.
 *
 * Return false if s cannot be interpreted as an integer leaving the
 * location pointed to by resultp unmodified.
 *
 * The input string can be interpreted as an iteger if it has an
 * optional sign and then a sequence of decimal digits with no
 * following characters, except for white space.
 * 
 * Parameters: a string s to be evaluated as an int (or not), and 
 * a pointer to an integer that, if s evaluates as an integer, will be
 * modified to become that integer. 
 * 
 */
bool RPNCalc::got_int(string s, int *resultp)
{
        /* Holds the first non-whitespace character after the integer */
        char extra;

        return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}


/*
 * max_length getter; helper for got_int.cpp
 * Purpose: Return length of longest C-style string in the array of C strings.
 *
 * NOTE:  Requires len > 0:   it is an unchecked error for len <= 0
 * Parameters: an array of strings and its length
 * Returns: a size_t of the length of the longest string in the array
 */
size_t RPNCalc::max_length(char *c_strs[], int len)
{
        size_t max_so_far = strlen(c_strs[0]);

        for (int i = 1; i < len; ++i)
                max_so_far = max(max_so_far, strlen(c_strs[i]));
        return max_so_far;
}


/* 
 * "quit" operator for RPNCalc
 * Purpose: quits the program when the user inputs "quit." Prints a nice 
 * parting message. 
 * Parameters: none.
 * Returns:    none 
 * 
 * IMPLEMENTATION NOTE: This function quits the program by setting a 
 * private class variable "full_stop" to true, which prevents further input.
 */ 
void RPNCalc::rpn_quit()
{
    full_stop = true; 
    cerr << "Thank you for using CalcYouLater.\n"; 
}
