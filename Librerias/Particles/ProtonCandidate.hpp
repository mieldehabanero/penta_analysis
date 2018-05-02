//
//  ProtonCandidate.hpp
//  
//
//  Created by Ricardo Zamora on 1/5/18.
//

#ifndef ProtonCandidate_hpp
#define ProtonCandidate_hpp

#include "ParticleCandidate.hpp"
#include "../constantes.h"

class ProtonCandidate: public ParticleCandidate {
public:
	ProtonCandidate(float px, float py, float pz);
};

#endif /* ProtonCandidate_hpp */
