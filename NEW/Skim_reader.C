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
TString in_file_name = "file.root";
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

float el1_Px;
float el1_Py;
float el1_Pz;
float el1_PID;
float el1_beta;
float el1_chi2PID;
float el1_status;
float el1_region;
float el1_E;
float el1_Th;
float MissMass_el1;
float MissMass2_el1;
float MissEnergy_el1;
TLorentzVector el1_LV; // No associated branch
float el2_Px;
float el2_Py;
float el2_Pz;
float el2_PID;
float el2_beta;
float el2_chi2PID;
float el2_status;
float el2_region;
float el2_E;
float el2_Th;
float MissMass_el2;
float MissMass2_el2;
float MissEnergy_el2;
TLorentzVector el2_LV; // No associated branch
float pro_Px;
float pro_Py;
float pro_Pz;
float pro_PID;
float pro_beta;
float pro_chi2PID;
float pro_status;
float pro_region;
float pro_E;
float pro_Th;
float MissMass_pro;
float MissMass2_pro;
float MissEnergy_pro;
TLorentzVector pro_LV; // No associated branch
float MissMass;
float MissMass2;
float InvMass_el1_el2;
float InvMass_el1_pro;
float InvMass_el2_pro;
float InvMass_el1_el2_pro;
float MissTh;
float MissE;
float Q2;
float Egamma;

tree->Branch("el1_Px",&el1_Px);
tree->Branch("el1_Py",&el1_Py);
tree->Branch("el1_Pz",&el1_Pz);
tree->Branch("el1_PID",&el1_PID);
tree->Branch("el1_beta",&el1_beta);
tree->Branch("el1_chi2PID",&el1_chi2PID);
tree->Branch("el1_status",&el1_status);
tree->Branch("el1_region",&el1_region);
tree->Branch("el1_E",&el1_E);
tree->Branch("el1_Th",&el1_Th);
tree->Branch("MissMass_el1",&MissMass_el1);
tree->Branch("MissMass2_el1",&MissMass2_el1);
tree->Branch("MissEnergy_el1",&MissEnergy_el1);
tree->Branch("el2_Px",&el2_Px);
tree->Branch("el2_Py",&el2_Py);
tree->Branch("el2_Pz",&el2_Pz);
tree->Branch("el2_PID",&el2_PID);
tree->Branch("el2_beta",&el2_beta);
tree->Branch("el2_chi2PID",&el2_chi2PID);
tree->Branch("el2_status",&el2_status);
tree->Branch("el2_region",&el2_region);
tree->Branch("el2_E",&el2_E);
tree->Branch("el2_Th",&el2_Th);
tree->Branch("MissMass_el2",&MissMass_el2);
tree->Branch("MissMass2_el2",&MissMass2_el2);
tree->Branch("MissEnergy_el2",&MissEnergy_el2);
tree->Branch("pro_Px",&pro_Px);
tree->Branch("pro_Py",&pro_Py);
tree->Branch("pro_Pz",&pro_Pz);
tree->Branch("pro_PID",&pro_PID);
tree->Branch("pro_beta",&pro_beta);
tree->Branch("pro_chi2PID",&pro_chi2PID);
tree->Branch("pro_status",&pro_status);
tree->Branch("pro_region",&pro_region);
tree->Branch("pro_E",&pro_E);
tree->Branch("pro_Th",&pro_Th);
tree->Branch("MissMass_pro",&MissMass_pro);
tree->Branch("MissMass2_pro",&MissMass2_pro);
tree->Branch("MissEnergy_pro",&MissEnergy_pro);
tree->Branch("MissMass",&MissMass);
tree->Branch("MissMass2",&MissMass2);
tree->Branch("InvMass_el1_el2",&InvMass_el1_el2);
tree->Branch("InvMass_el1_pro",&InvMass_el1_pro);
tree->Branch("InvMass_el2_pro",&InvMass_el2_pro);
tree->Branch("InvMass_el1_el2_pro",&InvMass_el1_el2_pro);
tree->Branch("MissTh",&MissTh);
tree->Branch("MissE",&MissE);
tree->Branch("Q2",&Q2);
tree->Branch("Egamma",&Egamma);

