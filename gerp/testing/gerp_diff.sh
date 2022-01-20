#!/bin/bash

# usage: ./gerp_diff.sh dir_to_test_with_gerps command_file

# requirements: a testing directory containing the above 2 (specified below)

# author : 1/10/2022
# notes: testing dir MUST contain 
#        1. test directories for gerp, possibly including symlinks to 
#           gutenberg directories 
#        2. command files. 

PATH_TO_REFERENCE="/h/rburto03/15_items/gerp/the_gerp"
PATH_TO_MY_GERP="/h/rburto03/15_items/gerp/gerp/current/gerp"
PATH_TO_TESTING_DIR="/h/rburto03/15_items/gerp/gerp/testing"

main() {
if [[ "$#" -ne "2" ]]; then 
>&2 echo "usage: ./gerp_diff.sh dir_to_test_w_gerp command_file"
exit 2

else 
"$PATH_TO_REFERENCE" "$1" \
"$PATH_TO_TESTING_DIR"/refout.txt < "$PATH_TO_TESTING_DIR"/"$2" > /dev/null

"$PATH_TO_MY_GERP" "$1" \
"$PATH_TO_TESTING_DIR"/myout.txt < "$PATH_TO_TESTING_DIR"/"$2" > /dev/null


sort -o refout.txt refout.txt
sort -o myout.txt myout.txt 

diff -q refout.txt myout.txt

    if [[ $? == "0" ]]; then
        echo "no difference! deleting output files."
        rm refout.txt myout.txt
    else 
        echo -n "output files refout.txt" 
        echo " and myout.txt available in $PATH_TO_TESTING_DIR"
    fi

fi 
}

main "$@"