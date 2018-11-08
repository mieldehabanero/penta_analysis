//
//  KaonCuts.cpp
//  
//
//  Created by Ricardo Zamora on 6/5/18.
//

#include "KaonCuts.hpp"

KaonCuts::KaonCuts(){
};

int KaonCuts::applyCuts(KaonCandidate *kaon){
	
	//	typedef long (AClass::*pmemfunc_t)(int, float);
	//	typedef std::vector<pmemfunc_t> memfuncvec_t;
	//	int val;
	//	for(auto& cut : cuts){
	//		val = (*cut)(kaon);
	//		if (val) return 0;
	//	}
	//	return 1;
	
	if (this->masa(kaon)) {
		return 1;
	}
	return 0;
}

int KaonCuts::masa(KaonCandidate *k_short){
	float valorInferior = (K_SHORT_MASS - K_SHORT_MASS_CUT);
	float valorSuperior = (K_SHORT_MASS + K_SHORT_MASS_CUT);
	
	if (valorInferior < k_short->getInvariantMass() && k_short->getInvariantMass() < valorSuperior){
		return 1;
	}
	return 0;
}