for(Int_t i=0;i<files->GetEntries();i++){

    clas12reader c12(files->At(i)->GetTitle());

    c12.addExactPid(11,2);
    c12.addExactPid(2212,1);
    c12.addZeroOfRestPid();

    Int_t eventnumber=0;
    while(c12.next()==true){
        eventnumber++;
        int evn_el_count=0;
        Int_t k = 0;
        auto particle = c12.getDetParticles();
        Int_t numofpart = particle.size();
        for(Int_t k=0;k<numofpart;k++){
            // Beam-electron(scattered) kinematics
            if (particle[k]->par()->getPid()==11 && evn_el_count==0){
              elScat_LV.SetXYZM(particle[k]->par()->getPx(),particle[k]->par()->getPy(),particle[k]->par()->getPz(),0.000511);
              evn_el_count++;
            }
            if (particle[k]->par()->getPid()==11){
              el1_Px=particle[k]->par()->getPx();
              el1_Py=particle[k]->par()->getPy();
              el1_Pz=particle[k]->par()->getPz();
              el1_PID=particle[k]->par()->getPid();
              el1_beta=particle[k]->par()->getBeta();
              el1_chi2PID=particle[k]->par()->getChi2Pid();
              el1_status=particle[k]->par()->getStatus();
              int region_abs = abs(particle[k]->par()->getStatus());
	      string region_abs_str = std::to_string(region_abs);
	      region_abs_str.replace(1, 3, 3, '0');
              el1_region=std::stoi(region_abs_str);
              float el1_M=PDG_info->GetParticle(particle[k]->par()->getPid())->Mass();
              el1_LV.SetXYZM(el1_Px,el1_Py,el1_Pz,el1_M);
              el1_E=el1_LV.E();
              el1_Th=el1_LV.Theta();
            }
            if (particle[k]->par()->getPid()==11){
              el2_Px=particle[k]->par()->getPx();
              el2_Py=particle[k]->par()->getPy();
              el2_Pz=particle[k]->par()->getPz();
              el2_PID=particle[k]->par()->getPid();
              el2_beta=particle[k]->par()->getBeta();
              el2_chi2PID=particle[k]->par()->getChi2Pid();
              el2_status=particle[k]->par()->getStatus();
              int region_abs = abs(particle[k]->par()->getStatus());
	      string region_abs_str = std::to_string(region_abs);
	      region_abs_str.replace(1, 3, 3, '0');
              el2_region=std::stoi(region_abs_str);
              float el2_M=PDG_info->GetParticle(particle[k]->par()->getPid())->Mass();
              el2_LV.SetXYZM(el2_Px,el2_Py,el2_Pz,el2_M);
              el2_E=el2_LV.E();
              el2_Th=el2_LV.Theta();
            }
            if (particle[k]->par()->getPid()==2212){
              pro_Px=particle[k]->par()->getPx();
              pro_Py=particle[k]->par()->getPy();
              pro_Pz=particle[k]->par()->getPz();
              pro_PID=particle[k]->par()->getPid();
              pro_beta=particle[k]->par()->getBeta();
              pro_chi2PID=particle[k]->par()->getChi2Pid();
              pro_status=particle[k]->par()->getStatus();
              int region_abs = abs(particle[k]->par()->getStatus());
	      string region_abs_str = std::to_string(region_abs);
	      region_abs_str.replace(1, 3, 3, '0');
              pro_region=std::stoi(region_abs_str);
              float pro_M=PDG_info->GetParticle(particle[k]->par()->getPid())->Mass();
              pro_LV.SetXYZM(pro_Px,pro_Py,pro_Pz,pro_M);
              pro_E=pro_LV.E();
              pro_Th=pro_LV.Theta();
            }
        }

        TLorentzVector miss_LV_el1;
        float missE_el1;
        miss_LV_el1 = Beam_LV + Target_LV - el2_LV - pro_LV;
        MissMass_el1 = miss_LV_el1.M();
        MissMass2_el1 = miss_LV_el1.M2();
        missE_el1 = Beam_LV.E() + Target_LV.E() - el2_LV.E() - pro_LV.E();
        MissEnergy_el1 = missE_el1;
        TLorentzVector miss_LV_el2;
        float missE_el2;
        miss_LV_el2 = Beam_LV + Target_LV - el1_LV - pro_LV;
        MissMass_el2 = miss_LV_el2.M();
        MissMass2_el2 = miss_LV_el2.M2();
        missE_el2 = Beam_LV.E() + Target_LV.E() - el1_LV.E() - pro_LV.E();
        MissEnergy_el2 = missE_el2;
        TLorentzVector miss_LV_pro;
        float missE_pro;
        miss_LV_pro = Beam_LV + Target_LV - el1_LV - el2_LV;
        MissMass_pro = miss_LV_pro.M();
        MissMass2_pro = miss_LV_pro.M2();
        missE_pro = Beam_LV.E() + Target_LV.E() - el1_LV.E() - el2_LV.E();
        MissEnergy_pro = missE_pro;
        TLorentzVector missAll_LV;
        missAll_LV = Beam_LV + Target_LV - el1_LV - el2_LV - pro_LV;
        MissMass = missAll_LV.M();
        MissMass2 = missAll_LV.M2();
        InvMass_el1_el2 = (el1_LV+el2_LV).M();
        InvMass_el1_pro = (el1_LV+pro_LV).M();
        InvMass_el2_pro = (el2_LV+pro_LV).M();
        InvMass_el1_el2_pro = (el1_LV+el2_LV+pro_LV).M();
        // (somewhat) miscellaneous
        MissTh = missAll_LV.Theta();
        MissE = Beam_LV.E() + Target_LV.E() - el1_LV.E() - el2_LV.E() - pro_LV.E();
        // Beam-electron(scattered) kinematics
        TLorentzVector gamma;
        gamma = Beam_LV - elScat_LV;
        Q2 = -gamma.M2();
        Egamma = gamma.E();
        evn_el_count=0;

        tree->Fill();

    }
}
tree->Write();

cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
cout << "Skimmed tree saved to 'skim_tree.root'" << endl;
cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

}
