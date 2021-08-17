#!/bin/bash 
#
# strcpy_finder.sh
# 
# Finds all instances of 'strcpy(' within a directory. strcpy is also evil, so
# this is a good tool to eliminate this bad method from your .c code. 
#
# Usage: ./strcpy_finder directory_to_search1, directory_to_search2, etc.
#
# Author: Roger A. Burtonpatel
# Last Update: 8/1/2021

# Argument parser (From tldp.org's Advanced Bash Scripting Guide, 
# with edits by Author)
if [ ! -n "$1" ]
then
	  echo -n "Usage: `basename $0` directory_to_search1," \
		 "directory_to_search2, etc."
	  echo
	    exit $E_BADARGS
    fi  

# main code 

# tracker of every instance of strcpy()
total_strcpy=0

for arg in $@
do

# grep argument of for loop returns list of files containing strcpy(). 
# The loops itself finds how many strcpy()s exist  per file using wc. 
# The line in question is commented. 
for i in $(grep -l -r 'strcpy(' $arg)
do
	x=$(grep -o 'strcpy(' $i | wc -l) # x = num strcpy()s in offending files
	let "total_strcpy+=x"		

	printf "%d %s %s \n" $x "instance(s) of strcpy() found in" $i 

done

printf "%d %s %s \n" $total_strcpy "total instances of strcpy() found in" $arg

# Congrats if no strcpy() in specified directory
if [ "$total_strcpy" -eq 0 ]
then
	printf "%s \n" "Great job avoiding strcpy() and writing safer code!"
fi
# Reset counter to search next directory 
let "total_strcpy=0"

printf "%s \n" "-------------------------------------------------------"
done
