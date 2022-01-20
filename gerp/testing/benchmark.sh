#!/bin/bash

# usage: ./benchmark.sh dir_to_test_with_gerps

# requirements: a testing directory containing the above 2 (specified below)

# author : rab
# date   : 1/17/2022
# notes: testing dir MUST contain 
#        1. test directories for gerp, possibly including symlinks to 
#           gutenberg directories 
#        2. command files. 

PATH_TO_REFERENCE="/h/rburto03/15_items/gerp/the_gerp"
PATH_TO_MY_GERP="/h/rburto03/15_items/gerp/gerp/current/gerp"
PATH_TO_TESTING_DIR="/h/rburto03/15_items/gerp/gerp/testing"

main() {
if [[ "$#" -ne "1" ]]; then 
>&2 echo "usage: ./benchmark.sh dir_to_test_w_gerp"
exit 2

else 
echo "@q" | /usr/bin/time -v "$PATH_TO_REFERENCE" "$1" \
"$PATH_TO_TESTING_DIR"/refout.txt 1> /dev/null 2> reftime.txt

echo "@q" | /usr/bin/time -v "$PATH_TO_MY_GERP" "$1" \
"$PATH_TO_TESTING_DIR"/myout.txt 1> /dev/null 2> mytime.txt

DIFF=$(diff <(tail -n +2 reftime.txt | head -n-12) \
            <(tail -n +2 mytime.txt | head -n-12))

    if [[ "$DIFF" != "" ]]
    then
        printf '\n%s\n%s\n' '< reference, > my gerp:' "$DIFF"
        echo -n "output files reftime.txt" 
        echo " and mytime.txt available in $PATH_TO_TESTING_DIR"
    else
        echo "no difference! deleting output files."
        rm reftime.txt mytime.txt
    fi

fi
}

main "$@"