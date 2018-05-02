//
//  JPsiCuts.hpp
//  
//
//  Created by Ricardo Zamora on 1/5/18.
//

#ifndef JPsiCuts_hpp
#define JPsiCuts_hpp

#include "CandidateCuts.hpp"
#include "../Particles/JPsiCandidate.hpp"
#include <stdio.h>

class JPsiCuts: public CandidateCuts {
public:
	JPsiCuts();
	int applyCuts(JPsiCandidate *jpsi);
	
private:
//	std::vector<int ( *)( JPSiCandidate *)> cuts;
	int pt_muon(JPsiCandidate *jpsi);
	int prob(JPsiCandidate *jpsi);
	int lxy(JPsiCandidate *jpsi);
	int pointing_angle(JPsiCandidate *jpsi);
	int pt_jpsi(JPsiCandidate *jpsi);
	int mass(JPsiCandidate *jpsi);
};

#endif /* JPsiCuts_hpp */
