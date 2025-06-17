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

TString in_file_name = file.hipo;
TChain chain("hipo");
chain.Add(in_file_name.Data());
auto files=chain.GetListOfFiles();
string outFile_name = "epKK_skimmed_tree.root";
TFile *tree_file = new TFile(outFile_name,"recreate");
TTree *tree = new TTree("tree","tree");

auto PDG_info=TDatabasePDG::Instance();
TLorentzVector Beam_LV;
Beam_LV.SetXYZM(0,0,10.2,0.000511);
TLorentzVector Target_LV;
Target_LV.SetXYZM(0,0,0,0.943);

float el_px;
float el_py;
float el_pz;
float el_pMag;
float el_vx;
float el_vy;
float el_vz;
float el_vt;
float el_E;
float el_theta;
float el_phi;
float el_M;
float el_beta;
float el_PID;
float el_chi2PID;
float el_status;
float el_region;
float pro_px;
float pro_py;
float pro_pz;
float pro_pMag;
float pro_vx;
float pro_vy;
float pro_vz;
float pro_vt;
float pro_E;
float pro_theta;
float pro_phi;
float pro_M;
float pro_beta;
float pro_PID;
float pro_chi2PID;
float pro_status;
float pro_region;
float kp1_px;
float kp1_py;
float kp1_pz;
float kp1_pMag;
float kp1_vx;
float kp1_vy;
float kp1_vz;
float kp1_vt;
float kp1_E;
float kp1_theta;
float kp1_phi;
float kp1_M;
float kp1_beta;
float kp1_PID;
float kp1_chi2PID;
float kp1_status;
float kp1_region;
float kp2_px;
float kp2_py;
float kp2_pz;
float kp2_pMag;
float kp2_vx;
float kp2_vy;
float kp2_vz;
float kp2_vt;
float kp2_E;
float kp2_theta;
float kp2_phi;
float kp2_M;
float kp2_beta;
float kp2_PID;
float kp2_chi2PID;
float kp2_status;
float kp2_region;
float InvMass_el_pro;
float InvMass_el_kp1;
float InvMass_el_kp2;
float InvMass_pro_kp1;
float InvMass_pro_kp2;
float InvMass_kp1_kp2;
float InvMass_el_pro_kp1;
float InvMass_el_pro_kp2;
float InvMass_el_kp1_kp2;
float InvMass_pro_kp1_kp2;
float InvMass_el_pro_kp1_kp2;
float MissMass_el;
float MissMass_pro;
float MissMass_kp1;
float MissMass_kp2;
float MissMass_el_pro;
float MissMass_el_kp1;
float MissMass_el_kp2;
float MissMass_pro_kp1;
float MissMass_pro_kp2;
float MissMass_kp1_kp2;
float MissMass_el_pro_kp1;
float MissMass_el_pro_kp2;
float MissMass_el_kp1_kp2;
float MissMass_pro_kp1_kp2;
float MissMass_el_pro_kp1_kp2;
float MissMass2_el_pro_kp1_kp2;
float TrigBits;
float Egamma;
float Q2;
float Pol;

