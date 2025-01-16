#!/usr/bin/bash

echo "Welcome to Skim Reader"
echo "This programme allows for easy HIPO skimming using clas12root"
echo "A macro is built with user-specified particles and conditions"

root -q -l $SkimR/Skim_reader_builder.C

while true; do
    echo "Run 'Skim_reader.C'? (yes/no)"
    read input
    if [ "$input" == "yes" ]; then
        echo "Running 'Skim_reader.C'"
	root -q -l Skim_reader.C
	break
    elif [ "$input" == "no" ]; then
        echo "Not running 'Skim_reader.C'"
	break
    else
        echo "Invalid input: Input must be yes or no"
    fi
done
