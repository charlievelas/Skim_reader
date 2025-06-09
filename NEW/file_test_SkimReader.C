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
Beam_LV.SetXYZM(0,0,10.2,0.000511);
TLorentzVector Target_LV;
Target_LV.SetXYZM(0,0,0,0.943);
TLorentzVector elScat_LV;

float a;
float b;
float c;

tree->Branch("a",&a);
tree->Branch("b",&b);
tree->Branch("c",&c);

TLorentzVector el1_LV;
TLorentzVector pro1_LV;
TLorentzVector el2_LV;
TLorentzVector nuetron_LV;

for(Int_t i=0;i<files->GetEntries();i++){

    clas12reader c12(files->At(i)->GetTitle());
    c12.addExactPid(11,2);
    c12.addAtLeastPid(2212,1);
    c12.addExactPid(2112,1);
    c12.addZeroOfRestPid();

    Int_t eventnumber=0;
    while(c12.next()==true){
        eventnumber++;
        Int_t k = 0;
        auto particle = c12.getDetParticles();
        Int_t numofpart = particle.size();
        for(Int_t k=0;k<numofpart;k++){

