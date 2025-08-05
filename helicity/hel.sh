# the purpose of this shell is to activate hel_calculator.C, the purpose of hel_calculator.C is to calculate hel variables for each event in a root tree

#!/bin/bash

# Ensure input is provided and is a .root file
if [[ $# -ne 1 || "$1" != *.root ]]; then
    echo "Usage: $0 input.root"
    exit 1
fi

infile="$1"

# Prompt user for variable names
read -p "electron variable name: " el_var
read -p "proton variable name: " pro_var
read -p "particle 1 variable name: " p1_var
read -p "particle 2 variable name: " p2_var

# Run hel_calculator with the provided arguments
root -l -b -q "hel_calculator.C(\"$infile\", \"$el_var\", \"$pro_var\", \"$p1_var\", \"$p2_var\")"

# Tell user that new root file has been made
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
outfile="hel_${infile}"
echo "Gottfried-Jackson angles calculated and saved to 'helPhi' and 'helCosTh' branches in $outfile"



