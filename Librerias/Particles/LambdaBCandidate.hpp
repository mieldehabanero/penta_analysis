//
//  LambdaBCandidate.hpp
//  
//
//  Created by Ricardo Zamora on 1/5/18.
//

#ifndef LambdaBCandidate_hpp
#define LambdaBCandidate_hpp

#include "JPsiCandidate.hpp"
#include "LambdaCandidate.hpp"
#include "LambdaBCandidate.hpp"
#include "../constantes.h"

class LambdaBCandidate: public ParticleCandidate {
public:
	LambdaBCandidate(JPsiCandidate *jpsi_c, LambdaCandidate *lambda_c);
	
	void setProbability(float prob);
	float getProbability();
	
private:
	JPsiCandidate jpsi;
	LambdaCandidate lambda;
	float probability;
};

#endif /* LambdaBCandidate_hpp */
