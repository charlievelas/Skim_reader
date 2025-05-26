#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>

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

void blueprint_builder(const char* filename, const char* particles) {

// Create the file
std::string file = std::string(filename) + ".txt";
std::ofstream outFile(file);

// Save particles
outFile << "Particles:" << endl;
std::string particles_str = std::string(particles);
std::replace(particles_str.begin(),particles_str.end(),':',' ');
outFile << particles_str << endl;
outFile << endl;

// Beam energy
outFile << "Beam energy (GeV)?" << endl;
outFile << endl;
outFile << endl;

// Target mass
outFile << "Target mass (Gev)?" << endl;
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
outFile << "Use FT based time of event for FT electron? (yes/no)" << endl;
outFile << endl;
outFile << endl;

// Scattered electron
outFile << "Calculate scattered electron kinematics? (empty=no)" << endl;
outFile << "Scattered electron variable name:" << endl;
outFile << endl;

// Gottfried-Jackson frame
outFile << "Calculate Gottfried-Jackson Variables? (empty=no)" << endl;
//UNDER CONSTRUCTION ...
outFile << "..." << endl;
outFile << endl;

// Addtional conditions
outFile << "Additional conditions (one condition per line, all branches below)? (empty=no)" << endl;
outFile << endl;
outFile << endl;

// All branches
outFile << "All branches:" << endl;


}