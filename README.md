# Skim_reader
A programme allowing for easy HIPO file skimming using clas12root

Requires ROOT, tested on version 6.30/06, and clas12root.

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
./creator.sh
Next, edit the blueprint file.
Next, builder SkimReader,
./builder.sh [blueprint file name] 
