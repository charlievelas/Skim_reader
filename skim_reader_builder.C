#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string>

std::vector<std::string> particle_option_strings(const std::string& particles, const std::vector<std::string>& options) {
    std::map<std::string, int> counts;
    std::vector<std::string> id_order;

    // Parse particles and count IDs
    std::istringstream ss(particles);
    std::string token;
    while (std::getline(ss, token, ':')) {
        size_t comma = token.find(',');
        if (comma == std::string::npos) continue;
        std::string id = token.substr(comma + 1);
        if (counts[id] == 0) id_order.push_back(id);
        counts[id]++;
    }

    // Build result
    std::vector<std::string> result;
    for (size_t i = 0; i < id_order.size(); ++i) {
        std::ostringstream out;
        if (options[i] == "yes")
            out << "c12.addAtLeastPid(" << id_order[i] << "," << counts[id_order[i]] << ");";
        else
            out << "c12.addExactPid(" << id_order[i] << "," << counts[id_order[i]] << ");";
    result.push_back(out.str());
    }
    return result;
}

void skim_reader_builder(string SkimR_location, string blueprint_name, string particles, string hipo_slurm, string beam_energy, string target_mass, const std::vector<std::string>& options_particles, string other_particles, string FT_based, string scat_el, std::string add_conditions, const std::vector<std::string>& all_branches){
// Create the file
std::string file = std::string(blueprint_name) + "_SkimReader.C";
std::ofstream outFile(file);

// Save header files
string part1_name = SkimR_location + "/skim_reader_part1.txt";
std::ifstream part1(part1_name);
std::string line1;
while (std::getline(part1, line1)) {
    outFile << line1 << std::endl;
}
part1.close();

// HIPO or slurm
if (hipo_slurm=="slurm"){
    outFile << "void " << std::string(blueprint_name) << "_SkimReader(TString infile, TString outfile){" << endl;
    outFile << endl;
    outFile << "TString in_file_name = infile;" << endl;
    outFile << "TChain chain(\"hipo\");" << endl;
    outFile << "chain.Add(in_file_name.Data());" << endl;
    outFile << "auto files=chain.GetListOfFiles();" << endl;
    outFile << "TFile *tree_file = new TFile(outfile,\"recreate\");" << endl;
    outFile << "TTree *tree = new TTree(\"tree\",\"tree\");" << endl;
    outFile << endl;   
    
} else {
    outFile << "void "<< std::string(blueprint_name) << "_SkimReader(){" << endl;
    outFile << endl;
    outFile << "TString in_file_name = \"" << hipo_slurm << "\";" << endl;
    outFile << "TChain chain(\"hipo\");" << endl;
    outFile << "chain.Add(in_file_name.Data());" << endl;
    outFile << "auto files=chain.GetListOfFiles();" << endl;
    outFile << "string outFile_name = \"" + blueprint_name + "_skimmed_tree.root\";" << endl;
    outFile << "TFile *tree_file = new TFile(outFile_name.c_str(),\"recreate\");" << endl;
    outFile << "TTree *tree = new TTree(\"tree\",\"tree\");" << endl;
    outFile << endl;
}

// Beam and target setup
outFile << "auto PDG_info=TDatabasePDG::Instance();" << std::endl;
outFile << "TLorentzVector Beam_LV;" << std::endl;
string beam_string = "Beam_LV.SetXYZM(0,0," + beam_energy + ",0.000511);";
outFile << beam_string << std::endl;
outFile << "TLorentzVector Target_LV;" << std::endl;
string target_string = "Target_LV.SetXYZM(0,0,0," + target_mass + ");";
outFile << target_string << std::endl;
outFile << std::endl;

// Initialisations
for (const std::string& branch : all_branches) {
    if (branch=="Egamma" && scat_el=="no"|| branch=="Q2" && scat_el=="no"|| branch=="Pol" && scat_el=="no") continue;
    outFile << "float " << branch << ";" << std::endl;
}
outFile << "" << endl;

// All branches
for (const std::string& branch : all_branches) {
    if (branch=="Egamma" && scat_el=="no"|| branch=="Q2" && scat_el=="no"|| branch=="Pol" && scat_el=="no") continue;
    outFile << "tree->Branch(\"" << branch << "\",&" << branch << ");" << std::endl;
}
outFile << "" << endl;

// Save particle variable names and PIDs to vectors
std::vector<std::string> var_names;
std::vector<std::string> PIDs;
std::istringstream particles_stream(particles);
std::string token;
while (std::getline(particles_stream, token, ':')) {
    size_t comma = token.find(',');
    if (comma != std::string::npos) {
        var_names.push_back(token.substr(0, comma));
        PIDs.push_back(token.substr(comma + 1));
    }
}

// Create TLorentzVector
for (const std::string& var_name : var_names) {
    outFile << "TLorentzVector " << var_name << "_LV;" << std::endl;
}
outFile << "" << endl;

// File and event loop
outFile << "for(Int_t i=0;i<files->GetEntries();i++){" << endl;
outFile << "" << endl;
outFile << "    clas12reader c12(files->At(i)->GetTitle());" << endl;

// 'More than' particle conditions
std::vector<std::string> particle_options = particle_option_strings(particles, options_particles);
for (const std::string& option : particle_options) {
    outFile << "    " << option << endl;
}

// Other particle conditions
if (other_particles=="no"){
    outFile << "    c12.addZeroOfRestPid();" << endl;
    outFile << endl;
}

// FT based events
if (FT_based=="yes") outFile << "    c12.useFTBased();" << endl;
outFile << endl;

// Start of event loop
outFile << "    // Individual particle branches" << endl;
string part2_name = SkimR_location + "/skim_reader_part2.txt";
std::ifstream part2(part2_name);
std::string line2;
while (std::getline(part2, line2)) {
    outFile << line2 << std::endl;
}
part2.close();

// Calculate individual particle branches
string part3_name = SkimR_location + "/skim_reader_part3.txt";
for (int PID_indx=0; PID_indx<PIDs.size(); PID_indx++){
    std::ifstream part3(part3_name);
    std::string line3;
    outFile << "            if (particle[k]->par()->getPid()==" + PIDs.at(PID_indx) + "){" << std::endl;
    while (std::getline(part3, line3)) {
        // Replace particle name in lines
        size_t pos = 0;
        while ((pos = line3.find("p4rtRepl4ce", pos)) != std::string::npos) {
            line3.replace(pos, 11, var_names.at(PID_indx));
            pos += var_names.at(PID_indx).length();
        }
        // Save line to outFile
        outFile << line3 << std::endl;
    }
    outFile << "            }" << std::endl;
}
outFile << std::endl;
outFile << "        }" << endl;

// Calculate event branches
outFile << "        // Event branches" << endl;
int start_indx = var_names.size()*17;
for (int br_indx = 0; br_indx<all_branches.size(); br_indx++){
    // Check if string starts with "InvMass", "MissMass" or "MissMass2"
    string branch_repl = all_branches.at(br_indx);
    if (branch_repl.rfind("InvMass_", 0) == 0) {
        outFile << "        " << branch_repl;
        string branch_repl_new = branch_repl.substr(8);
        size_t pos = 0;
        while ((pos = branch_repl_new.find("_", pos)) != std::string::npos) {
            branch_repl_new.replace(pos, 1, "_LV + ");
            pos += 3;
        }
        outFile << " = (" << branch_repl_new << "_LV).M();" << endl;
    } 
    // 
    else if (branch_repl.rfind("MissMass_", 0) == 0) {
        outFile << "        " << branch_repl;
        string branch_repl_new = branch_repl.substr(9);
        size_t pos = 0;
        while ((pos = branch_repl_new.find("_", pos)) != std::string::npos) {
            branch_repl_new.replace(pos, 1, "_LV + ");
            pos += 3;
        }
        outFile << " = ((Beam_LV + Target_LV) - (" << branch_repl_new << "_LV)).M();" << endl;
    } else if (branch_repl.rfind("MissMass2_", 0) == 0) {
        outFile << "        " << branch_repl;
        string branch_repl_new = branch_repl.substr(10);
        size_t pos = 0;
        while ((pos = branch_repl_new.find("_", pos)) != std::string::npos) {
            branch_repl_new.replace(pos, 1, "_LV + ");
            pos += 3;
        }
        outFile << " = ((Beam_LV + Target_LV) - (" << branch_repl_new << "_LV)).M2();" << endl;
    } else if (branch_repl.rfind("Triggers", 0) == 0) {
        outFile << "        " << branch_repl << " = c12.runconfig()->getTrigger();" << endl; 
    } else if (branch_repl.rfind("Egamma", 0) == 0 && scat_el!="no") {
        outFile << "        " << branch_repl << " = (Beam_LV - " << scat_el + "_LV).E();" << endl; 
    } else if (branch_repl.rfind("Q2", 0) == 0 && scat_el!="no") {
        outFile << "        " << branch_repl << " = -(Beam_LV - " << scat_el + "_LV).M2();" << endl; 
    }

}

    // Fill tree
    outFile << endl;
    if (add_conditions!="no"){
        outFile << "        if (" << add_conditions << "){" << endl;
        outFile << "            tree->Fill();" << endl;
        outFile << "        }" << endl;
    } else{
        outFile << "        tree->Fill();" << endl;
    }
    outFile << "    }" << endl;
    outFile << "}" << endl;
    outFile << endl;
    outFile << "tree->Write();" << endl;
    outFile << endl;

    // Saved tree statement
    outFile << "cout << \"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\" << endl;" << endl;
    outFile << "cout << \"Skimmed tree saved to '" + blueprint_name + "_skimmed_tree.root'\" << endl;" << endl;
    outFile << "cout << \"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\" << endl;" << endl;

    // Skim reader print statement
    cout << file << " has been created." << endl;

    outFile << "}" << endl;
    outFile << "}" << endl;
}

