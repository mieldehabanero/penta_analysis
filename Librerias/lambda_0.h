//
//  lambda_0.h
//  
//
//  Created by Ricardo Zamora on 28/1/18.
//

#ifndef constantes_h
#include "constantes.h"
#endif /* constantes_h */

#ifndef lambda_0_h
#define lambda_0_h

#include "Particles/ProtonCandidate.hpp"
#include "Particles/PionCandidate.hpp"
#include "Particles/LambdaCandidate.hpp"

int es_candidato_lambda_0(ProtonCandidate *proton, PionCandidate *pion, LambdaCandidate *lambda);
int corte_masa_lambda_0(LambdaCandidate *lambda);
void fit_lambda_0();

#endif /* lambda_0_h */
