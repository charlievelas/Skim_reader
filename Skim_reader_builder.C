#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

// Function to generate combinations of any size (from 2 to vec.size())
void generate_combinations(const std::vector<std::string>& vec, int start, int k, std::vector<std::string>& current, std::vector<std::string>& Inv_names, std::vector<std::string>& Inv_formulae) {
    // If the current combination size is equal to the desired size (k), convert to string and add to Inv_names and Inv_formulae
    if (current.size() == k) {
        std::string name_combination;
        std::string formula_combination;

        // Convert current combination to a string for Inv_names (with underscores)
        for (size_t i = 0; i < current.size(); ++i) {
            name_combination += current[i];
            if (i != current.size() - 1) {
                name_combination += "_";  // Separate values with an underscore
            }
        }
        Inv_names.push_back(name_combination);  // Store the combination in Inv_names

        // Convert current combination to a string for Inv_formulae (with plus signs)
        for (size_t i = 0; i < current.size(); ++i) {
            formula_combination += current[i] + "_LV";
            if (i != current.size() - 1) {
                formula_combination += "+";  // Separate values with a plus sign
            }
        }
        Inv_formulae.push_back(formula_combination);  // Store the combination in Inv_formulae

        return;
    }

    // Generate combinations starting from 'start'
    for (size_t i = start; i < vec.size(); ++i) {
        current.push_back(vec[i]);  // Add current element to the combination
        generate_combinations(vec, i + 1, k, current, Inv_names, Inv_formulae);  // Recurse for the next element
        current.pop_back();  // Backtrack
    }
}

// Function to generate all combinations of sizes from 2 to vec.size() for both Inv_names and Inv_formulae
void generate_all_combinations(const std::vector<std::string>& vec, std::vector<std::string>& Inv_names, std::vector<std::string>& Inv_formulae) {
    std::vector<std::string> current;
    // Generate combinations for each size from 2 to vec.size()
    for (int k = 2; k <= vec.size(); ++k) {
        generate_combinations(vec, 0, k, current, Inv_names, Inv_formulae);  // Generate combinations of size k
    }
}

