// the purpose of pol_calculator.C is to calculate the degree of linear polarisation, P, and the angle between the electron scattering plane and the hadron production plane, elHadPhi, also known as the polarisation angle.
// elHadPhi is the angle given in Fig. 4 in https://arxiv.org/pdf/1310.7498


void pol_calculator(string filename, string el_input, string p1_input, string p2_input){

// Open root file, open tree
TFile fFile(filename.c_str());
TTree *fTree = (TTree*)fFile.Get(fFile.GetListOfKeys()->At(0)->GetName());

//// Initialise variables and set branches
float el_px;
float el_py;
float el_pz;
float el_E;
float p1_px;
float p1_py;
float p1_pz;
float p1_E;
float p2_px;
float p2_py;
float p2_pz;
float p2_E;
string el_px_str = el_input + "_px";
fTree->SetBranchAddress(el_px_str.c_str(),&el_px);
string el_py_str = el_input + "_py";
fTree->SetBranchAddress(el_py_str.c_str(),&el_py);
string el_pz_str = el_input + "_pz";
fTree->SetBranchAddress(el_pz_str.c_str(),&el_pz);
string el_E_str = el_input + "_E";
fTree->SetBranchAddress(el_E_str.c_str(),&el_E);
string p1_px_str = p1_input + "_px";
fTree->SetBranchAddress(p1_px_str.c_str(),&p1_px);
string p1_py_str = p1_input + "_py";
fTree->SetBranchAddress(p1_py_str.c_str(),&p1_py);
string p1_pz_str = p1_input + "_pz";
fTree->SetBranchAddress(p1_pz_str.c_str(),&p1_pz);
string p1_E_str = p1_input + "_E";
fTree->SetBranchAddress(p1_E_str.c_str(),&p1_E);
string p2_px_str = p2_input + "_px";
fTree->SetBranchAddress(p2_px_str.c_str(),&p2_px);
string p2_py_str = p2_input + "_py";
fTree->SetBranchAddress(p2_py_str.c_str(),&p2_py);
string p2_pz_str = p2_input + "_pz";
fTree->SetBranchAddress(p2_pz_str.c_str(),&p2_pz);
string p2_E_str = p2_input + "_E";
fTree->SetBranchAddress(p2_E_str.c_str(),&p2_E);


// Create a new root file and tree
string filename_new = "pol_" + filename;
TFile fFileNew(filename_new.c_str(), "RECREATE");
TTree* fTreeNew = fTree->CloneTree(0);

// Add pol branches to tree
double polP;
double polElHadPhi;
TBranch* polP_branch = fTreeNew->Branch("polP", &polP, "polP/D");
TBranch* polElHadPhi_branch = fTreeNew->Branch("polElHadPhi", &polElHadPhi, "polElHadPhi/D");


//// Initialise Lorentz vectors
// Define Q2
double Q2;

// Define beam and target lorentz vectors
ROOT::Math::PxPyPzEVector beam_LV(0,0,10.2,10.2);
ROOT::Math::PxPyPzEVector target_LV(0,0,0,0.938272);

// Define input particle lorentz vectors    
ROOT::Math::PxPyPzEVector el_LV;
ROOT::Math::PxPyPzEVector p1_LV;
ROOT::Math::PxPyPzEVector p2_LV;

// Define gamma LV
ROOT::Math::PxPyPzEVector gamma_LV;

// Obtain centre of mass LV and beta
ROOT::Math::PxPyPzEVector CM_LV;
ROOT::Math::Boost::XYZVector CM_beta;

// Define beam electron boosted into CM frame
ROOT::Math::PxPyPzEVector beam_boosted_LV;

// Define meson boosted into CM frame
ROOT::Math::PxPyPzEVector M_LV;
ROOT::Math::PxPyPzEVector M_boosted_LV;

// Boost scattered gamma into CM frame
ROOT::Math::PxPyPzEVector gamma_boosted_M_CM_LV;

// Define z,y and x axes
ROOT::Math::XYZVector zAxis;
ROOT::Math::XYZVector yAxis;
ROOT::Math::XYZVector xAxis;


//// Loop over tree
for(Int_t i=0;i<fTree->GetEntries();i++){

fTree->GetEvent(i);

// Set input particle LVs
el_LV.SetPxPyPzE(el_px,el_py,el_pz,el_E);
p1_LV.SetPxPyPzE(p1_px,p1_py,p1_pz,p1_E);
p2_LV.SetPxPyPzE(p2_px,p2_py,p2_pz,p2_E);

// Define gamma LV
gamma_LV = beam_LV - el_LV;

// Calculate polP
Q2 = -gamma_LV.M2();
polP = 1./(1+2*(1+gamma_LV.E()*gamma_LV.E()/Q2)*TMath::Tan(el_LV.Theta()/2)*TMath::Tan(el_LV.Theta()/2));

// Obtain centre of mass beta
CM_LV = beam_LV + target_LV;
CM_beta = CM_LV.BoostToCM();

// Boost beam electron into CM frame
beam_boosted_LV = ROOT::Math::VectorUtil::boost(beam_LV,CM_beta);

// Boost meson into CM frame
M_LV = p1_LV + p2_LV;
M_boosted_LV = ROOT::Math::VectorUtil::boost(M_LV,CM_beta);

// Boost scattered gamma into CM frame
gamma_boosted_M_CM_LV = ROOT::Math::VectorUtil::boost(gamma_LV,CM_beta);

// Define z,y and x axes
zAxis = gamma_boosted_M_CM_LV.Vect().Unit();
yAxis = gamma_boosted_M_CM_LV.Vect().Cross(beam_boosted_LV.Vect()).Unit();
xAxis = yAxis.Cross(zAxis).Unit();

// Define angles
ROOT::Math::DisplacementVector3D< ROOT::Math::Cartesian3D< Double_t >, ROOT::Math::DefaultCoordinateSystemTag > elHadAngles(M_boosted_LV.Vect().Dot(xAxis),M_boosted_LV.Vect().Dot(yAxis),M_boosted_LV.Vect().Dot(zAxis));

// Define polElHadPhi
polElHadPhi = elHadAngles.Phi();

// Fill new tree
fTreeNew->Fill();

}

fTreeNew->Write("", TObject::kOverwrite);
fFile.Close();
fFileNew.Close();

}

