//
//  LambdaCuts.cpp
//
//
//  Created by Ricardo Zamora on 1/5/18.
//

#include "LambdaCuts.hpp"

LambdaCuts::LambdaCuts(){
};

int LambdaCuts::applyCuts(LambdaCandidate *lambda){
	
	//	typedef long (AClass::*pmemfunc_t)(int, float);
	//	typedef std::vector<pmemfunc_t> memfuncvec_t;
	//	int val;
	//	for(auto& cut : cuts){
	//		val = (*cut)(lambda);
	//		if (val) return 0;
	//	}
	//	return 1;
	
	if (this->d0(lambda) && this->chi2(lambda) && this->lxy(lambda) && this->pt(lambda) && this->prob(lambda) && this->masa(lambda)) {
		return 1;
	}
	return 0;
}


int LambdaCuts::d0(LambdaCandidate *lambda) {
	if (lambda->getD0Sigma() > LAMBDA_0_D0_S_CUT){
		return 1;
	}
	return 0;
}

int LambdaCuts::chi2(LambdaCandidate *lambda) {
	if (lambda->getChi2() < LAMBDA_0_CHI2_CUT){
		return 1;
	}
	return 0;
}

int LambdaCuts::lxy(LambdaCandidate *lambda) {
	if (lambda->getDecayDistance()/lambda->getDecayDistanceSigma() >= LAMBDA_0_LXY_S_CUT){
		return 1;
	}
	return 0;
}

//Checa si el pt del Lambda 0 esta en el rango requerido, sí = 1, no = 0.
int LambdaCuts::pt(LambdaCandidate *lambda) {
	
	//Se calcula si los pts están dentro del rango (pt_π > 0.3GeV, pt_p > 1.0GeV, y pt_pπ > 1.3GeV)
	if (lambda->getProton().getTransverseMomentum() > PROTON_PT_CUT && lambda->getPion().getTransverseMomentum() > PION_PT_CUT && lambda->getTransverseMomentum() > LAMBDA_0_PT_CUT){
		return 1;
	}
	return 0;
}

//Checa si la probabilidad de que µ+µ- vengan del mismo vértice, sí = 1, no = 0.
int LambdaCuts::prob(LambdaCandidate *lambda) {
	//Valores en GeV
	
	//Se calcula si la probabilidad es mayor al cuttoff
	if (lambda->getProbability() > LAMBDA_0_PROB_CUT){
		return 1;
	}
	return 0;
}

//Checa si la masa del Lambda 0 esta en el rango requerido, sí = 1, no = 0.
int LambdaCuts::masa(LambdaCandidate *lambda) {
	
	float valorInferior = (LAMBDA_0_MASS - LAMBDA_0_MASS_CUT);
	float valorSuperior = (LAMBDA_0_MASS + LAMBDA_0_MASS_CUT);
	
	if (valorInferior < lambda->getInvariantMass() && lambda->getInvariantMass() < valorSuperior){
		return 1;
	}
	return 0;
}

