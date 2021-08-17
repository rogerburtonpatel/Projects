#!/bin/bash 
#
# eval_finder.sh
# 
# Finds all instances of 'eval(' within a directory. eval is evil, so
# this is a good tool to eliminate this bad method from your .js code. 
#
# Usage: ./eval_finder directory_to_search1, directory_to_search2, etc.
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

# tracker of every instance of eval()
total_eval=0

for arg in $@
do

# grep argument of for loop returns list of files containing eval(). 
# The loops itself finds how many eval()s exist  per file using wc. 
# The line in question is commented. 
for i in $(grep -l -r 'eval(' $arg)
do
	x=$(grep -o 'eval(' $i | wc -l) # x = num of eval()s in offending files
	let "total_eval+=x"		

	printf "%d %s %s \n" $x "instance(s) of eval() found in" $i 

done

printf "%d %s %s \n" $total_eval "total instances of eval() found in" $arg

# Congrats if no eval() in specified directory
if [ "$total_eval" -eq 0 ]
then
	printf "%s \n" "Great job avoiding eval() and writing safer code!"
fi
# Reset counter to search next directory 
let "total_eval=0"

printf "%s \n" "-------------------------------------------------------"
done
