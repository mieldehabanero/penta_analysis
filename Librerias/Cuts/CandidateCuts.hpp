//
//  CandidateCuts.hpp
//  
//
//  Created by Ricardo Zamora on 1/5/18.
//

#ifndef CandidateCuts_hpp
#define CandidateCuts_hpp

#include "../Particles/ParticleCandidate.hpp"
#include <stdio.h>

class CandidateCuts {
protected:
	std::vector<int (*)()> cuts;
	
public:
	CandidateCuts(){};
	void applyCuts(){};
};

#endif /* CandidateCuts_hpp */
