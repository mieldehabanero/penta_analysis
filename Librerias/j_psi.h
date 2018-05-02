//
//  j_psi.h
//  
//
//  Created by Ricardo Zamora on 28/1/18.
//

#ifndef constantes_h
#include "constantes.h"
#endif /* constantes_h */

#ifndef j_psi_h
#define j_psi_h

#include "Particles/MuonCandidate.hpp"
#include "Particles/JPsiCandidate.hpp"

int es_candidato_jpsi(MuonCandidate *muon1, MuonCandidate *muon2, JPsiCandidate *jpsi);
void fit_jpsi();

#endif /* j_psi_h */
