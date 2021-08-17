#
# Makefile for Six Degrees
#
# Project 2 (spring 2021)
#
# Edited by Roger A. Burtonpatel 4/18/2021
#
# 

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11 
INCLUDES = $(shell echo *.h)

# This rule builds the SixDegrees executable. 
SixDegrees: main.o SixDegrees.o CollabGraph.o Artist.o
	${CXX} -o $@ $^ 

# This rule builds .o files. 
%.o: %.cpp ${INCLUDES}
	${CXX} ${CXXFLAGS} -c $<

# This rule runs unit_test.  
unit_test: CollabGraph_tests.o unit_test_driver.o CollabGraph.o Artist.o
	${CXX} ${CXXFLAGS} CollabGraph_tests.o unit_test_driver.o\
	 CollabGraph.o Artist.o

# Removes all executables, .o and temporary files. 
clean:
	rm -rf SixDegrees a.out *.o *.dSYM 

##############################################
# PLEASE DO NOT FORGET TO ADD ANY ADDITIONAL #
# FILES YOU MADE, SUCH AS TESTING FILES.     #
##############################################

providephase1:
	provide comp15 proj2phase1 SixDegrees.cpp SixDegrees.h \
			main.cpp README Makefile CollabGraph.cpp CollabGraph.h \
			CollabGraph_tests.cpp diff.sh ABCD.txt printquit.txt \
			printprint.txt

providephase2:
	provide comp15 proj2phase2 SixDegrees.cpp SixDegrees.h \
			main.cpp README Makefile CollabGraph.cpp CollabGraph.h \
			CollabGraph_tests.cpp SixDegrees_tests.sh ABCD.txt \
			printquit.txt printprint.txt blank.txt bfs_tests.txt \
			dfs_tests.txt not_tests.txt exit_not_test.txt
