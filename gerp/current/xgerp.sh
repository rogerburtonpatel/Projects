#!/bin/bash

if [ "$1" == "small" ]; then
    ./gerp /g/15/2019f/files/proj2-test-dirs/smallGutenberg out

elif [ "$1" == "med" ]; then
    ./gerp /g/15/2019f/files/proj2-test-dirs/mediumGutenberg out

elif [ "$1" == "large" ]; then
    ./gerp /g/15/2019f/files/proj2-test-dirs/largeGutenberg out

else echo "use an arg- 'small', 'med', 'large'"
fi