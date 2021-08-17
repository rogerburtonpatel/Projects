/* main.cpp
 * 
 * COMP 15 project 1
 * edited by Roger A. Burtonpatel, 3/10/2021
 * 
 * Driver file for RPNCalc. Used to run CalcYouLater, an interactive 
 * Reverse Polish Notation (RPN) calculator that can read from files 
 * and perform some complex commands in addition to integer algebra 
 * and boolean / special string comparison. A useful tool for any 
 * Reverse Polish Mathematician. 
 *  
 * REQUIRED PARAMETERS: 
 * 1. RPNCalc.cpp, RPNCalc.h, DatumStack.h, DatumStack.cpp, 
 * Datum.h, Datum.o, Makefile
 * 2. Any files used for testing. 
 * 
 * COMMANDS: 
 * All input from the user is taken through cin. This can be redirected 
 * and commands may be taken from a file using the built-in "file" command. 
 * See RPNCalc.cpp for example commands, and Commands.txt for a full list of 
 * commands. 
 * 
 * Compile using "make CalcYouLater" and run using:
 * 
 * ./CalcYouLater
 * 
 * quit by imputting, "quit."
 */

#include "DatumStack.h"
#include "RPNCalc.h"
#include <fstream>
using namespace std; 


int main()
{
    RPNCalc newCalc; 
    return 0; 
}
