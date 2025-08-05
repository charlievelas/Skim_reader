
void pol_calculator_singleEvent(){

//// Initialise Lorentz vectors
// Define beam lorentz vector
ROOT::Math::PxPyPzEVector beam_LV(0,0,10.2,10.2);
ROOT::Math::PxPyPzEVector target_LV(0,0,0,0.938272);
ROOT::Math::PxPyPzEVector el_LV(-0.1,0.1,5,5);
ROOT::Math::PxPyPzEVector p1_LV(-2,2,3,3.77);
ROOT::Math::PxPyPzEVector p2_LV(-2,1,3,3.77);

// Define gamma LV
ROOT::Math::PxPyPzEVector gamma_LV;
gamma_LV = beam_LV - el_LV;

// Obtain centre of mass beta
ROOT::Math::PxPyPzEVector CM_LV = beam_LV + target_LV;
ROOT::Math::Boost::XYZVector CM_beta = CM_LV.BoostToCM();

// Boost beam electron into CM frame
ROOT::Math::PxPyPzEVector beam_boosted_LV = ROOT::Math::VectorUtil::boost(beam_LV,CM_beta);

// Boost meson into CM frame
ROOT::Math::PxPyPzEVector M_LV = p1_LV + p2_LV;
ROOT::Math::PxPyPzEVector M_boosted_LV = ROOT::Math::VectorUtil::boost(M_LV,CM_beta);

// Boost scattered gamma into CM frame
ROOT::Math::PxPyPzEVector gamma_boosted_M_CM_LV = ROOT::Math::VectorUtil::boost(gamma_LV,CM_beta);

// Define z,y and x axes
ROOT::Math::XYZVector zAxis = gamma_boosted_M_CM_LV.Vect().Unit();
ROOT::Math::XYZVector yAxis = gamma_boosted_M_CM_LV.Vect().Cross(beam_boosted_LV.Vect()).Unit();
ROOT::Math::XYZVector xAxis = yAxis.Cross(zAxis).Unit();

// Define angles
ROOT::Math::DisplacementVector3D< ROOT::Math::Cartesian3D< Double_t >, ROOT::Math::DefaultCoordinateSystemTag > elHadAngles(M_boosted_LV.Vect().Dot(xAxis),M_boosted_LV.Vect().Dot(yAxis),M_boosted_LV.Vect().Dot(zAxis));

// Define elHadPhi
double elHadPhi = elHadAngles.Phi();

cout << elHadPhi << endl;


}