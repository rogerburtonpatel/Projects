###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Roger A. Burtonpatel 


CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow 
LDFLAGS  = -g3 

## This rule builds CalcYouLater 
CalcYouLater: main.o DatumStack.o RPNCalc.o Datum.o
	$(CXX) $(CXXFLAGS) main.o DatumStack.o RPNCalc.o Datum.o -o CalcYouLater

## This rule builds DatumStack.o 
DatumStack.o: DatumStack.h DatumStack.cpp Datum.h 
	$(CXX) $(CXXFLAGS) DatumStack.cpp -c 

## This rule builds RPNCalc.o 
RPNCalc.o: RPNCalc.cpp RPNCalc.h Datum.h 
	$(CXX) $(CXXFLAGS) RPNCalc.cpp -c 

## This rule builds main.o 
main.o: main.cpp RPNCalc.h DatumStack.h 
	$(CXX) $(CXXFLAGS) main.cpp -c 



# The below rules are used by unit_test
# This rule will be used by unit_test to build the tests for the 
# DatumStack class. 
unit_test: unit_test_driver.o DatumStack_tests.o Datum.o DatumStack.o 
	$(CXX) $(CXXFLAGS) unit_test_driver.o DatumStack_tests.o Datum.o\
	 DatumStack.o 


# This rule builds the unit_test_driver.o file 
# unit_test_driver.cpp will be copied for you when running unit_test.
# This driver will contain main()
unit_test_driver.o: unit_test_driver.cpp
	$(CXX) $(CXXFLAGS) -c unit_test_driver.cpp 

# This rule builds DatumStack_tests.o
DatumStack_tests.o: DatumStack_tests.cpp DatumStack.h Datum.h 
	$(CXX) $(CXXFLAGS) -c DatumStack_tests.cpp


##
## Here is a rule for compiling .cyl files for use in testing
##
%.cylc:  %.cyl
	./cylc $^

# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
# 3/8/2021 also cleans up leftovers from making CalcYouLater. 
clean: 
	rm DatumStack.o RPNCalc.o unit_test_driver.o DatumStack_tests.o main.o \
	 *~ a.out CalcYouLater

provide:
	provide comp15 proj1 DatumStack.h DatumStack.cpp DatumStack_tests.cpp \
	RPNCalc.h RPNCalc.cpp main.cpp README Makefile test.cyl quit.cyl \
	quit2.cyl rStringTest.cyl errors.cyl fib.cyl fact.cyl cylc \
	fib_debug.cyl Datum.h Datum.o Commands.txt
