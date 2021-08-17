#!/bin/bash
#
# SixDegrees_tests.sh
#
# Script for large-scale diff test of proj2 using testing files. Tests all 
# main commands (bfs, dfs, not) with extensive edge case consideration.
#
# This testing paradigm uses my SixDegrees program with artists.txt
# (as well as a custom artists file) and a unique command file per test. 
# The output is written to a file called my_output.txt. 
# Ex: Line 30
# Then the same files are read by the reference implementation, 
# with output written to a file called ref_output.txt.
# Ex: Line 31
# The two files are then compared using man diff -c, 
# with a message to indicate the diff process is occurring. 
# Ex: Lines 33-35
# The files are subsequently deleted, and a new test is run. 
# Ex: Lines 37-onwards. 
# 
# Instructions: ./SixDegrees_tests.sh to run. Requires components for proj2 and 
# reference implementation named the_SixDegrees
# Author: Roger A. Burtonpatel 

## Removes all temporary files 
make clean

## Compiles and links the program, creating an exacutable "SixDegrees."
make 

### GRAPH CONSTRUCTION/FILE READING/EXITING TESTS
echo "GRAPH CONSTRUCTION/FILE READING/EXITING TESTS:" 

## Test of quitting from within a command file. Tests that 
## calling "quit" from within a command file will successfully 
## end the program with no further output.
./SixDegrees  artists.txt printquit.txt my_output.txt
./the_SixDegrees artists.txt printquit.txt ref_output.txt

echo -n "diffing results for commandfile" 
echo " printquit.txt with input file artists.txt"
diff -c my_output.txt ref_output.txt

rm my_output.txt
rm ref_output.txt

## Test of exiting program when reaching the end of a command file. 
## Tests that calling reaching the end of a command file without
## calling "quit" will successfully end the program with no further output. 
./SixDegrees  artists.txt printprint.txt my_output.txt
./the_SixDegrees artists.txt printprint.txt ref_output.txt

echo -n "diffing results for commandfile" 
echo " printprint.txt with input file artists.txt"
diff -c my_output.txt ref_output.txt

rm my_output.txt
rm ref_output.txt

## Test of a different, shorter Artist file. Prints and 
## quits the graph. The artists are all connected to 
## another artist. 
./SixDegrees  ABCD.txt printquit.txt my_output.txt
./the_SixDegrees ABCD.txt printquit.txt ref_output.txt

echo "diffing results for commandfile printquit.txt with input file ABCD.txt"
diff -c my_output.txt ref_output.txt

rm my_output.txt
rm ref_output.txt

## Test of a different, shorter Artist file. Prints twice 
## and exits upon reachin end
## of command file. The artists are all connected to 
## another artist. 
./SixDegrees  ABCD.txt printprint.txt my_output.txt
./the_SixDegrees ABCD.txt printprint.txt ref_output.txt

echo "diffing results for commandfile printprint.txt with input file ABCD.txt"
diff -c my_output.txt ref_output.txt

rm my_output.txt
rm ref_output.txt

## Test of artists.txt with a blank command file. 
./SixDegrees  artists.txt blank.txt my_output.txt
./the_SixDegrees artists.txt blank.txt ref_output.txt

echo "diffing results for commandfile blank.txt with input file artists.txt"
diff -c my_output.txt ref_output.txt


rm my_output.txt
rm ref_output.txt

## Test of alternative artists file with a blank command file. 
./SixDegrees  ABCD.txt blank.txt my_output.txt
./the_SixDegrees ABCD.txt blank.txt ref_output.txt

echo "diffing results for commandfile blank.txt with input file ABCD.txt"
diff -c my_output.txt ref_output.txt

rm my_output.txt
rm ref_output.txt

## Test of blank artists file with a normal command file. 
./SixDegrees  blank.txt printprint.txt my_output.txt
./the_SixDegrees blank.txt printprint.txt ref_output.txt

echo "diffing results for commandfile printprint.txt with input file blank.txt"
diff -c my_output.txt ref_output.txt

rm my_output.txt
rm ref_output.txt

## Test of blank artists file with a blank command file. 
./SixDegrees  blank.txt blank.txt my_output.txt
./the_SixDegrees blank.txt blank.txt ref_output.txt

echo -n "diffing results for commandfile blank.txt"
echo " with input file blank.txt"
diff -c my_output.txt ref_output.txt

rm my_output.txt
rm ref_output.txt


### BFS TESTS 
echo "BFS TESTS:" 

## Tests bfs with: 
## two artists w a direct path 
## two artists w longer path 
## two artists with no path
## bfs with one artist inputted followed by the end of the file (EDGE CASE)
## and diffs. Uses artists.txt. 
./SixDegrees  artists.txt bfs_tests.txt my_output.txt
./the_SixDegrees artists.txt bfs_tests.txt ref_output.txt

echo "diffing results for commandfile bfs_tests.txt with input file artists.txt"
diff -c my_output.txt ref_output.txt

rm my_output.txt
rm ref_output.txt


### DFS TESTS 
echo "DFS TESTS:" 

## Tests dfs with: 
## two artists w a direct path 
## two artists w longer path 
## two artists with no path
## dfs with one artist inputted followed by the end of the file (EDGE CASE)
## without using diff, since reference 
## output intentionally differs from mine. Because of this, 
## manual verification of path construction is required. 
## Uses artists.txt. 
./SixDegrees  artists.txt dfs_tests.txt my_dfs_output.txt
./the_SixDegrees artists.txt dfs_tests.txt ref_dfs_output.txt

echo -n "see my_dfs_output.txt and ref_dfs_output.txt to make sure"
echo " path construction was accurate."


### "NOT" TESTS 
echo ""NOT" TESTS:" 

## Tests "not" with: 
## two artists w a direct path, excluding no one 
## two artists w a direct path, excluding one other (EDGE CASE)
## two artists w a direct path, excluding several others (EDGE CASE)
## two artists w longer path, excluding no one (EDGE CASE)
## two artists w longer path, excluding one other
## two artists w longer path, excluding several others
## two artists w any path in which exclusive search results in no path 
## two artists w no path, excluding none (EDGE CASE)
## two artists w no path, excluding one other (EDGE CASE) 
## two artists w no path, excluding several (EDGE CASE)

## two artists w direct path, excluding first artist (EDGE CASE)
## two artists w direct path, excluding second artist (EDGE CASE)
## two artists w longer path, excluding either artist (EDGE CASE)
## two artists with no path, excluding either artist (EDGE CASE)

## "not" with one artist inputted followed by the end of the file (EDGE CASE)

## ending not command by reaching end of file without reading * (EDGE CASE)
./SixDegrees  artists.txt not_tests.txt my_output.txt
./the_SixDegrees artists.txt not_tests.txt ref_output.txt

echo "diffing results for commandfile not_tests.txt with input file artists.txt"
diff -c my_output.txt ref_output.txt

rm my_output.txt
rm ref_output.txt

./SixDegrees  artists.txt not_tests.txt my_output.txt
./the_SixDegrees artists.txt not_tests.txt ref_output.txt

echo -n "diffing results for commandfile exit_not_test.txt" 
echo " with input file artists.txt"
diff -c my_output.txt ref_output.txt

rm my_output.txt
rm ref_output.txt


## Removes all temporary files 
make clean 

### END OF TESTING FILE 
