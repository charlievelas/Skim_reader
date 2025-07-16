# Skim_reader
A program allowing for easy HIPO file skimming using clas12root

Requires ROOT, tested on version 6.30/06, and clas12root.

Skim reader is designed to be quick and easy to use. When creating the skim reader file, few variables are saved to the skimmed tree. The mass/PID and the px,py and pz momentum components are saved meaning that the 4-vectors for each particles can be obtained to calculated another variable. For example, Gottfried-Jackson variables can be calculated after skimming is complete, using these variables.  

## How to install
On cshrc
```sh
git clone https://github.com/charlievelas/Skim_reader.git
cd Skim_reader
setenv SkimR $PWD
chmod u+x creator.sh
chmod u+x builder.sh
```

## How to run
First, run blueprint creator,

```
$SkimR/creator.sh
```
Next, edit the blueprint file.

Next, build SkimReader,

```
$SkimR/builder.sh [blueprint file name] 
```
