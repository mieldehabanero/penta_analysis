//
//  MuonCandidate.hpp
//  
//
//  Created by Ricardo Zamora on 1/5/18.
//

#ifndef MuonCandidate_hpp
#define MuonCandidate_hpp

#include "ParticleCandidate.hpp"
#include "TVector3.h"
#include "../constantes.h"

class MuonCandidate: public ParticleCandidate {
public:
	MuonCandidate(float px, float py, float pz);
	double getETA();
};

#endif /* MuonCandidate_hpp */