tree->Branch("el_px",&el_px);
tree->Branch("el_py",&el_py);
tree->Branch("el_pz",&el_pz);
tree->Branch("el_pMag",&el_pMag);
tree->Branch("el_vx",&el_vx);
tree->Branch("el_vy",&el_vy);
tree->Branch("el_vz",&el_vz);
tree->Branch("el_vt",&el_vt);
tree->Branch("el_E",&el_E);
tree->Branch("el_theta",&el_theta);
tree->Branch("el_phi",&el_phi);
tree->Branch("el_M",&el_M);
tree->Branch("el_beta",&el_beta);
tree->Branch("el_PID",&el_PID);
tree->Branch("el_chi2PID",&el_chi2PID);
tree->Branch("el_status",&el_status);
tree->Branch("el_region",&el_region);
tree->Branch("pro_px",&pro_px);
tree->Branch("pro_py",&pro_py);
tree->Branch("pro_pz",&pro_pz);
tree->Branch("pro_pMag",&pro_pMag);
tree->Branch("pro_vx",&pro_vx);
tree->Branch("pro_vy",&pro_vy);
tree->Branch("pro_vz",&pro_vz);
tree->Branch("pro_vt",&pro_vt);
tree->Branch("pro_E",&pro_E);
tree->Branch("pro_theta",&pro_theta);
tree->Branch("pro_phi",&pro_phi);
tree->Branch("pro_M",&pro_M);
tree->Branch("pro_beta",&pro_beta);
tree->Branch("pro_PID",&pro_PID);
tree->Branch("pro_chi2PID",&pro_chi2PID);
tree->Branch("pro_status",&pro_status);
tree->Branch("pro_region",&pro_region);
tree->Branch("kp1_px",&kp1_px);
tree->Branch("kp1_py",&kp1_py);
tree->Branch("kp1_pz",&kp1_pz);
tree->Branch("kp1_pMag",&kp1_pMag);
tree->Branch("kp1_vx",&kp1_vx);
tree->Branch("kp1_vy",&kp1_vy);
tree->Branch("kp1_vz",&kp1_vz);
tree->Branch("kp1_vt",&kp1_vt);
tree->Branch("kp1_E",&kp1_E);
tree->Branch("kp1_theta",&kp1_theta);
tree->Branch("kp1_phi",&kp1_phi);
tree->Branch("kp1_M",&kp1_M);
tree->Branch("kp1_beta",&kp1_beta);
tree->Branch("kp1_PID",&kp1_PID);
tree->Branch("kp1_chi2PID",&kp1_chi2PID);
tree->Branch("kp1_status",&kp1_status);
tree->Branch("kp1_region",&kp1_region);
tree->Branch("kp2_px",&kp2_px);
tree->Branch("kp2_py",&kp2_py);
tree->Branch("kp2_pz",&kp2_pz);
tree->Branch("kp2_pMag",&kp2_pMag);
tree->Branch("kp2_vx",&kp2_vx);
tree->Branch("kp2_vy",&kp2_vy);
tree->Branch("kp2_vz",&kp2_vz);
tree->Branch("kp2_vt",&kp2_vt);
tree->Branch("kp2_E",&kp2_E);
tree->Branch("kp2_theta",&kp2_theta);
tree->Branch("kp2_phi",&kp2_phi);
tree->Branch("kp2_M",&kp2_M);
tree->Branch("kp2_beta",&kp2_beta);
tree->Branch("kp2_PID",&kp2_PID);
tree->Branch("kp2_chi2PID",&kp2_chi2PID);
tree->Branch("kp2_status",&kp2_status);
tree->Branch("kp2_region",&kp2_region);
tree->Branch("InvMass_el_pro",&InvMass_el_pro);
tree->Branch("InvMass_el_kp1",&InvMass_el_kp1);
tree->Branch("InvMass_el_kp2",&InvMass_el_kp2);
tree->Branch("InvMass_pro_kp1",&InvMass_pro_kp1);
tree->Branch("InvMass_pro_kp2",&InvMass_pro_kp2);
tree->Branch("InvMass_kp1_kp2",&InvMass_kp1_kp2);
tree->Branch("InvMass_el_pro_kp1",&InvMass_el_pro_kp1);
tree->Branch("InvMass_el_pro_kp2",&InvMass_el_pro_kp2);
tree->Branch("InvMass_el_kp1_kp2",&InvMass_el_kp1_kp2);
tree->Branch("InvMass_pro_kp1_kp2",&InvMass_pro_kp1_kp2);
tree->Branch("InvMass_el_pro_kp1_kp2",&InvMass_el_pro_kp1_kp2);
tree->Branch("MissMass_el",&MissMass_el);
tree->Branch("MissMass_pro",&MissMass_pro);
tree->Branch("MissMass_kp1",&MissMass_kp1);
tree->Branch("MissMass_kp2",&MissMass_kp2);
tree->Branch("MissMass_el_pro",&MissMass_el_pro);
tree->Branch("MissMass_el_kp1",&MissMass_el_kp1);
tree->Branch("MissMass_el_kp2",&MissMass_el_kp2);
tree->Branch("MissMass_pro_kp1",&MissMass_pro_kp1);
tree->Branch("MissMass_pro_kp2",&MissMass_pro_kp2);
tree->Branch("MissMass_kp1_kp2",&MissMass_kp1_kp2);
tree->Branch("MissMass_el_pro_kp1",&MissMass_el_pro_kp1);
tree->Branch("MissMass_el_pro_kp2",&MissMass_el_pro_kp2);
tree->Branch("MissMass_el_kp1_kp2",&MissMass_el_kp1_kp2);
tree->Branch("MissMass_pro_kp1_kp2",&MissMass_pro_kp1_kp2);
tree->Branch("MissMass_el_pro_kp1_kp2",&MissMass_el_pro_kp1_kp2);
tree->Branch("MissMass2_el_pro_kp1_kp2",&MissMass2_el_pro_kp1_kp2);
tree->Branch("TrigBits",&TrigBits);
tree->Branch("Egamma",&Egamma);
tree->Branch("Q2",&Q2);
tree->Branch("Pol",&Pol);

TLorentzVector el_LV;
TLorentzVector pro_LV;
TLorentzVector kp1_LV;
TLorentzVector kp2_LV;

