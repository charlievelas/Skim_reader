#!/bin/bash

# Ensure input is provided and is a .txt file
if [[ $# -ne 1 || "$1" != *.txt ]]; then
    echo "Usage: $0 input.txt"
    exit 1
fi

input_file="$1"
SkimR=$SkimR  # Set SkimR to your desired value

var1="$SkimR/"   # SkimReader name
var2=""         # Blueprint name
var3=""         # Particles
var4=""         # HIPO file/run or slurm
var5=""         # Electron beam energy (GeV)
var6=""         # Target mass (GeV)
var7_list=()    # More than each particle (array)
var8=""         # Other particles
var9=""         # Use FT based time of event for FT electron? (yes/no)
var10=""        # Scattered electron name
var11=""        # Gottfried-Jackson frame
var12=""        # Additional conditions
var13=""        # All branches
branches=()

while IFS= read -r line; do
    if [[ "$line" == "Blueprint name:"* ]]; then
        read -r next_line
        if [[ -z "$next_line" ]]; then
            var2="no"
        else
            var2="$next_line"
        fi
    elif [[ "$line" == "Particles:"* ]]; then
        read -r next_line
        if [[ -z "$next_line" ]]; then
            var3="no"
        else
            var3="$next_line"
        fi
    elif [[ "$line" == "Enter run/HIPO file location or enter \"slurm\" to configure SkimReader for slurm:"* ]]; then
        read -r next_line
        if [[ -z "$next_line" ]]; then
            var4="HIPO"
        else
            var4="$next_line"
        fi
    elif [[ "$line" == "Electron beam energy (GeV)?"* ]]; then
        read -r next_line
        if [[ -z "$next_line" ]]; then
            var5="10.2"
        else
            var5="$next_line"
        fi
    elif [[ "$line" == "Target mass (GeV)?"* ]]; then
        read -r next_line
        if [[ -z "$next_line" ]]; then
            var6="0.943"
        else
            var6="$next_line"
        fi
    elif [[ "$line" == "Allow events with more than"* ]]; then
        read -r next_line
        if [[ -z "$next_line" ]]; then
            var7_list+=("\"no\"")
        else
            var7_list+=("\"$next_line\"")
        fi
    elif [[ "$line" == "Allow events with other particles? (yes/no)"* ]]; then
        read -r next_line
        if [[ -z "$next_line" ]]; then
            var8="no"
        else
            var8="$next_line"
        fi
    elif [[ "$line" == "Use FT based time for event? (yes/no)"* ]]; then
        read -r next_line
        if [[ -z "$next_line" ]]; then
            var9="no"
        else
            var9="$next_line"
        fi
    elif [[ "$line" == "Scattered electron variable name:"* ]]; then
        read -r next_line
        if [[ -z "$next_line" ]]; then
            var10="no"
        else
            var10="$next_line"
        fi
    elif [[ "$line" == "Calculate Gottfried-Jackson frame variables? (empty=no)"* ]]; then
        read -r next_line
        if [[ -z "$next_line" ]]; then
            var11="no"
        else
            var11="$next_line"
        fi
    elif [[ "$line" == "Additional conditions (all conditions on one line)? (empty=no)"* ]]; then
        read -r next_line
        if [[ -z "$next_line" ]]; then
            var12="no"
        else
            var12="$next_line"
        fi
    elif [[ "$line" == "All branches:"* ]]; then
        branches=()
        while IFS= read -r next_line; do
            # Stop if end of file (loop will exit naturally)
            if [[ -z "$next_line" ]]; then
                continue
            fi
            branches+=("\"$next_line\"")
        done
        # var13 will be set after the loop
    fi
done < "$input_file"

# var7 should never be empty, always output as {"...", "..."}
if [[ ${#var7_list[@]} -gt 0 ]]; then
    IFS=,; var7="{${var7_list[*]}}"; IFS=$' \t\n'
else
    var7="{}"
fi

if [[ -n "${branches[*]}" ]]; then
    IFS=,; var13="{${branches[*]}}"; IFS=$' \t\n'
else
    var13="{}"
fi

echo "Configuration"
sleep 0.5
echo "Blueprint name:                $var2"
sleep 0.5
echo "Particles:                     $var3"
sleep 0.5
echo "HIPO file/run or slurm:        $var4"
sleep 0.5
echo "Electron beam energy (GeV):    $var5"
sleep 0.5
echo "Target mass (GeV):             $var6"
sleep 0.5
echo "More than each particle:       $var7"
sleep 0.5
echo "Other particles:               $var8"
sleep 0.5
echo "Use FT based time:             $var9"
sleep 0.5
echo "Scattered electron name:       $var10"
sleep 0.5
echo "Gottfried-Jackson frame:       $var11"
sleep 0.5
echo "Additional conditions:         $var12"
sleep 0.5
echo ""
echo "Building SkimReader"

root -q -l 'skim_reader_builder.C("'$var1'","'$var2'","'$var3'","'$var4'","'$var5'","'$var6'",'$var7',"'$var8'","'$var9'","'$var10'","'$var11'","'"$var12"'",'$var13')' 2>&1 | grep -v '^Processing'
