//
//  LambdaBCandidate.cpp
//  
//
//  Created by Ricardo Zamora on 1/5/18.
//

#include "LambdaBCandidate.hpp"

LambdaBCandidate::LambdaBCandidate(JPsiCandidate *jpsi_c, LambdaCandidate *lambda_c):jpsi(*jpsi_c), lambda(*lambda_c), ParticleCandidate(jpsi_c->getFourMomentum() + lambda_c->getFourMomentum(), LAMBDA_B_MASS){
}

void LambdaBCandidate::setProbability(float prob){
	probability = prob;
}

float LambdaBCandidate::getProbability(){
	return probability;
}
