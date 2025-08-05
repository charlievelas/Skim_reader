// the purpose of GJ_calculator.C is to calculate GJ variables for each event in a root tree 


void GJ_calculator_basic(){

// To get to the Gottfried-Jackson frame, the system must first be boosted to the centre-of-mass frame and then the GJ frame
// https://halldweb.jlab.org/DocDB/0048/004829/005/coordinates.pdf

// inital interaction is 10.2 GeV photon striking stationary proton

cout << "Inital interaction is 10.2 GeV photon striking stationary proton." << endl;
cout << "Lorentz vectors (px,py,pz,E) defined in lab frame" << endl;

// define Lorentz vectors (px,py,pz,E)
ROOT::Math::PxPyPzEVector gamma_LV(0,0,10.2,10.2);
ROOT::Math::PxPyPzEVector pro_LV(0,0,0,0.938272);

cout << "gamma LV" << endl;

cout << "X: " << gamma_LV.X() << endl;
cout << "Y: " << gamma_LV.Y() << endl;
cout << "Z: " << gamma_LV.Z() << endl;
cout << "E: " << gamma_LV.E() << endl;

cout << "proton LV" << endl;

cout << "X: " << pro_LV.X() << endl;
cout << "Y: " << pro_LV.Y() << endl;
cout << "Z: " << pro_LV.Z() << endl;
cout << "E: " << pro_LV.E() << endl;


// centre of mass boost
cout << "calculate the centre of mass beta vector" << endl;
ROOT::Math::PxPyPzEVector gamma_pro_CM_LV = gamma_LV + pro_LV;

cout << gamma_pro_CM_LV.E() << endl;

ROOT::Math::Boost::XYZVector CM_beta = gamma_pro_CM_LV.BoostToCM();

cout << "centre of mass beta vector" << endl;
cout << CM_beta.X() << endl;
cout << CM_beta.Y() << endl;
cout << CM_beta.Z() << endl;

// boost into centre of mass frame
cout << "boost into centre of mass frame" << endl;

ROOT::Math::PxPyPzEVector gamma_boosted_LV = ROOT::Math::VectorUtil::boost(gamma_LV,CM_beta);

cout << "gamma boosted LV" << endl;

cout << "X: " << gamma_boosted_LV.X() << endl;
cout << "Y: " << gamma_boosted_LV.Y() << endl;
cout << "Z: " << gamma_boosted_LV.Z() << endl;
cout << "E: " << gamma_boosted_LV.E() << endl;

ROOT::Math::PxPyPzEVector pro_boosted_LV = ROOT::Math::VectorUtil::boost(pro_LV,CM_beta);

cout << "proton boosted LV" << endl;

cout << "X: " << pro_boosted_LV.X() << endl;
cout << "Y: " << pro_boosted_LV.Y() << endl;
cout << "Z: " << pro_boosted_LV.Z() << endl;
cout << "E: " << pro_boosted_LV.E() << endl;

cout << "As expected, the momenta of the particles in the COM frame are equal and opposite." << endl;

cout << "Now two kaons will be introduced into the frame" << endl;
ROOT::Math::PxPyPzEVector k1_LV(2,1,3,3.77); // E = sqrt(p_mag^2 + m_k^2)
ROOT::Math::PxPyPzEVector k2_LV(-1,-2,3,3.77);

cout << "lab frame k1 LV" << endl;

cout << "X: " << k1_LV.X() << endl;
cout << "Y: " << k1_LV.Y() << endl;
cout << "Z: " << k1_LV.Z() << endl;
cout << "E: " << k1_LV.E() << endl;

cout << "lab frame k2 LV" << endl;

cout << "X: " << k2_LV.X() << endl;
cout << "Y: " << k2_LV.Y() << endl;
cout << "Z: " << k2_LV.Z() << endl;
cout << "E: " << k2_LV.E() << endl;

cout << "k1 and k2 are the decay products of M, the CM frame of M is calculated";
ROOT::Math::PxPyPzEVector M_LV = k1_LV + k2_LV;
ROOT::Math::Boost::XYZVector M_CM_beta = M_LV.BoostToCM();

cout << "centre of mass beta vector" << endl;
cout << M_CM_beta.X() << endl;
cout << M_CM_beta.Y() << endl;
cout << M_CM_beta.Z() << endl;

cout << "boost k1 and k2 into M centre of mass frame" << endl;

ROOT::Math::PxPyPzEVector k1_boosted_LV = ROOT::Math::VectorUtil::boost(k1_LV,M_CM_beta);

cout << "k1 boosted LV" << endl;

cout << "X: " << k1_boosted_LV.X() << endl;
cout << "Y: " << k1_boosted_LV.Y() << endl;
cout << "Z: " << k1_boosted_LV.Z() << endl;
cout << "E: " << k1_boosted_LV.E() << endl;

ROOT::Math::PxPyPzEVector k2_boosted_LV = ROOT::Math::VectorUtil::boost(k2_LV,M_CM_beta);

cout << "k2 booseted LV" << endl;

cout << "X: " << k2_boosted_LV.X() << endl;
cout << "Y: " << k2_boosted_LV.Y() << endl;
cout << "Z: " << k2_boosted_LV.Z() << endl;
cout << "E: " << k2_boosted_LV.E() << endl;

cout << "As expected, the momenta of the particles in the M CM frame are equal and opposite." << endl;



ROOT::Math::PxPyPzEVector pro_scat_LV(-0.5,0.5,1,1.54);

cout << "pro_scat booseted LV" << endl;
cout << "X: " << pro_scat_LV.X() << endl;
cout << "Y: " << pro_scat_LV.Y() << endl;
cout << "Z: " << pro_scat_LV.Z() << endl;
cout << "E: " << pro_scat_LV.E() << endl;



cout << "The GJ jackson variables can be obtained by first boosting all particles into M CM frame" << endl; 
	
ROOT::Math::PxPyPzEVector gamma_boosted_M_CM_LV = ROOT::Math::VectorUtil::boost(gamma_LV,M_CM_beta);

cout << "gamma boosted LV" << endl;

cout << "X: " << gamma_boosted_M_CM_LV.X() << endl;
cout << "Y: " << gamma_boosted_M_CM_LV.Y() << endl;
cout << "Z: " << gamma_boosted_M_CM_LV.Z() << endl;
cout << "E: " << gamma_boosted_M_CM_LV.E() << endl;

ROOT::Math::PxPyPzEVector pro_scat_boosted_M_CM_LV = ROOT::Math::VectorUtil::boost(pro_scat_LV,M_CM_beta);

cout << "pro_scat booseted LV" << endl;

cout << "X: " << pro_scat_boosted_M_CM_LV.X() << endl;
cout << "Y: " << pro_scat_boosted_M_CM_LV.Y() << endl;
cout << "Z: " << pro_scat_boosted_M_CM_LV.Z() << endl;
cout << "E: " << pro_scat_boosted_M_CM_LV.E() << endl;	
	
	
cout << "Then, define " << endl;
cout <<	"the z axis as the gamma direction" << endl;
cout << "the y axis as the baryon and gamma cross product and setting the x axis as" << endl;
cout << "the x axis as the y axis and x axis cross product." << endl;
cout << "boost gamma and scattered proton into M CM frame." << endl;


ROOT::Math::XYZVector zAxis = gamma_boosted_M_CM_LV.Vect().Unit();
ROOT::Math::XYZVector yAxis = pro_scat_boosted_M_CM_LV.Vect().Cross(gamma_boosted_M_CM_LV.Vect()).Unit();
ROOT::Math::XYZVector xAxis = yAxis.Cross(zAxis).Unit();


// Define a new vector, k1 in the GJ frame
cout << "Define a new vector, k1 in the GJ frame" << endl;

ROOT::Math::DisplacementVector3D< ROOT::Math::Cartesian3D< Double_t >, ROOT::Math::DefaultCoordinateSystemTag > k1_GJ(k1_boosted_LV.Vect().Dot(xAxis),k1_boosted_LV.Vect().Dot(yAxis),k1_boosted_LV.Vect().Dot(zAxis));

cout << "k1 in the GJ frame" << endl;

cout << "X: " << k1_GJ.X() << endl;
cout << "Y: " << k1_GJ.Y() << endl;
cout << "Z: " << k1_GJ.Z() << endl;


cout << "the GJ angles are" << endl;

double costh = TMath::Cos(k1_GJ.Theta());
double phi = k1_GJ.Phi();

cout << "phi: " << phi << endl;
cout << "cosTh: " << costh << endl;


}





