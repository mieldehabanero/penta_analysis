//
//  JPsiCandidate.hpp
//  
//
//  Created by Ricardo Zamora on 1/5/18.
//

#ifndef JPsiCandidate_hpp
#define JPsiCandidate_hpp

#include "ParticleCandidate.hpp"
#include "MuonCandidate.hpp"
#include "../constantes.h"

class JPsiCandidate: public ParticleCandidate {
public:
	JPsiCandidate(MuonCandidate *muon1, MuonCandidate *muon2);
	
	void setProbability(float prob);
	float getProbability();
	void setDecayDistance(float x, float y);
	float getDecayDistance();
	void setDecayDistanceError(float ex_1, float ex_2, float ey_1, float ey_2);
	float getDecayDistanceSigma();
	float getCosAlpha();
	MuonCandidate getMuon1();
	MuonCandidate getMuon2();
	
private:
	MuonCandidate muon_1;
	MuonCandidate muon_2;
	float probability;
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


#endif /* JPsiCandidate_hpp */
