#!/usr/bin/bash

# write to standard out a new version of the file on the input.

FILE=`mktemp`; # Let the shell create a temporary file
trap 'rm -f $FILE' 0 1 2 3 15;   # Clean up the temporary file 

(
  echo 'cat <<END_OF_TEXT'
  cat "$1"
  echo 'END_OF_TEXT'
) > $FILE
. $FILE