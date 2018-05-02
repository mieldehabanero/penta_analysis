//
//  KaonCandidate.cpp
//  
//
//  Created by Ricardo Zamora on 1/5/18.
//

#include "KaonCandidate.hpp"

KaonCandidate::KaonCandidate(PionCandidate *pion_1, PionCandidate *pion_2):pion1(*pion_1), pion2(*pion_2), ParticleCandidate(pion_1->getFourMomentum() + pion_2->getFourMomentum(), K_SHORT_MASS){
}
