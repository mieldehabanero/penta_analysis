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

int es_candidato_lambda_0(float lambda_0_chi2, std::vector<float>lambda_0_p, std::vector<float>d_xy, std::vector<float>L_xy_E, float proton_pt_magnitude, float pion_pt_magnitude, float charged_prob, float l0_mass);
float calcula_energia_lambda_0(std::vector<float>proton_p, std::vector<float>pion_p);
int corte_masa_lambda_0(float masa);
void fit_lambda_0();

#endif /* lambda_0_h */
