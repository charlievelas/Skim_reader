// the purpose of GJ_calculator_singleEvent.C is to calculate GJ variables for each event in a root tree 


/////////////////// ALL THE CALCULATION NEEDS TO GO IN A LOOP, THE TREE NEEDS TO BE READ AND THE ANGLES SAVED TO A NEW TREE, ALSO THE LORETNZ VECTORS NEED TO BE DEFINED


void GJ_calculator_singleEvent(){

// Define momentum and energy
double el_px=0.1;
double el_py=0.1;
double el_pz=7;
double el_E=7;
double pro_px=0.5;
double pro_py=-0.5;
double pro_pz=1;
double pro_E=1.22;
double p1_px=2;
double p1_py=1;
double p1_pz=3;
double p1_E=3.77;
double p2_px=-1;
double p2_py=-2;
double p2_pz=3;
double p2_E=3.77;


//// Define beam lorentz vector
ROOT::Math::PxPyPzEVector beam_LV(0,0,10.2,10.2); 

//// Define input particle Lorentz vectors
ROOT::Math::PxPyPzEVector el_LV(el_px,el_py,el_pz,el_E);
ROOT::Math::PxPyPzEVector pro_LV(pro_px,pro_py,pro_pz,pro_E);
ROOT::Math::PxPyPzEVector p1_LV(p1_px,p1_py,p1_pz,p1_E);
ROOT::Math::PxPyPzEVector p2_LV(p2_px,p2_py,p2_pz,p2_E);


//// Perform boosts and obtain angles

// Define LV of meson
ROOT::Math::PxPyPzEVector M_LV = p1_LV + p2_LV;

// Define meson CM beta
ROOT::Math::Boost::XYZVector M_CM_beta = M_LV.BoostToCM();

// Boost p1 into CM frame
ROOT::Math::PxPyPzEVector p1_boosted_LV = ROOT::Math::VectorUtil::boost(p1_LV,M_CM_beta);

// Define gamma LV
ROOT::Math::PxPyPzEVector gamma_LV;
gamma_LV = beam_LV - el_LV;

// Boost scattered gamma into CM frame
ROOT::Math::PxPyPzEVector gamma_boosted_M_CM_LV = ROOT::Math::VectorUtil::boost(gamma_LV,M_CM_beta);

// Boost scattered proton into CM frame
ROOT::Math::PxPyPzEVector pro_scat_boosted_M_CM_LV = ROOT::Math::VectorUtil::boost(pro_LV,M_CM_beta);

// Define z,y and x axis in Gottfried-Jackson frame
ROOT::Math::XYZVector zAxis = gamma_boosted_M_CM_LV.Vect().Unit();
ROOT::Math::XYZVector yAxis = pro_scat_boosted_M_CM_LV.Vect().Cross(gamma_boosted_M_CM_LV.Vect()).Unit();
ROOT::Math::XYZVector xAxis = yAxis.Cross(zAxis).Unit();

// Define a p1 in the GJ frame 
ROOT::Math::DisplacementVector3D< ROOT::Math::Cartesian3D< Double_t >, ROOT::Math::DefaultCoordinateSystemTag > p1_GJ(p1_boosted_LV.Vect().Dot(xAxis),p1_boosted_LV.Vect().Dot(yAxis),p1_boosted_LV.Vect().Dot(zAxis));

// Calculate Gottfried-Jackson angles
double costh = TMath::Cos(p1_GJ.Theta());
double phi = p1_GJ.Phi();

cout << "cosTh=" << costh << " and phi=" << phi << endl;

}





