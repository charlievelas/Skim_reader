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

TString in_file_name = HIPO;
TChain chain("hipo");
chain.Add(in_file_name.Data());
auto files=chain.GetListOfFiles();
string outFile_name = "epK_skimmed_tree.root";
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
float kp_px;
float kp_py;
float kp_pz;
float kp_pMag;
float kp_vx;
float kp_vy;
float kp_vz;
float kp_vt;
float kp_E;
float kp_theta;
float kp_phi;
float kp_M;
float kp_beta;
float kp_PID;
float kp_chi2PID;
float kp_status;
float kp_region;
float InvMass_el_pro;
float InvMass_el_kp;
float InvMass_pro_kp;
float InvMass_el_pro_kp;
float MissMass_el;
float MissMass_pro;
float MissMass_kp;
float MissMass_el_pro;
float MissMass_el_kp;
float MissMass_pro_kp;
float MissMass_el_pro_kp;
float MissMass2_el_pro_kp;
float TrigBits;
float GJcosTheta;
float GJphi;
float GJpolPhi;

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
tree->Branch("kp_px",&kp_px);
tree->Branch("kp_py",&kp_py);
tree->Branch("kp_pz",&kp_pz);
tree->Branch("kp_pMag",&kp_pMag);
tree->Branch("kp_vx",&kp_vx);
tree->Branch("kp_vy",&kp_vy);
tree->Branch("kp_vz",&kp_vz);
tree->Branch("kp_vt",&kp_vt);
tree->Branch("kp_E",&kp_E);
tree->Branch("kp_theta",&kp_theta);
tree->Branch("kp_phi",&kp_phi);
tree->Branch("kp_M",&kp_M);
tree->Branch("kp_beta",&kp_beta);
tree->Branch("kp_PID",&kp_PID);
tree->Branch("kp_chi2PID",&kp_chi2PID);
tree->Branch("kp_status",&kp_status);
tree->Branch("kp_region",&kp_region);
tree->Branch("InvMass_el_pro",&InvMass_el_pro);
tree->Branch("InvMass_el_kp",&InvMass_el_kp);
tree->Branch("InvMass_pro_kp",&InvMass_pro_kp);
tree->Branch("InvMass_el_pro_kp",&InvMass_el_pro_kp);
tree->Branch("MissMass_el",&MissMass_el);
tree->Branch("MissMass_pro",&MissMass_pro);
tree->Branch("MissMass_kp",&MissMass_kp);
tree->Branch("MissMass_el_pro",&MissMass_el_pro);
tree->Branch("MissMass_el_kp",&MissMass_el_kp);
tree->Branch("MissMass_pro_kp",&MissMass_pro_kp);
tree->Branch("MissMass_el_pro_kp",&MissMass_el_pro_kp);
tree->Branch("MissMass2_el_pro_kp",&MissMass2_el_pro_kp);
tree->Branch("TrigBits",&TrigBits);
tree->Branch("GJcosTheta",&GJcosTheta);
tree->Branch("GJphi",&GJphi);
tree->Branch("GJpolPhi",&GJpolPhi);

TLorentzVector el_LV;
TLorentzVector pro_LV;
TLorentzVector kp_LV;

for(Int_t i=0;i<files->GetEntries();i++){

    clas12reader c12(files->At(i)->GetTitle());
    c12.addExactPid(11,1);
    c12.addExactPid(2212,1);
    c12.addExactPid(321,1);
    c12.addZeroOfRestPid();


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

        // Event branches
        InvMass_el_pro = (el_LV + pro_LV)).M();
        InvMass_el_kp = (el_LV + kp_LV)).M();
        InvMass_pro_kp = (pro_LV + kp_LV)).M();
        InvMass_el_pro_kp = (el_LV + pro_LV + kp_LV)).M();
        MissMass_el = ((Beam_LV + Target_LV) - (el_LV)).M();
        MissMass_pro = ((Beam_LV + Target_LV) - (pro_LV)).M();
        MissMass_kp = ((Beam_LV + Target_LV) - (kp_LV)).M();
        MissMass_el_pro = ((Beam_LV + Target_LV) - (el_LV + pro_LV)).M();
        MissMass_el_kp = ((Beam_LV + Target_LV) - (el_LV + kp_LV)).M();
        MissMass_pro_kp = ((Beam_LV + Target_LV) - (pro_LV + kp_LV)).M();
        MissMass_el_pro_kp = ((Beam_LV + Target_LV) - (el_LV + pro_LV + kp_LV)).M();
        MissMass2_el_pro_kp = ((Beam_LV + Target_LV) - (el_LV + pro_LV + kp_LV)).M2();
        //TrigBits...
        //GJcosTheta...
        //GJphi...
        //GJpolPhi...

        if (el_px<1 && el_py<1 && el_pz<5){
            tree->Fill();
        }
    }
}

tree->Write();

cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
cout << "Skimmed tree saved to 'epK_skimmed_tree.root'" << endl;
cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
