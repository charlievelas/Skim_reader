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

// HIPO or slum optimised

auto PDG_info=TDatabasePDG::Instance();
TLorentzVector Beam_LV;
Beam_LV.SetXYZM(0,0,10,0.000511);
TLorentzVector Target_LV;
Target_LV.SetXYZM(0,0,0,0.9999);
TLorentzVector elScat_LV;

float first;
float second;
float third;

tree->Branch("first",&first);
tree->Branch("second",&second);
tree->Branch("third",&third);

TLorentzVector el_LV;
TLorentzVector pro_LV;
TLorentzVector kp_LV;

for(Int_t i=0;i<files->GetEntries();i++){

    clas12reader c12(files->At(i)->GetTitle());
    c12.addAtLeastPid(11,1);
    c12.addAtLeastPid(2212,1);
    c12.addAtLeastPid(32,1);

    Int_t eventnumber=0;
    while(c12.next()==true){
        eventnumber++;
        Int_t k = 0;
        auto particle = c12.getDetParticles();
        Int_t numofpart = particle.size();
        for(Int_t k=0;k<numofpart;k++){

