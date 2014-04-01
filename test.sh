#!/usr/bin/env bash

#PROGRAM_TO_SJMMIE="cat example-data/input.txt"
#PROGRAM_TO_SJMMIE="curl localhost"
#PROGRAM_TO_SJMMIE="wget localhost -O /dev/null"
#PROGRAM_TO_SJMMIE="wget localhost"
PROGRAM_TO_SJMMIE="/Applications/Firefox.app/Contents/MacOS/firefox"
#PROGRAM_TO_SJMMIE="ls"

#PROGRAM_TO_SJMMIE="/Applications/VLC.app/Contents/MacOS/VLC -I dummy --loop /Users/timmattison/Desktop/annex/github/cg-snippets/python/rccl/horizontal-line.avi --sout '#duplicate{dst=rtp{mux=ts,dst=239.192.128.105,port=1234,sdp=sap://,name=\"TestStream\",ttl=12}}'"
#PROGRAM_TO_SJMMIE="ping localhost"
#PROGRAM_TO_SJMMIE="nslookup google.com"

echo "Without SJMMIE"
$PROGRAM_TO_SJMMIE

echo "With SJMMIE"
PROGRAM_TO_SJMMIE="$PROGRAM_TO_SJMMIE" ./run.sh
