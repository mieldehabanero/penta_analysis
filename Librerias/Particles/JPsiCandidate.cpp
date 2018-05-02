
//
//  JPsiCandidate.cpp
//  
//
//  Created by Ricardo Zamora on 1/5/18.
//

#include "JPsiCandidate.hpp"

JPsiCandidate::JPsiCandidate(MuonCandidate *muon1, MuonCandidate *muon2):muon_1(*muon1), muon_2(*muon2), ParticleCandidate(muon1->getFourMomentum() + muon2->getFourMomentum(), J_PSI_MASS){
}

void JPsiCandidate::setProbability(float prob){
	probability = prob;
}

float JPsiCandidate::getProbability(){
	return probability;
}

void JPsiCandidate::setDecayDistance(float x, float y){
	dx = x;
	dy = y;
	d_xy = sqrt(pow(x, 2) + pow(y, 2));
	
	std::vector<float> p_vtx = four_momentum.getMomentumVtx();
	
	float p_xy_magnitud = sqrt(pow(p_vtx[0], 2) + pow(p_vtx[1], 2));
	float d_xy_magnitude = sqrt(pow(dx, 2) + pow(dy, 2));
	float dot_product = p_vtx[0]*dx + p_vtx[1]*dy;
	
	cos_alpha = dot_product/(d_xy_magnitude * p_xy_magnitud);
}

float JPsiCandidate::getDecayDistance(){
	return d_xy;
}

void JPsiCandidate::setDecayDistanceError(float ex_1, float ex_2, float ey_1, float ey_2){
	ex1 = ex_1;
	ex2 = ex_2;
	ey1 = ey_1;
	ey2 = ey_2;
	
	float sigma = sqrt(pow(dx, 2) * (pow(ex1, 2) + pow(ex2, 2))
					   + pow(dy, 2) * (pow(ey1, 2) + pow(ey2, 2)));
	sigma = sigma/d_xy;
}

float JPsiCandidate::getDecayDistanceSigma(){
	return sigma;
}

float JPsiCandidate::getCosAlpha(){
	return cos_alpha;
}

MuonCandidate JPsiCandidate::getMuon1(){
	return muon_1;
}

MuonCandidate JPsiCandidate::getMuon2(){
	return muon_2;
}
