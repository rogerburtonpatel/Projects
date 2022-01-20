#!/bin/bash

# uses perf instead of time. runs argv[2] times. much cooler. 

# usage: ./perfmark.sh dir_to_test_with_gerps num_times_to_run

# requirements: a testing directory containing the above 2 (specified below)

# author : rab
# date   : 1/18/2022
# notes: testing dir MUST contain 
#        1. test directories for gerp, possibly including symlinks to 
#           gutenberg directories 
#        2. command files. 

PATH_TO_GERP1="/h/rburto03/15_items/gerp/gerp/new_vector/gerp"
PATH_TO_MY_GERP2="/h/rburto03/15_items/gerp/gerp/current/gerp"
PATH_TO_TESTING_DIR="/h/rburto03/15_items/gerp/gerp/testing"

main() {
if [[ "$#" -ne "2" ]]; then 
>&2 echo "usage: ./perfmark.sh dir_to_test_w_gerp num_times_to_run"
exit 2

else 

local runs="$2"

echo "@q" | perf stat --repeat "$runs" "$PATH_TO_GERP1" "$1" \
"$PATH_TO_TESTING_DIR"/out1.txt 1> /dev/null 2> perf1.txt

echo "@q" | perf stat --repeat "$runs" "$PATH_TO_MY_GERP2" "$1" \
"$PATH_TO_TESTING_DIR"/out2.txt 1> /dev/null 2> perf2.txt

DIFF=$(diff <(tail -n +2 perf1.txt | head -n-12) \
            <(tail -n +2 perf2.txt | head -n-12))

    if [[ "$DIFF" != "" ]]
    then
        printf '\n%s\n%s\n' '< gerp1, > gerp2:' "$DIFF"
        echo -n "output files perf1.txt" 
        echo " and perf2.txt available in $PATH_TO_TESTING_DIR"
    else
        echo "no difference! deleting output files."
        rm perf1.txt perf2.txt
    fi

fi
}

main "$@"