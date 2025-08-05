# the purpose of this shell is to activate pol_calculator.C, the purpose of pol_calculator.C is to calculate the degree of linear polarisation, P, and the angle between the electron scattering plane and the hadron production plane, elHadPhi, also known as the polarisation angle

#!/bin/bash

# Ensure input is provided and is a .root file
if [[ $# -ne 1 || "$1" != *.root ]]; then
    echo "Usage: $0 input.root"
    exit 1
fi

infile="$1"

# Prompt user for variable names
read -p "electron variable name: " el_var
read -p "particle 1 variable name: " p1_var
read -p "particle 2 variable name: " p2_var

# Run GJ_calculator with the provided arguments
root -l -b -q "pol_calculator.C(\"$infile\", \"$el_var\", \"$p1_var\", \"$p2_var\")"

# Tell user that new root file has been made
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
outfile="GJ_${infile}"
echo "degree of linear polarisation and electron-hadron plane phi angle calculated and saved to 'polP' and 'polElHadPhi' branches in $outfile"



