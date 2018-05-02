//
//  LambdaCandidate.hpp
//  
//
//  Created by Ricardo Zamora on 1/5/18.
//

#ifndef LambdaCandidate_hpp
#define LambdaCandidate_hpp

#include "ParticleCandidate.hpp"
#include "ProtonCandidate.hpp"
#include "PionCandidate.hpp"
#include "../constantes.h"

class LambdaCandidate: public ParticleCandidate {
public:
	LambdaCandidate(ProtonCandidate *proton_c, PionCandidate *pion_c);
	
	void setProbability(float prob);
	float getProbability();
	void setChi2(float chi);
	float getChi2();
	void setDecayDistance(float x, float y);
	float getDecayDistance();
	void setDecayDistanceError(float ex_1, float ex_2, float ey_1, float ey_2);
	float getDecayDistanceSigma();
	float getCosAlpha();
	float getD0Sigma();
	
private:
	ProtonCandidate proton;
	PionCandidate pion;
	float probability;
	float chi2;
	float dx;
	float dy;
	float d_xy;
	float ex1;
	float ex2;
	float ey1;
	float ey2;
	float sigma;
	float cos_alpha;
};

#endif /* LambdaCandidate_hpp */
