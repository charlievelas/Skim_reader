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
    c12.addAtLeastPid(321,1);

    Int_t eventnumber=0;
    while(c12.next()==true){
        eventnumber++;
        Int_t k = 0;
        auto particle = c12.getDetParticles();
        Int_t numofpart = particle.size();
        for(Int_t k=0;k<numofpart;k++){
            if (particle[k]->par()->getPid()==11){
                el_px=particle[k]->par()->getPx();
                el_py=particle[k]->par()->getPx();
                el_pz=particle[k]->par()->getPx();
                el_LV.SetXYZM(el_px,el_py,el_pz,PDG_info->GetParticle(particle[k]->par()->getPid())->Mass());
                el_pMag=el_LV.Rho();
                el_vx=particle[k]->par()->getVx();
                el_vy=particle[k]->par()->getVy();
                el_vz=particle[k]->par()->getVz();
                el_vt=particle[k]->par()->getVt();
                el_E=el_LV.E()
                el_theta=el_LV.Theta();
                el_phi=el_LV.Phi();
                el_M=el_LV.M();
                el_beta=particle[k]->par()->getBeta();
                el_PID=particle[k]->par()->getPid();
                el_chi2PID=particle[k]->par()->getChi2Pid();
                el_status=particle[k]->par()->getStatus();
                el_region=el_status.replace(1, 3, 3, '0');
            }
            if (particle[k]->par()->getPid()==2212){
                pro_px=particle[k]->par()->getPx();
                pro_py=particle[k]->par()->getPx();
                pro_pz=particle[k]->par()->getPx();
                pro_LV.SetXYZM(pro_px,pro_py,pro_pz,PDG_info->GetParticle(particle[k]->par()->getPid())->Mass());
                pro_pMag=pro_LV.Rho();
                pro_vx=particle[k]->par()->getVx();
                pro_vy=particle[k]->par()->getVy();
                pro_vz=particle[k]->par()->getVz();
                pro_vt=particle[k]->par()->getVt();
                pro_E=pro_LV.E()
                pro_theta=pro_LV.Theta();
                pro_phi=pro_LV.Phi();
                pro_M=pro_LV.M();
                pro_beta=particle[k]->par()->getBeta();
                pro_PID=particle[k]->par()->getPid();
                pro_chi2PID=particle[k]->par()->getChi2Pid();
                pro_status=particle[k]->par()->getStatus();
                pro_region=pro_status.replace(1, 3, 3, '0');
            }
            if (particle[k]->par()->getPid()==321){
                kp_px=particle[k]->par()->getPx();
                kp_py=particle[k]->par()->getPx();
                kp_pz=particle[k]->par()->getPx();
                kp_LV.SetXYZM(kp_px,kp_py,kp_pz,PDG_info->GetParticle(particle[k]->par()->getPid())->Mass());
                kp_pMag=kp_LV.Rho();
                kp_vx=particle[k]->par()->getVx();
                kp_vy=particle[k]->par()->getVy();
                kp_vz=particle[k]->par()->getVz();
                kp_vt=particle[k]->par()->getVt();
                kp_E=kp_LV.E()
                kp_theta=kp_LV.Theta();
                kp_phi=kp_LV.Phi();
                kp_M=kp_LV.M();
                kp_beta=particle[k]->par()->getBeta();
                kp_PID=particle[k]->par()->getPid();
                kp_chi2PID=particle[k]->par()->getChi2Pid();
                kp_status=particle[k]->par()->getStatus();
                kp_region=kp_status.replace(1, 3, 3, '0');
            }
