//
//  LambdaCandidate.cpp
//  
//
//  Created by Ricardo Zamora on 1/5/18.
//

#include "LambdaCandidate.hpp"

LambdaCandidate::LambdaCandidate(ProtonCandidate *proton_c, PionCandidate *pion_c):proton(*proton_c), pion(*pion_c), ParticleCandidate(proton_c->getFourMomentum() + pion_c->getFourMomentum(), LAMBDA_0_MASS){
}

void LambdaCandidate::setProbability(float prob){
	probability = prob;
}

float LambdaCandidate::getProbability(){
	return probability;
}

void LambdaCandidate::setChi2(float chi){
	chi2 = chi;
}

float LambdaCandidate::getChi2(){
	return chi2;
}

void LambdaCandidate::setDecayDistance(float x, float y){
	dx = x;
	dy = y;
	d_xy = sqrt(pow(x, 2) + pow(y, 2));
	
	std::vector<float> p_vtx = four_momentum.getMomentumVtx();
	
	float p_xy_magnitud = sqrt(pow(p_vtx[0], 2) + pow(p_vtx[1], 2));
	float d_xy_magnitude = sqrt(pow(dx, 2) + pow(dy, 2));
	float dot_product = p_vtx[0]*dx + p_vtx[1]*dy;
	
	cos_alpha = dot_product/(d_xy_magnitude * p_xy_magnitud);
}

float LambdaCandidate::getDecayDistance(){
	return d_xy;
}

void LambdaCandidate::setDecayDistanceError(float ex_1, float ex_2, float ey_1, float ey_2){
	ex1 = ex_1;
	ex2 = ex_2;
	ey1 = ey_1;
	ey2 = ey_2;
	
	float sigma = sqrt(pow(dx, 2) * (pow(ex1, 2) + pow(ex2, 2))
					   + pow(dy, 2) * (pow(ey1, 2) + pow(ey2, 2)));
	sigma = sigma/d_xy;
}

float LambdaCandidate::getDecayDistanceSigma(){
	return sigma;
}

float LambdaCandidate::getCosAlpha(){
	return cos_alpha;
}

float LambdaCandidate::getD0Sigma(){
	return d_xy/sigma;
}
