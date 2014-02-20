#!/usr/bin/env bash

#PROGRAM_TO_SJMMIE="cat example-data/input.txt"
#PROGRAM_TO_SJMMIE="curl localhost"
#PROGRAM_TO_SJMMIE="wget localhost -O /dev/null"
PROGRAM_TO_SJMMIE="/Applications/Firefox.app/Contents/MacOS/firefox"
#PROGRAM_TO_SJMMIE="ls"

echo "Without SJMMIE"
$PROGRAM_TO_SJMMIE

echo "With SJMMIE"
PROGRAM_TO_SJMMIE="$PROGRAM_TO_SJMMIE" ./run.sh
