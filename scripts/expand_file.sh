#!/usr/bin/env bash

# write to standard out a version of the file named on the 
# command line
# that has had all variables expanded.

# Note that this is **insanely insecure**.

FILE=`mktemp`; # Let the shell create a temporary file
trap 'rm -f $FILE' 0 1 2 3 15;   # Clean up the temporary file 

(
  echo 'cat <<END_OF_TEXT'
  cat "$1"
  echo 'END_OF_TEXT'
) > $FILE
. $FILE