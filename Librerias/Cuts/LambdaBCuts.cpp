//
//  LambdaBCuts.cpp
//  
//
//  Created by Ricardo Zamora on 6/5/18.
//

#include "LambdaBCuts.hpp"

LambdaBCuts::LambdaBCuts(){
};

int LambdaBCuts::applyCuts(LambdaBCandidate *lambda_b){
	
	//	typedef long (AClass::*pmemfunc_t)(int, float);
	//	typedef std::vector<pmemfunc_t> memfuncvec_t;
	//	int val;
	//	for(auto& cut : cuts){
	//		val = (*cut)(lambda);
	//		if (val) return 0;
	//	}
	//	return 1;
	
	if (this->pt(lambda_b) && this->prob(lambda_b) && this->masa(lambda_b)) {
		return 1;
	}
	return 0;
}


//Checa si el pt del Lambda b esta en el rango requerido, sí = 1, no = 0.
int LambdaBCuts::pt(LambdaBCandidate *lambda_b) {
	//Valores en GeV
	
	//Se calcula si los pts están dentro del rango (pt_π > 0.3GeV, pt_p > 1.0GeV, y pt_pπ > 1.3GeV)
	if (lambda_b->getTransverseMomentum() > LAMBDA_B_PT_CUT){
		return 1;
	}
	return 0;
}

//Checa si la probabilidad de que µ+µ- vengan del mismo vértice, sí = 1, no = 0.
int LambdaBCuts::prob(LambdaBCandidate *lambda_b) {
	//Valores en GeV
	
	//Se calcula si la probabilidad es mayor al cuttoff
	if (lambda_b->getProbability() > LAMBDA_B_PROB_CUT){
		return 1;
	}
	return 0;
}

//Checa si la masa del Lambda b esta en el rango requerido, sí = 1, no = 0.
//masa esta en MeV
int LambdaBCuts::masa(LambdaBCandidate *lambda_b) {
	//Valores en GeV
	if (LAMBDA_B_MASS_LOWER_LIMIT < lambda_b->getInvariantMass() && lambda_b->getInvariantMass() < LAMBDA_B_MASS_UPPER_LIMIT){
		return 1;
	}
	return 0;
}
