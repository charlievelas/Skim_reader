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

void skim_reader_slurm(TString infile, TString outfile){

TString in_file_name = infile;
TChain chain("hipo");
chain.Add(in_file_name.Data());
auto files=chain.GetListOfFiles();
TFile *tree_file = new TFile(outfile,"recreate");
TTree *tree = new TTree("tree","tree");

auto PDG_info=TDatabasePDG::Instance();
TLorentzVector Beam_LV;
Beam_LV.SetXYZM(0,0,10.2,0.000511);
TLorentzVector Target_LV;
Target_LV.SetXYZM(0,0,0,0.938272);

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
float km_px;
float km_py;
float km_pz;
float km_pMag;
float km_vx;
float km_vy;
float km_vz;
float km_vt;
float km_E;
float km_theta;
float km_phi;
float km_M;
float km_beta;
float km_PID;
float km_chi2PID;
float km_status;
float km_region;
float InvMass_el_pro;
float InvMass_el_kp;
float InvMass_el_km;
float InvMass_pro_kp;
float InvMass_pro_km;
float InvMass_kp_km;
float InvMass_el_pro_kp;
float InvMass_el_pro_km;
float InvMass_el_kp_km;
float InvMass_pro_kp_km;
float InvMass_el_pro_kp_km;
float MissMass_el;
float MissMass_pro;
float MissMass_kp;
float MissMass_km;
float MissMass_el_pro;
float MissMass_el_kp;
float MissMass_el_km;
float MissMass_pro_kp;
float MissMass_pro_km;
float MissMass_kp_km;
float MissMass_el_pro_kp;
float MissMass_el_pro_km;
float MissMass_el_kp_km;
float MissMass_pro_kp_km;
float MissMass_el_pro_kp_km;
float MissMass2_el_pro_kp_km;
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
tree->Branch("km_px",&km_px);
tree->Branch("km_py",&km_py);
tree->Branch("km_pz",&km_pz);
tree->Branch("km_pMag",&km_pMag);
tree->Branch("km_vx",&km_vx);
tree->Branch("km_vy",&km_vy);
tree->Branch("km_vz",&km_vz);
tree->Branch("km_vt",&km_vt);
tree->Branch("km_E",&km_E);
tree->Branch("km_theta",&km_theta);
tree->Branch("km_phi",&km_phi);
tree->Branch("km_M",&km_M);
tree->Branch("km_beta",&km_beta);
tree->Branch("km_PID",&km_PID);
tree->Branch("km_chi2PID",&km_chi2PID);
tree->Branch("km_status",&km_status);
tree->Branch("km_region",&km_region);
tree->Branch("InvMass_el_pro",&InvMass_el_pro);
tree->Branch("InvMass_el_kp",&InvMass_el_kp);
tree->Branch("InvMass_el_km",&InvMass_el_km);
tree->Branch("InvMass_pro_kp",&InvMass_pro_kp);
tree->Branch("InvMass_pro_km",&InvMass_pro_km);
tree->Branch("InvMass_kp_km",&InvMass_kp_km);
tree->Branch("InvMass_el_pro_kp",&InvMass_el_pro_kp);
tree->Branch("InvMass_el_pro_km",&InvMass_el_pro_km);
tree->Branch("InvMass_el_kp_km",&InvMass_el_kp_km);
tree->Branch("InvMass_pro_kp_km",&InvMass_pro_kp_km);
tree->Branch("InvMass_el_pro_kp_km",&InvMass_el_pro_kp_km);
tree->Branch("MissMass_el",&MissMass_el);
tree->Branch("MissMass_pro",&MissMass_pro);
tree->Branch("MissMass_kp",&MissMass_kp);
tree->Branch("MissMass_km",&MissMass_km);
tree->Branch("MissMass_el_pro",&MissMass_el_pro);
tree->Branch("MissMass_el_kp",&MissMass_el_kp);
tree->Branch("MissMass_el_km",&MissMass_el_km);
tree->Branch("MissMass_pro_kp",&MissMass_pro_kp);
tree->Branch("MissMass_pro_km",&MissMass_pro_km);
tree->Branch("MissMass_kp_km",&MissMass_kp_km);
tree->Branch("MissMass_el_pro_kp",&MissMass_el_pro_kp);
tree->Branch("MissMass_el_pro_km",&MissMass_el_pro_km);
tree->Branch("MissMass_el_kp_km",&MissMass_el_kp_km);
tree->Branch("MissMass_pro_kp_km",&MissMass_pro_kp_km);
tree->Branch("MissMass_el_pro_kp_km",&MissMass_el_pro_kp_km);
tree->Branch("MissMass2_el_pro_kp_km",&MissMass2_el_pro_kp_km);
tree->Branch("TrigBits",&TrigBits);
tree->Branch("Egamma",&Egamma);
tree->Branch("Q2",&Q2);
tree->Branch("Pol",&Pol);

TLorentzVector el_LV;
TLorentzVector pro_LV;
TLorentzVector kp_LV;
TLorentzVector km_LV;

for(Int_t i=0;i<files->GetEntries();i++){

    clas12reader c12(files->At(i)->GetTitle());
    c12.addExactPid(11,1);
    c12.addAtLeastPid(2212,1);
    c12.addExactPid(321,1);
    c12.addExactPid(-321,1);
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
                el_E=el_LV.E();
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
                pro_E=pro_LV.E();
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
                kp_E=kp_LV.E();
                kp_theta=kp_LV.Theta();
                kp_phi=kp_LV.Phi();
                kp_M=kp_LV.M();
                kp_beta=particle[k]->par()->getBeta();
                kp_PID=particle[k]->par()->getPid();
                kp_chi2PID=particle[k]->par()->getChi2Pid();
                kp_status=particle[k]->par()->getStatus();
                kp_region=kp_status.replace(1, 3, 3, '0');
            }
            if (particle[k]->par()->getPid()==-321){
                km_px=particle[k]->par()->getPx();
                km_py=particle[k]->par()->getPx();
                km_pz=particle[k]->par()->getPx();
                km_LV.SetXYZM(km_px,km_py,km_pz,PDG_info->GetParticle(particle[k]->par()->getPid())->Mass());
                km_pMag=km_LV.Rho();
                km_vx=particle[k]->par()->getVx();
                km_vy=particle[k]->par()->getVy();
                km_vz=particle[k]->par()->getVz();
                km_vt=particle[k]->par()->getVt();
                km_E=km_LV.E();
                km_theta=km_LV.Theta();
                km_phi=km_LV.Phi();
                km_M=km_LV.M();
                km_beta=particle[k]->par()->getBeta();
                km_PID=particle[k]->par()->getPid();
                km_chi2PID=particle[k]->par()->getChi2Pid();
                km_status=particle[k]->par()->getStatus();
                km_region=km_status.replace(1, 3, 3, '0');
            }

        // Event branches
        InvMass_el_pro = (el_LV + pro_LV).M();
        InvMass_el_kp = (el_LV + kp_LV).M();
        InvMass_el_km = (el_LV + km_LV).M();
        InvMass_pro_kp = (pro_LV + kp_LV).M();
        InvMass_pro_km = (pro_LV + km_LV).M();
        InvMass_kp_km = (kp_LV + km_LV).M();
        InvMass_el_pro_kp = (el_LV + pro_LV + kp_LV).M();
        InvMass_el_pro_km = (el_LV + pro_LV + km_LV).M();
        InvMass_el_kp_km = (el_LV + kp_LV + km_LV).M();
        InvMass_pro_kp_km = (pro_LV + kp_LV + km_LV).M();
        InvMass_el_pro_kp_km = (el_LV + pro_LV + kp_LV + km_LV).M();
        MissMass_el = ((Beam_LV + Target_LV) - (el_LV)).M();
        MissMass_pro = ((Beam_LV + Target_LV) - (pro_LV)).M();
        MissMass_kp = ((Beam_LV + Target_LV) - (kp_LV)).M();
        MissMass_km = ((Beam_LV + Target_LV) - (km_LV)).M();
        MissMass_el_pro = ((Beam_LV + Target_LV) - (el_LV + pro_LV)).M();
        MissMass_el_kp = ((Beam_LV + Target_LV) - (el_LV + kp_LV)).M();
        MissMass_el_km = ((Beam_LV + Target_LV) - (el_LV + km_LV)).M();
        MissMass_pro_kp = ((Beam_LV + Target_LV) - (pro_LV + kp_LV)).M();
        MissMass_pro_km = ((Beam_LV + Target_LV) - (pro_LV + km_LV)).M();
        MissMass_kp_km = ((Beam_LV + Target_LV) - (kp_LV + km_LV)).M();
        MissMass_el_pro_kp = ((Beam_LV + Target_LV) - (el_LV + pro_LV + kp_LV)).M();
        MissMass_el_pro_km = ((Beam_LV + Target_LV) - (el_LV + pro_LV + km_LV)).M();
        MissMass_el_kp_km = ((Beam_LV + Target_LV) - (el_LV + kp_LV + km_LV)).M();
        MissMass_pro_kp_km = ((Beam_LV + Target_LV) - (pro_LV + kp_LV + km_LV)).M();
        MissMass_el_pro_kp_km = ((Beam_LV + Target_LV) - (el_LV + pro_LV + kp_LV + km_LV)).M();
        MissMass2_el_pro_kp_km = ((Beam_LV + Target_LV) - (el_LV + pro_LV + kp_LV + km_LV)).M2();
        //TrigBits...
        Egamma = (Beam_LV - el_LV).E();
        Q2 = -(Beam_LV - el_LV).M2();

        if (el_theta<0.1 && kp_theta>0.1 && kp_theta<0.6 && kp_theta>0.1 && km_theta<0.6){
            tree->Fill();
        }
    }
}

tree->Write();

cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
cout << "Skimmed tree saved to 'epKK_skimmed_tree.root'" << endl;
cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}
