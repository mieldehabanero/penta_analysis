//
//  PionCandidate.hpp
//  
//
//  Created by Ricardo Zamora on 1/5/18.
//

#ifndef PionCandidate_hpp
#define PionCandidate_hpp

#include "ParticleCandidate.hpp"
#include "../constantes.h"

class PionCandidate: public ParticleCandidate {
public:
	PionCandidate(float px, float py, float pz);
};

#endif /* PionCandidate_hpp */
