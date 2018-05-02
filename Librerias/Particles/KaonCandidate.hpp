//
//  KaonCandidate.hpp
//  
//
//  Created by Ricardo Zamora on 1/5/18.
//

#ifndef KaonCandidate_hpp
#define KaonCandidate_hpp

#include "ParticleCandidate.hpp"
#include "PionCandidate.hpp"
#include "ProtonCandidate.hpp"
#include "../constantes.h"

class KaonCandidate: public ParticleCandidate {
public:
	KaonCandidate(PionCandidate *pion_1, PionCandidate *pion_2);
	
private:
	PionCandidate pion1;
	PionCandidate pion2;
};

#endif /* KaonCandidate_hpp */
