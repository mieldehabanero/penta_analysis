//
//  JPsiCuts.cpp
//  
//
//  Created by Ricardo Zamora on 1/5/18.
//

#include "JPsiCuts.hpp"

JPsiCuts::JPsiCuts(){
//	cuts.push_back(JPsiCuts::pt_muon);
//	cuts.push_back(&JPsiCuts::prob);
//	cuts.push_back(&JPsiCuts::lxy);
//	cuts.push_back(&JPsiCuts::pointing_angle);
//	cuts.push_back(&JPsiCuts::pt_jpsi);
//	cuts.push_back(&JPsiCuts::mass);
	
//	cuts = {&JPsiCuts::pt_muon, &JPsiCuts::prob, &JPsiCuts::lxy, &JPsiCuts::pointing_angle, &JPsiCuts::pt_jpsi, &JPsiCuts::mass}
};

int JPsiCuts::applyCuts(JPsiCandidate *jpsi){
	
//	typedef long (AClass::*pmemfunc_t)(int, float);
//	typedef std::vector<pmemfunc_t> memfuncvec_t;
//	int val;
//	for(auto& cut : cuts){
//		val = (*cut)(jpsi);
//		if (val) return 0;
//	}
//	return 1;
	
	if (this->pt_muon(jpsi) && this->prob(jpsi) && this->lxy(jpsi) && this->pointing_angle(jpsi) && this->pt_jpsi(jpsi) && this->mass(jpsi)) {
		return 1;
	}
	return 0;
}


//Checa si el pt de ambos µ esta en el rango requerido, sí = 1, no = 0.
int JPsiCuts::pt_muon(JPsiCandidate *jpsi) {
	
	//Se calcula si los pts están dentro del rango (pt_µ > 4GeV)
	if (jpsi->getMuon1().getTransverseMomentum() > MUON_PT_CUT && jpsi->getMuon2().getTransverseMomentum() > MUON_PT_CUT){
		return 1;
	}
	return 0;
}

//Checa si la probabilidad de que µ+µ- vengan del mismo vértice, sí = 1, no = 0.
int JPsiCuts::prob(JPsiCandidate *jpsi) {
	
	//Se calcula si la probabilidad es mayor al cuttoff
	if (jpsi->getProbability() > J_PSI_PROB_CUT){
		return 1;
	}
	return 0;
}

int JPsiCuts::lxy(JPsiCandidate *jpsi) {
	if (jpsi->getDecayDistance()/jpsi->getDecayDistanceSigma() > J_PSI_LXY_S_CUT){
		return 1;
	}
	return 0;
}

int JPsiCuts::pointing_angle(JPsiCandidate *jpsi) {
	if (jpsi->getCosAlpha() > J_PSI_COS_ALPHA){
		return 1;
	}
	return 0;
}


//Checa si el pt del J/Psi esta en el rango requerido, sí = 1, no = 0.
int JPsiCuts::pt_jpsi(JPsiCandidate *jpsi) {
	
	//Se calcula si los pts están dentro del rango (pt_µ > 4GeV, y pt_µ+µ- > 8GeV)
	if (jpsi->getTransverseMomentum() > J_PSI_PT_CUT){
		return 1;
	}
	return 0;
}

//Checa si la masa del J/Psi esta en el rango requerido, sí = 1, no = 0.
//masa esta en MeV
int JPsiCuts::mass(JPsiCandidate *jpsi) {
	float valorInferior = (J_PSI_MASS - J_PSI_MASS_CUT);
	float valorSuperior = (J_PSI_MASS + J_PSI_MASS_CUT);
	
	if (valorInferior < jpsi->getInvariantMass() && jpsi->getInvariantMass() < valorSuperior){
		return 1;
	}
	return 0;
}
