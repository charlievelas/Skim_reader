#!/usr/bin/bash

echo "Welcome to Skim Reader."
echo "This program allows for easy HIPO file skimming using clas12root."
echo "The process:"
echo "	particles -> blueprint -> Skim Reader"
echo ""

echo "~ BLUEPRINT ~"
echo "Please enter name for blueprint file (don't use file extension):"
read FILE_NAME
echo ""

echo "~ PARTICLES ~"
echo "Use format (name,PID:name,PID:name,PID ...),"
echo "Enter 'PIDs' for CLAS12 PIDs,'EXP' for example."

while true; do
	echo "Please enter particles:"
	read PARTICLES
	if [[ "$PARTICLES" == "PIDs" ]]; then
		echo "e+  -11   //   e-  11    //  gamma 22"
		echo "d-  -45   //   d   45"
		echo "pi- -211  //   pi+ 211"
		echo "K-  -321  //   K+  321"
		echo "n   2112  //   p- -2212  //  p 2212 "
	elif [[ "$PARTICLES" == "EXP" ]]; then
		echo "Example 'el,11:pro,2212:pi1,211:pi2,-211'"
    else
        break
    fi
done

# Send particles to blueprint_builder.C to build blueprint
root -q -l 'blueprint_builder.C("'$FILE_NAME'_blueprint","'$PARTICLES'")' 2>&1 | grep -v '^Processing'

echo "~ FILE ~"
echo "'${FILE_NAME}_blueprint.txt' has been created,"
echo "please OPEN this file and enter information."