void Skim_reader_builder(){

//// BUILD SKIM READER ////

// Create the file
std::ofstream outFile("Skim_reader.C");

// Include headers
outFile << "#include <cstdlib>" << endl;
outFile << "#include <iostream>" << endl;
outFile << "#include <chrono>" << endl;
outFile << "#include <TFile.h>" << endl;
outFile << "#include <TTree.h>" << endl;
outFile << "#include <TApplication.h>" << endl;
outFile << "#include <TROOT.h>" << endl;
outFile << "#include <TDatabasePDG.h>" << endl;
outFile << "#include <TLorentzVector.h>" << endl;
outFile << "#include <TH1.h>" << endl;
outFile << "#include <TChain.h>" << endl;
outFile << "#include <TCanvas.h>" << endl;
outFile << "#include <TBenchmark.h>" << endl;
outFile << "#include \"clas12reader.h\"" << endl;
outFile << "using namespace clas12;" << endl;
outFile << endl;

// Start of macro
outFile << "void Skim_reader(){" << endl;
outFile << endl;

//Input file, output file, HIPO location and Ttree
outFile << "// Input file, output file, HIPO file and Ttree" << endl;

// HIPO input
std::string HIPOinput;
std::cout << "Enter location of HIPO files(s) to be analysed:" << endl;
std::getline(std::cin, HIPOinput);  // Get the user inpu

outFile << "TString in_file_name = \"" + HIPOinput + "\";" << endl;
outFile << "TChain chain(\"hipo\");" << endl;
outFile << "chain.Add(in_file_name.Data());" << endl;
outFile << "auto files=chain.GetListOfFiles();" << endl;
outFile << "TFile *tree_file = new TFile(\"skim_tree.root\",\"recreate\");" << endl;
outFile << "TTree *tree = new TTree(\"tree\",\"tree\");" << endl;
outFile << endl;

cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
std::cout << "Beam is 10.2 GeV electron and target is stationary proton," << endl;
std::cout << "this can be changed before running" << endl;
outFile << "auto PDG_info=TDatabasePDG::Instance();" << endl;
outFile << "TLorentzVector Beam_LV;" << endl;
outFile << "Beam_LV.SetXYZM(0,0,10.2,0.000511);" << endl;
outFile << "TLorentzVector Target_LV;" << endl;
outFile << "Target_LV.SetXYZM(0,0,0,0.93827);" << endl;
outFile << "TLorentzVector elScat_LV;" << endl;
outFile << endl;

//// USER PID INPUT ////
// Initialise variables, vectors and counts
vector<string> PID_list = {"-11","11","22","-45","45","-211","211","-321","321","2112","-2212","2212"};
vector<string> part_list = {"e+","e-","g","d-","d","pi-","pi+","K-","K+","n","p-","p"}; // LINKED TO 'PID conditions' SECTION, DO NOT ALTER
std::string var_name = "";
vector<string> var_name_vect;
int var_name_count=0;
std::string PID = "";
vector<string> PID_vect;
int PID_count=0;
std::string input;
std::string input2;
std::string input3;
std::string com = ",";
std::string col = ":";

cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

while (true) {
    // Ask the user for input
    std::cout << "Enter particles (variable name 1,PID:variable name 2,PID ... etc): " << endl;
    std::getline(std::cin, input);  // Get the user input
    int input_size=input.size();

    // Check if the input contains spaces
    if (input.find(' ') != std::string::npos) {
        std::cout << "Invalid input: The input must not contain spaces" << endl;
        continue;  // Re-prompt the user if it contains spaces
    } 

    // Check if the input doesn't contain at least one comma
    if (input.find(',') == std::string::npos) {
        std::cout << "Invalid input: The variable name and PID must be separated by a \",\"" << endl;
        continue;  // Re-prompt the user if it contains spaces
    }

    // Check if the input contains symbols
    bool has_invalid_characters = false;
    for (char ch : input) {
        // If any character is not alphanumeric, a comma, a colon ort an underscore then it's invalid
        if (!std::isalnum(ch) && ch != ',' && ch != ':' && ch != '_' && ch != '-') {
            has_invalid_characters = true;
            break;  // No need to check further if one invalid character is found
        }
    }
    if (has_invalid_characters) {
        std::cout << "Invalid input: Do not name variables using symbols (except \"_\")" << endl;
        continue;  // Re-prompt the user if invalid characters are found
    }
    
    // Check if the input starts with "," or ":" or fails to end in
    if(input.at(0)==com || input.at(0)==col || input.at(input_size-1)==com || input.at(input_size-1)==col){
        std::cout << "Invalid input: Input must not begin or end with \",\" or \":\""<< endl;
        continue;  // Re-prompt the user if it contains spaces
    }

    // Save input to variable name and PID vectors
    // Add colon to end of input so that code finds end
    input = input +":";
    for(Int_t indx=0; indx<input_size+1;indx++){
        if(input.at(indx)==com){
            var_name_count++;
        } else if(input.at(indx)==col){
            var_name_vect.push_back(var_name);
            PID_vect.push_back(PID);
            var_name = "";
            PID = "";
            var_name_count=0;
            PID_count=0;
        } else if(var_name_count==0){
            var_name = var_name + input.at(indx);
        } else if(var_name_count==1 && PID_count==0){
            PID = PID + input.at(indx);
        }
    }

    // Ensure PID is in PID list
    bool all_valid = true;
    for (const std::string& PID : PID_vect) {
        if (std::find(PID_list.begin(), PID_list.end(), PID) == PID_list.end()) {
            all_valid = false;
            std::cout << "Invalid input: \"" << PID << "\" is not a valid PID.\n";
            break;  // No need to check further if one PID is invalid
        }
    }

    if (all_valid) {
        break;
    }
}


// VARIABLES AND BRANCHES
for (int var_indx=0; var_indx<var_name_vect.size(); var_indx++){    
    outFile << "float " + var_name_vect.at(var_indx) + "_Px;" << endl;
    outFile << "float " + var_name_vect.at(var_indx) + "_Py;" << endl;
    outFile << "float " + var_name_vect.at(var_indx) + "_Pz;" << endl;
    outFile << "float " + var_name_vect.at(var_indx) + "_PID;" << endl;
    outFile << "float " + var_name_vect.at(var_indx) + "_beta;" << endl;
    outFile << "float " + var_name_vect.at(var_indx) + "_chi2PID;" << endl;
    outFile << "float " + var_name_vect.at(var_indx) + "_status;" << endl;
    outFile << "float " + var_name_vect.at(var_indx) + "_region;" << endl;
    outFile << "float " + var_name_vect.at(var_indx) + "_E;" << endl;
    outFile << "float " + var_name_vect.at(var_indx) + "_Th;" << endl;
    outFile << "float MissMass_" + var_name_vect.at(var_indx) + ";" << endl;
    outFile << "float MissMass2_" + var_name_vect.at(var_indx) + ";" << endl;
    outFile << "float MissEnergy_" + var_name_vect.at(var_indx) + ";" << endl;
    outFile << "TLorentzVector " + var_name_vect.at(var_indx) + "_LV; // No associated branch" << endl; // No associated branch
}
outFile << "float MissMass;" << endl;
outFile << "float MissMass2;" << endl;
// Inv mass loop
std::vector<std::string> Inv_names;
std::vector<std::string> Inv_formulae;
generate_all_combinations(var_name_vect, Inv_names, Inv_formulae);
for (size_t i = 0; i < Inv_names.size(); ++i) {
    outFile << "float InvMass_" + Inv_names[i] + ";" << std::endl;
}
outFile << "float MissTh;" << endl;
outFile << "float MissE;" << endl;
outFile << "float Q2;" << endl;
outFile << "float Egamma;" << endl;

outFile << endl;
for (int var_indx=0; var_indx<var_name_vect.size(); var_indx++){    
    outFile << "tree->Branch(\"" + var_name_vect.at(var_indx) + "_Px\",&" + var_name_vect.at(var_indx) + "_Px);" << endl;
    outFile << "tree->Branch(\"" + var_name_vect.at(var_indx) + "_Py\",&" + var_name_vect.at(var_indx) + "_Py);" << endl;
    outFile << "tree->Branch(\"" + var_name_vect.at(var_indx) + "_Pz\",&" + var_name_vect.at(var_indx) + "_Pz);" << endl;
    outFile << "tree->Branch(\"" + var_name_vect.at(var_indx) + "_PID\",&" + var_name_vect.at(var_indx) + "_PID);" << endl;
    outFile << "tree->Branch(\"" + var_name_vect.at(var_indx) + "_beta\",&" + var_name_vect.at(var_indx) + "_beta);" << endl;
    outFile << "tree->Branch(\"" + var_name_vect.at(var_indx) + "_chi2PID\",&" + var_name_vect.at(var_indx) + "_chi2PID);" << endl;
    outFile << "tree->Branch(\"" + var_name_vect.at(var_indx) + "_status\",&" + var_name_vect.at(var_indx) + "_status);" << endl;
    outFile << "tree->Branch(\"" + var_name_vect.at(var_indx) + "_region\",&" + var_name_vect.at(var_indx) + "_region);" << endl;
    outFile << "tree->Branch(\"" + var_name_vect.at(var_indx) + "_E\",&" + var_name_vect.at(var_indx) + "_E);" << endl;
    outFile << "tree->Branch(\"" + var_name_vect.at(var_indx) + "_Th\",&" + var_name_vect.at(var_indx) + "_Th);" << endl;        
    outFile << "tree->Branch(\"MissMass_" + var_name_vect.at(var_indx) + "\",&MissMass_" + var_name_vect.at(var_indx) + ");" << endl;        
    outFile << "tree->Branch(\"MissMass2_" + var_name_vect.at(var_indx) + "\",&MissMass2_" + var_name_vect.at(var_indx) + ");" << endl;
    outFile << "tree->Branch(\"MissEnergy_" + var_name_vect.at(var_indx) + "\",&MissEnergy_" + var_name_vect.at(var_indx) + ");" << endl;
}
outFile << "tree->Branch(\"MissMass\",&MissMass);" << endl;        
outFile << "tree->Branch(\"MissMass2\",&MissMass2);" << endl;
// Inv mass loop
for (size_t i = 0; i < Inv_names.size(); ++i) {
    outFile << "tree->Branch(\"InvMass_" + Inv_names[i] + "\",&InvMass_" + Inv_names[i] + ");" << endl;
}
outFile << "tree->Branch(\"MissTh\",&MissTh);" << endl;        
outFile << "tree->Branch(\"MissE\",&MissE);" << endl;
outFile << "tree->Branch(\"Q2\",&Q2);" << endl;
outFile << "tree->Branch(\"Egamma\",&Egamma);" << endl;
outFile << endl;


// Loop
outFile << "for(Int_t i=0;i<files->GetEntries();i++){" << endl;
outFile << endl;

// Assign a hipo file to the clas12 reader object
outFile << "    clas12reader c12(files->At(i)->GetTitle());" << endl;
outFile << endl;

// PID conditions
cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
cout << "Select conditions for each particle:" << endl;
std::string PIDs_chosen = "You have chosen ";
std::string PID_chosen = "";
int PID_list_indx = 0;

// Use an unordered_map to count occurrences of each string
std::unordered_map<std::string, int> countMap;
for (const auto& str : PID_vect) {
    // Only count the string the first time it appears
    if (countMap.find(str) == countMap.end()) {
        // Count the occurrences of the PID
        countMap[str] = 1;
        // Store the count for the first appearance of the PID
        int count = std::count(PID_vect.begin(), PID_vect.end(), str);
        for (int i = 0; i < 12; ++i) {
            if (PID_list.at(i) == str) {
                PID_list_indx = i;
                break;  // Stop searching once the string is found
            }
        }
        cout << "You have chosen " + std::to_string(count) + " " + part_list.at(PID_list_indx) << endl;
        
        while (true) {
            // Ask the user for input
            std::cout << "Allow events with more than " + std::to_string(count) + " " + part_list.at(PID_list_indx) + "? (yes/no)" << endl;
            std::getline(std::cin, input);  // Get the user input
            int input_size=input.size();

            // Check input
            if (input!="yes") {
                if (input!="no") {
                    std::cout << "Invalid input: Input must be yes or no" << endl;
                    continue;  // Re-prompt user
                } else if (input=="no"){
                    PID_chosen = "exactly " + std::to_string(count) + " " + part_list.at(PID_list_indx) + " and ";
                    outFile << "    c12.addExactPid(" + PID_list.at(PID_list_indx) + "," + std::to_string(count) + ");" << endl;
                }
            }   
            // WRITE CONDITION
            if (input=="yes"){
                PID_chosen = "at least " + std::to_string(count) + " " + part_list.at(PID_list_indx) + " and ";
                outFile << "    c12.addAtLeastPid(" + PID_list.at(PID_list_indx) + "," + std::to_string(count) + ");" << endl;           
            }
        break;
        }
        PIDs_chosen = PIDs_chosen + PID_chosen;
    }
}

PIDs_chosen.erase(PIDs_chosen.length() - 5);
cout << PIDs_chosen << endl;

while (true) {
    // Ask the user for input
    std::cout << "Allow events with other particles? (yes/no)" << endl;
    std::getline(std::cin, input);  // Get the user input
    int input_size=input.size();

    // Check if the input contains spaces
    if (input!="yes") {
        if (input!="no") {
            std::cout << "Invalid input: Input must be yes or no" << endl;
            continue;  // Re-prompt user
        } else if (input=="no"){
            outFile << "    c12.addZeroOfRestPid();" << endl;
            // Change an 'at least's to 'exactly's in PIDs_chosen
            size_t pos = 0;
            while ((pos = PIDs_chosen.find("at least", pos)) != std::string::npos) {
                PIDs_chosen.replace(pos, 8, "exactly");
                pos += 7;
            }
            cout << PIDs_chosen + " with no other particles" << endl;
        }
    }
    // WRITE CONDITION
    if (input=="yes"){
        cout << PIDs_chosen + " with other particles" << endl;
    }
break;
}

outFile << endl;

// Event loop
outFile << "    Int_t eventnumber=0;" << endl;
outFile << "    while(c12.next()==true){" << endl;
outFile << "        eventnumber++;" << endl;
outFile << "        int evn_el_count=0;" << endl;
outFile << "        Int_t k = 0;" << endl;
outFile << "        auto particle = c12.getDetParticles();" << endl;
outFile << "        Int_t numofpart = particle.size();" << endl;
outFile << "        for(Int_t k=0;k<numofpart;k++){" << endl;

int evn_el_count=0;
for (int var_indx=0; var_indx<var_name_vect.size(); var_indx++){
    if (PID_vect.at(var_indx)=="11" && evn_el_count==0){
        outFile << "            // Beam-electron(scattered) kinematics" << endl;
        outFile << "            if (particle[k]->par()->getPid()==11 && evn_el_count==0){" << endl;
        outFile << "              elScat_LV.SetXYZM(particle[k]->par()->getPx(),particle[k]->par()->getPy(),particle[k]->par()->getPz(),0.000511);" << endl;
        outFile << "              evn_el_count++;" << endl;
        outFile << "            }" << endl;
        evn_el_count++;
    }
    outFile << "            if (particle[k]->par()->getPid()==" + PID_vect.at(var_indx) + "){" << endl;
    outFile << "              " + var_name_vect.at(var_indx) + "_Px=particle[k]->par()->getPx();" << endl;
    outFile << "              " + var_name_vect.at(var_indx) + "_Py=particle[k]->par()->getPy();" << endl;
    outFile << "              " + var_name_vect.at(var_indx) + "_Pz=particle[k]->par()->getPz();" << endl;
    outFile << "              " + var_name_vect.at(var_indx) + "_PID=particle[k]->par()->getPid();" << endl;
    outFile << "              " + var_name_vect.at(var_indx) + "_beta=particle[k]->par()->getBeta();" << endl;
    outFile << "              " + var_name_vect.at(var_indx) + "_chi2PID=particle[k]->par()->getChi2Pid();" << endl;
    outFile << "              " + var_name_vect.at(var_indx) + "_status=particle[k]->par()->getStatus();" << endl;
    // region calcualtion
    outFile << "              int region_abs = abs(particle[k]->par()->getStatus());" << endl;
    outFile << "	      string region_abs_str = std::to_string(region_abs);" << endl;
    outFile << "	      region_abs_str.replace(1, 3, 3, '0');" << endl;
    outFile << "              " + var_name_vect.at(var_indx) + "_region=std::stoi(region_abs_str);" << endl;
    outFile << "              float " + var_name_vect.at(var_indx) + "_M=" + "PDG_info->GetParticle(particle[k]->par()->getPid())->Mass();" << endl;
    outFile << "              " + var_name_vect.at(var_indx) + "_LV.SetXYZM(" + var_name_vect.at(var_indx) + "_Px," + var_name_vect.at(var_indx) + "_Py," + var_name_vect.at(var_indx) + "_Pz," + var_name_vect.at(var_indx) + "_M);" << endl;
    outFile << "              " + var_name_vect.at(var_indx) + "_E=" + var_name_vect.at(var_indx) + "_LV.E();" << endl;
    outFile << "              " + var_name_vect.at(var_indx) + "_Th=" + var_name_vect.at(var_indx) + "_LV.Theta();" << endl;
    outFile << "            }" << endl;
}

outFile << "        }" << endl;
outFile << endl;

std::string missAll_LV = "Beam_LV + Target_LV";
std::string missEAll = "Beam_LV.E() + Target_LV.E()";
for (int var_indx=0; var_indx<var_name_vect.size(); var_indx++){
    missAll_LV = missAll_LV + " - " + var_name_vect.at(var_indx) + "_LV";
    missEAll = missEAll + " - " + var_name_vect.at(var_indx) + "_LV.E()";
    // Confusion ahead: variables of the same name used here and also uploaded to outFile
    outFile << "        TLorentzVector miss_LV_" + var_name_vect.at(var_indx) + ";" << endl;
    outFile << "        float missE_" + var_name_vect.at(var_indx) + ";" << endl;
    std::string miss_LV = "Beam_LV + Target_LV";
    std::string missE = "Beam_LV.E() + Target_LV.E()";
    for (int var_indx_2=0; var_indx_2<var_name_vect.size(); var_indx_2++){
        if (var_indx!=var_indx_2){
            miss_LV = miss_LV + " - " + var_name_vect.at(var_indx_2) + "_LV"; 
            missE = missE + " - " + var_name_vect.at(var_indx_2) + "_LV.E()";
        }
    }
    outFile << "        miss_LV_" + var_name_vect.at(var_indx) + " = " + miss_LV + ";" << endl;
    outFile << "        MissMass_" + var_name_vect.at(var_indx) + " = miss_LV_" + var_name_vect.at(var_indx) + ".M();" << endl;
    outFile << "        MissMass2_" + var_name_vect.at(var_indx) + " = miss_LV_" + var_name_vect.at(var_indx) + ".M2();" << endl;
    outFile << "        missE_" + var_name_vect.at(var_indx) + " = " + missE + ";" << endl;
    outFile << "        MissEnergy_" + var_name_vect.at(var_indx) + " = missE_" + var_name_vect.at(var_indx) + ";" << endl;
}

outFile << "        TLorentzVector missAll_LV;" << endl;
outFile << "        missAll_LV = " + missAll_LV + ";" << endl; 
outFile << "        MissMass = missAll_LV.M();" << endl;
outFile << "        MissMass2 = missAll_LV.M2();" << endl;
// Inv mass loop
// Inv mass loop
for (size_t i = 0; i < Inv_names.size(); ++i) {
    outFile << "        InvMass_" + Inv_names[i]  + " = (" + Inv_formulae[i] + ").M();" << endl;
}
outFile << "        // (somewhat) miscellaneous" << endl;
outFile << "        MissTh = missAll_LV.Theta();" << endl;
outFile << "        MissE = " + missEAll + ";" << endl;
if (evn_el_count==1){
    outFile << "        // Beam-electron(scattered) kinematics" << endl;
    outFile << "        TLorentzVector gamma;" << endl;
    outFile << "        gamma = Beam_LV - elScat_LV;" << endl;
    outFile << "        Q2 = -gamma.M2();" << endl;
    outFile << "        Egamma = gamma.E();" << endl;
}
outFile << "        evn_el_count=0;" << endl;
outFile << endl;

cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
std::string condition;
while (true) {
    // Ask the user for input
    std::cout << "Any additional skimming condition(s)? (yes/no)" << endl;
    std::cout << "WARNING: condtion(s) must be specified and formatted correctly or else Skim Reader will FAIL," << endl;
    std::cout << "no additional skimming condition(s) is the recommended option." << endl;
    std::getline(std::cin, input);  // Get the user input
    // Check the input
    if (input!="no") {
        if (input!="yes") {
            std::cout << "Invalid input: Input must be yes or no" << endl;
            continue;  // Re-prompt user
        } else if (input=="yes"){
            std::cout << "Please enter additional skimming condition(s) (do not use quotation marks):" << endl;
            std::getline(std::cin, input2);  // Get the user input
            std::cout << "Submitted: " + input2 << endl;
            while (true) {
            // Ask the user for input
            std::cout << "Are you sure? (yes/no)" << endl;
            std::getline(std::cin, input3);  // Get the user input
            // Check if the input contains spaces
            if (input3!="no") {
                if (input3!="yes") {
                    std::cout << "Invalid input: Input must be yes or no" << endl;
                    continue;  // Re-prompt user
                } else if (input3=="yes"){
                    std::cout << "Skimming with: " + input2 << endl;
                    outFile << "        if (" + input2 + "){" << endl;
                    outFile << "            tree->Fill();" << endl;
                    outFile << "        }" << endl;
                }
            }
            // WRITE CONDITION
            if (input3=="no"){
                cout << "No additional skimming conditions to be submitted" << endl;
                outFile << "        tree->Fill();" << endl;
                break;
            }
        break;
        }
        }
    }
    // WRITE CONDITION
    if (input=="no"){
        cout << "No additional skimming conditions submitted" << endl;
        outFile << "        tree->Fill();" << endl;
    }
break;
}

outFile << endl;
outFile << "    }" << endl;
outFile << "}" << endl;
outFile << "tree->Write();" << endl;
outFile << endl;
outFile << "cout << \"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\" << endl;" << endl;
outFile << "cout << \"Skimmed tree saved to 'skim_tree.root'\" << endl;" << endl;
outFile << "cout << \"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\" << endl;" << endl;
outFile << endl;
outFile << "}" << endl;

cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
cout << "Your Skim Reader file has been built as saved as 'Skim_reader.C'" << endl;
cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}
