#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>

// Makes the 'more than particles' strings
std::vector<std::string> more_than(const std::string& input) {
    // PID list
    std::unordered_map<std::string, std::string> pid_to_name = {
        {"-11", "e-"}, {"11", "e+"}, {"22", "gamma"},
        {"-45", "d-"}, {"45", "d"},
        {"-211", "pi-"}, {"211", "pi+"},
        {"-321", "K-"}, {"321", "K+"},
        {"2112", "n"}, {"-2212", "p-"}, {"2212", "p"}
    };

    std::map<std::string, int> counts;
    std::vector<std::string> order;

    std::istringstream ss(input);
    std::string token;
    while (std::getline(ss, token, ':')) {
        size_t comma = token.find(',');
        if (comma == std::string::npos) continue;
        std::string id = token.substr(comma + 1);
        auto it = pid_to_name.find(id);
        if (it != pid_to_name.end()) {
            if (counts[it->second] == 0) order.push_back(it->second);
            counts[it->second]++;
        }
    }

    std::vector<std::string> more_than_strings;
    for (const auto& particle : order) {
        std::ostringstream oss;
        oss << "Allow events with more than " << counts[particle] << " " << particle << "? (yes/no)";
        more_than_strings.push_back(oss.str());
    }
    return more_than_strings;
}

// Makes all the particle branch names
std::vector<std::string> particle_branches(const std::string& input) {
    // List of suffixes to append
    std::vector<std::string> suffixes = {
        "_px", "_py", "_pz", "_pMag", "_vx", "_vy", "_vz", "_vt",
        "_E", "_theta", "_phi", "_M", "_beta", "_PID", "_chi2PID", "_status", "_region"
    };

    std::vector<std::string> particle_branches;
    std::istringstream ss(input);
    std::string token;
    while (std::getline(ss, token, ':')) {
        size_t comma = token.find(',');
        if (comma == std::string::npos) continue;
        std::string var = token.substr(0, comma);
        for (const auto& suf : suffixes) {
            particle_branches.push_back(var + suf);
        }
    }
    return particle_branches;
}

// Invariant and missing mass branches
    std::vector<std::string> inv_miss_mass_branches(const std::string& input) {
    // Parse variable names in order
    std::vector<std::string> vars;
    std::istringstream ss(input);
    std::string token;
    while (std::getline(ss, token, ':')) {
        size_t comma = token.find(',');
        if (comma == std::string::npos) continue;
        vars.push_back(token.substr(0, comma));
    }

    // Generate all unique, non-repeating combinations (size >= 2) in order of appearance
    std::vector<std::string> combos;
    int n = vars.size();
    for (int k = 1; k <= n; ++k) {
        std::vector<int> idx(k);
        for (int i = 0; i < k; ++i) idx[i] = i;
        while (true) {
            std::string combo = vars[idx[0]];
            for (int j = 1; j < k; ++j) combo += "_" + vars[idx[j]];
            combos.push_back(combo);
            // Next combination
            int i = k - 1;
            while (i >= 0 && idx[i] == n - k + i) --i;
            if (i < 0) break;
            ++idx[i];
            for (int j = i + 1; j < k; ++j) idx[j] = idx[j - 1] + 1;
        }
    }

    // Add InvMass_ first, then MissMass_ in the same order
    std::vector<std::string> inv_miss_particle_strings;
    for (int j = n; j < combos.size(); ++j)
        inv_miss_particle_strings.push_back("InvMass_" + combos.at(j));
    for (const auto& combo : combos)
        inv_miss_particle_strings.push_back("MissMass_" + combo);
    // Add MissMass2_ for the last MissMass_ entry
    if (!combos.empty()) {
        inv_miss_particle_strings.push_back("MissMass2_" + combos.back());
    }

    return inv_miss_particle_strings;
}


// Main function
void blueprint_builder(const char* filename, const char* particles) {

// Create the file
std::string file = std::string(filename) + ".txt";
std::ofstream outFile(file);

// Save blueprint name
outFile << "Blueprint name:" << endl;
string filename_str = filename;
filename_str.erase(filename_str.length()-10);
outFile << filename_str << endl;
outFile << endl;

// Save particles
outFile << "Particles:" << endl;
outFile << particles << endl;
outFile << endl;

// Slurm optimisation
outFile << "Enter run/HIPO file location or enter \"slurm\" to configure SkimReader for slurm:" << endl;
outFile << endl;
outFile << endl;

// Beam energy
outFile << "Electron beam energy (GeV)?" << endl;
outFile << endl;
outFile << endl;

// Target mass
outFile << "Target mass (GeV)?" << endl;
outFile << endl;
outFile << endl;

// More than particles chosen
std::vector<std::string> more_than_strings = more_than(particles);
for (int i=0; i<more_than_strings.size();i++){
    outFile << more_than_strings.at(i) << endl;
    outFile << endl;
    outFile << endl;
}

// Other particles
outFile << "Allow events with other particles? (yes/no)" << endl;
outFile << endl;
outFile << endl;

// FT based
outFile << "Use FT based time for event? (yes/no)" << endl;
outFile << endl;
outFile << endl;

// Scattered electron
outFile << "Calculate scattered electron kinematics? (empty=no)" << endl;
outFile << "Scattered electron variable name:" << endl;
outFile << endl;
outFile << endl;

// Addtional conditions
outFile << "Additional conditions (all conditions on one line)? (empty=no)" << endl;
outFile << endl;
outFile << endl;

// All branches
outFile << "All branches (DO NOT CHANGE):" << endl;
// Particle branches
std::vector<std::string> particle_branch_strings = particle_branches(particles);
for (int i=0; i<particle_branch_strings.size();i++){
    outFile << particle_branch_strings.at(i) << endl;
}

// Invariant and missing mass branches
std::vector<std::string> inv_miss_mass_branch_strings = inv_miss_mass_branches(particles);
for (int i=0; i<inv_miss_mass_branch_strings.size();i++){
    outFile << inv_miss_mass_branch_strings.at(i) << endl;
}

// Trigger bits
outFile << "Triggers" << endl;

// Scattered electron kinematics
outFile << "Egamma" << endl;
outFile << "Q2" << endl;

}

