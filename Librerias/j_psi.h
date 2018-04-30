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

int es_candidato_jpsi(std::vector<float>muon_p1, std::vector<float>muon_p2, float muon_prob, std::vector<float>jpsi_p, std::vector<float>jpsi_d_xy, std::vector<float>jpsi_L_xy_E, float jpsi_invariant_mass);
float calcula_energia_jpsi(std::vector<float>muon_p1, std::vector<float>muon_p2);
void fit_jpsi();

#endif /* j_psi_h */