for(Int_t i=0;i<files->GetEntries();i++){

    clas12reader c12(files->At(i)->GetTitle());
    c12.addExactPid(11,1);
    c12.addAtLeastPid(2212,1);
    c12.addExactPid(321,2);
    c12.addZeroOfRestPid();

    c12.useFTBased();

    // Individual particle branches
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
                kp1_px=particle[k]->par()->getPx();
                kp1_py=particle[k]->par()->getPx();
                kp1_pz=particle[k]->par()->getPx();
                kp1_LV.SetXYZM(kp1_px,kp1_py,kp1_pz,PDG_info->GetParticle(particle[k]->par()->getPid())->Mass());
                kp1_pMag=kp1_LV.Rho();
                kp1_vx=particle[k]->par()->getVx();
                kp1_vy=particle[k]->par()->getVy();
                kp1_vz=particle[k]->par()->getVz();
                kp1_vt=particle[k]->par()->getVt();
                kp1_E=kp1_LV.E()
                kp1_theta=kp1_LV.Theta();
                kp1_phi=kp1_LV.Phi();
                kp1_M=kp1_LV.M();
                kp1_beta=particle[k]->par()->getBeta();
                kp1_PID=particle[k]->par()->getPid();
                kp1_chi2PID=particle[k]->par()->getChi2Pid();
                kp1_status=particle[k]->par()->getStatus();
                kp1_region=kp1_status.replace(1, 3, 3, '0');
            }
            if (particle[k]->par()->getPid()==321){
                kp2_px=particle[k]->par()->getPx();
                kp2_py=particle[k]->par()->getPx();
                kp2_pz=particle[k]->par()->getPx();
                kp2_LV.SetXYZM(kp2_px,kp2_py,kp2_pz,PDG_info->GetParticle(particle[k]->par()->getPid())->Mass());
                kp2_pMag=kp2_LV.Rho();
                kp2_vx=particle[k]->par()->getVx();
                kp2_vy=particle[k]->par()->getVy();
                kp2_vz=particle[k]->par()->getVz();
                kp2_vt=particle[k]->par()->getVt();
                kp2_E=kp2_LV.E()
                kp2_theta=kp2_LV.Theta();
                kp2_phi=kp2_LV.Phi();
                kp2_M=kp2_LV.M();
                kp2_beta=particle[k]->par()->getBeta();
                kp2_PID=particle[k]->par()->getPid();
                kp2_chi2PID=particle[k]->par()->getChi2Pid();
                kp2_status=particle[k]->par()->getStatus();
                kp2_region=kp2_status.replace(1, 3, 3, '0');
            }

        // Event branches
        InvMass_el_pro = (el_LV + pro_LV)).M();
        InvMass_el_kp1 = (el_LV + kp1_LV)).M();
        InvMass_el_kp2 = (el_LV + kp2_LV)).M();
        InvMass_pro_kp1 = (pro_LV + kp1_LV)).M();
        InvMass_pro_kp2 = (pro_LV + kp2_LV)).M();
        InvMass_kp1_kp2 = (kp1_LV + kp2_LV)).M();
        InvMass_el_pro_kp1 = (el_LV + pro_LV + kp1_LV)).M();
        InvMass_el_pro_kp2 = (el_LV + pro_LV + kp2_LV)).M();
        InvMass_el_kp1_kp2 = (el_LV + kp1_LV + kp2_LV)).M();
        InvMass_pro_kp1_kp2 = (pro_LV + kp1_LV + kp2_LV)).M();
        InvMass_el_pro_kp1_kp2 = (el_LV + pro_LV + kp1_LV + kp2_LV)).M();
        MissMass_el = ((Beam_LV + Target_LV) - (el_LV)).M();
        MissMass_pro = ((Beam_LV + Target_LV) - (pro_LV)).M();
        MissMass_kp1 = ((Beam_LV + Target_LV) - (kp1_LV)).M();
        MissMass_kp2 = ((Beam_LV + Target_LV) - (kp2_LV)).M();
        MissMass_el_pro = ((Beam_LV + Target_LV) - (el_LV + pro_LV)).M();
        MissMass_el_kp1 = ((Beam_LV + Target_LV) - (el_LV + kp1_LV)).M();
        MissMass_el_kp2 = ((Beam_LV + Target_LV) - (el_LV + kp2_LV)).M();
        MissMass_pro_kp1 = ((Beam_LV + Target_LV) - (pro_LV + kp1_LV)).M();
        MissMass_pro_kp2 = ((Beam_LV + Target_LV) - (pro_LV + kp2_LV)).M();
        MissMass_kp1_kp2 = ((Beam_LV + Target_LV) - (kp1_LV + kp2_LV)).M();
        MissMass_el_pro_kp1 = ((Beam_LV + Target_LV) - (el_LV + pro_LV + kp1_LV)).M();
        MissMass_el_pro_kp2 = ((Beam_LV + Target_LV) - (el_LV + pro_LV + kp2_LV)).M();
        MissMass_el_kp1_kp2 = ((Beam_LV + Target_LV) - (el_LV + kp1_LV + kp2_LV)).M();
        MissMass_pro_kp1_kp2 = ((Beam_LV + Target_LV) - (pro_LV + kp1_LV + kp2_LV)).M();
        MissMass_el_pro_kp1_kp2 = ((Beam_LV + Target_LV) - (el_LV + pro_LV + kp1_LV + kp2_LV)).M();
        MissMass2_el_pro_kp1_kp2 = ((Beam_LV + Target_LV) - (el_LV + pro_LV + kp1_LV + kp2_LV)).M2();
        //TrigBits...
        Egamma = (Beam_LV - el_LV).E();
        Q2 = -(Beam_LV - el_LV).M2();

        if (el_theta>0.044 && el_theta<0.079){
            tree->Fill();
        }
    }
}

tree->Write();

cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
cout << "Skimmed tree saved to 'epKK_skimmed_tree.root'" << endl;
cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
