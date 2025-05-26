#include <cstdlib>
#include <iostream>
#include <chrono>
#include <TFile.h>
#include <TTree.h>
#include <TApplication.h>
#include <TROOT.h>
#include <TDatabasePDG.h>
#include <TLorentzVector.h>
#include <TH1.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TBenchmark.h>
#include "clas12reader.h"
using namespace clas12;

void Skim_reader(){

// Input file, output file, HIPO file and Ttree
TString in_file_name = "file";
TChain chain("hipo");
chain.Add(in_file_name.Data());
auto files=chain.GetListOfFiles();
TFile *tree_file = new TFile("skim_tree.root","recreate");
TTree *tree = new TTree("tree","tree");

auto PDG_info=TDatabasePDG::Instance();
TLorentzVector Beam_LV;
Beam_LV.SetXYZM(0,0,10.2,0.000511);
TLorentzVector Target_LV;
Target_LV.SetXYZM(0,0,0,0.93827);
TLorentzVector elScat_LV;

float el_Px;
float el_Py;
float el_Pz;
float el_PID;
float el_beta;
float el_chi2PID;
float el_status;
float el_region;
float el_E;
float el_Th;
float MissMass_el;
float MissMass2_el;
float MissEnergy_el;
TLorentzVector el_LV; // No associated branch
float el_Px;
float el_Py;
float el_Pz;
float el_PID;
float el_beta;
float el_chi2PID;
float el_status;
float el_region;
float el_E;
float el_Th;
float MissMass_el;
float MissMass2_el;
float MissEnergy_el;
TLorentzVector el_LV; // No associated branch
float MissMass;
float MissMass2;
float InvMass_el_el;
float MissTh;
float MissE;
float Q2;
float Egamma;

tree->Branch("el_Px",&el_Px);
tree->Branch("el_Py",&el_Py);
tree->Branch("el_Pz",&el_Pz);
tree->Branch("el_PID",&el_PID);
tree->Branch("el_beta",&el_beta);
tree->Branch("el_chi2PID",&el_chi2PID);
tree->Branch("el_status",&el_status);
tree->Branch("el_region",&el_region);
tree->Branch("el_E",&el_E);
tree->Branch("el_Th",&el_Th);
tree->Branch("MissMass_el",&MissMass_el);
tree->Branch("MissMass2_el",&MissMass2_el);
tree->Branch("MissEnergy_el",&MissEnergy_el);
tree->Branch("el_Px",&el_Px);
tree->Branch("el_Py",&el_Py);
tree->Branch("el_Pz",&el_Pz);
tree->Branch("el_PID",&el_PID);
tree->Branch("el_beta",&el_beta);
tree->Branch("el_chi2PID",&el_chi2PID);
tree->Branch("el_status",&el_status);
tree->Branch("el_region",&el_region);
tree->Branch("el_E",&el_E);
tree->Branch("el_Th",&el_Th);
tree->Branch("MissMass_el",&MissMass_el);
tree->Branch("MissMass2_el",&MissMass2_el);
tree->Branch("MissEnergy_el",&MissEnergy_el);
tree->Branch("MissMass",&MissMass);
tree->Branch("MissMass2",&MissMass2);
tree->Branch("InvMass_el_el",&InvMass_el_el);
tree->Branch("MissTh",&MissTh);
tree->Branch("MissE",&MissE);
tree->Branch("Q2",&Q2);
tree->Branch("Egamma",&Egamma);

for(Int_t i=0;i<files->GetEntries();i++){

    clas12reader c12(files->At(i)->GetTitle());

