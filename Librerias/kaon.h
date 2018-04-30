//
//  kaon.h
//  
//
//  Created by Ricardo Zamora on 30/1/18.
//

#ifndef constantes_h
#include "constantes.h"
#endif /* constantes_h */

#ifndef kaon_h
#define kaon_h

float calcula_energia_k_short(std::vector<float>pion_p1, std::vector<float>pion_p2);
int es_candidato_k_short(float k_short_mass);
void fit_k_short();

#endif /* kaon_h */
