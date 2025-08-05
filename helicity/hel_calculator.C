// the purpose of hel_calculator.C is to calculate helicity variables for each event in a root tree 


void hel_calculator(string filename, string el_input, string pro_input, string p1_input, string p2_input){

// Open root file, open tree
TFile fFile(filename.c_str());
TTree *fTree = (TTree*)fFile.Get(fFile.GetListOfKeys()->At(0)->GetName());

//// Initialise variables and set branches
float el_px;
float el_py;
float el_pz;
float el_E;
float pro_px;
float pro_py;
float pro_pz;
float pro_E;
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
string pro_px_str = pro_input + "_px";
fTree->SetBranchAddress(pro_px_str.c_str(),&pro_px);
string pro_py_str = pro_input + "_py";
fTree->SetBranchAddress(pro_py_str.c_str(),&pro_py);
string pro_pz_str = pro_input + "_pz";
fTree->SetBranchAddress(pro_pz_str.c_str(),&pro_pz);
string pro_E_str = pro_input + "_E";
fTree->SetBranchAddress(pro_E_str.c_str(),&pro_E);
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
string filename_new = "hel_" + filename;
TFile fFileNew(filename_new.c_str(), "RECREATE");
TTree* fTreeNew = fTree->CloneTree(0);

// Add hel branches to tree
double helCosTh;
double helPhi;

TBranch* helCosTh_branch = fTreeNew->Branch("helCosTh", &helCosTh, "helCosTh/D");
TBranch* helPhi_branch = fTreeNew->Branch("helPhi", &helPhi, "helPhi/D");


//// Initialise Lorentz vectors
// Define beam lorentz vector
ROOT::Math::PxPyPzEVector beam_LV(0,0,10.2,10.2); 

// Define input particle Lorentz vectors
ROOT::Math::PxPyPzEVector el_LV(el_px,el_py,el_pz,el_E);
ROOT::Math::PxPyPzEVector pro_LV(pro_px,pro_py,pro_pz,pro_E);
ROOT::Math::PxPyPzEVector p1_LV(p1_px,p1_py,p1_pz,p1_E);
ROOT::Math::PxPyPzEVector p2_LV(p2_px,p2_py,p2_pz,p2_E);

// Define LV of meson
ROOT::Math::PxPyPzEVector M_LV;

// Define meson CM beta
ROOT::Math::Boost::XYZVector M_CM_beta;

// Boost p1 into CM frame
ROOT::Math::PxPyPzEVector p1_boosted_LV;

// Define gamma Lorentz Vector
ROOT::Math::PxPyPzEVector gamma_LV;

// Boost scattered gamma into CM frame
ROOT::Math::PxPyPzEVector gamma_boosted_M_CM_LV;

// Boost scattered proton into CM frame
ROOT::Math::PxPyPzEVector pro_scat_boosted_M_CM_LV;

// Define z,y and x axis in Gottfried-Jackson frame
ROOT::Math::XYZVector zAxis;
ROOT::Math::XYZVector yAxis;
ROOT::Math::XYZVector xAxis;



//// Loop over tree
for(Int_t i=0;i<fTree->GetEntries();i++){

fTree->GetEvent(i);

// Define input particle Lorentz vectors
el_LV.SetPxPyPzE(el_px,el_py,el_pz,el_E);
pro_LV.SetPxPyPzE(pro_px,pro_py,pro_pz,pro_E);
p1_LV.SetPxPyPzE(p1_px,p1_py,p1_pz,p1_E);
p2_LV.SetPxPyPzE(p2_px,p2_py,p2_pz,p2_E);


//// Perform boosts and obtain angles

// Define LV of meson
M_LV = p1_LV + p2_LV;

// Define meson CM beta
M_CM_beta = M_LV.BoostToCM();

// Boost p1 into CM frame
p1_boosted_LV = ROOT::Math::VectorUtil::boost(p1_LV,M_CM_beta);

// Define gamma LV
gamma_LV = beam_LV - el_LV;

// Boost scattered gamma into CM frame
gamma_boosted_M_CM_LV = ROOT::Math::VectorUtil::boost(gamma_LV,M_CM_beta);

// Boost scattered proton into CM frame
pro_scat_boosted_M_CM_LV = ROOT::Math::VectorUtil::boost(pro_LV,M_CM_beta);

// Define z,y and x axis in Gottfried-Jackson frame
zAxis = -pro_scat_boosted_M_CM_LV.Vect().Unit();
yAxis = pro_scat_boosted_M_CM_LV.Vect().Cross(gamma_boosted_M_CM_LV.Vect()).Unit();
xAxis = yAxis.Cross(zAxis).Unit();

// Define a p1 in the hel frame 
ROOT::Math::DisplacementVector3D< ROOT::Math::Cartesian3D< Double_t >, ROOT::Math::DefaultCoordinateSystemTag > p1_hel(p1_boosted_LV.Vect().Dot(xAxis),p1_boosted_LV.Vect().Dot(yAxis),p1_boosted_LV.Vect().Dot(zAxis));

// Calculate Gottfried-Jackson angles
helCosTh = TMath::Cos(p1_hel.Theta());
helPhi = p1_hel.Phi();

// Fill new tree
fTreeNew->Fill();

}

fTreeNew->Write("", TObject::kOverwrite);
fFile.Close();
fFileNew.Close();

}





