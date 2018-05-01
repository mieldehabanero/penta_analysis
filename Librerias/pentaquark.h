//
//  pentaquark.h
//  
//
//  Created by Ricardo Zamora on 30/4/18.
//

#ifndef constantes_h
#include "constantes.h"
#endif /* constantes_h */

#ifndef pentaquark_h
#define pentaquark_h

void fit_pentaquark_breit_wigner();
void fit_pentaquark_breit_wigner_fija();
void fit_pentaquark_gauss(float c1, float c2, float b);
void fit_pentaquark_gauss_fija();
void fit_pentaquark_ruido(float c1, float c2, float b);
void pentaquark_distribucion_masa(float lower_limit, float upper_limit);

//Valores obtenidos por el PDG.
#define PENTAQUARK_DATA_PATH "Resultados/candidatos_lambda_b.root"
#define PENTAQUARK_NTUPLE_NAME "candidatos_lambda_b"
#define PENTAQUARK_VARIABLE_NAME "lambda_b_mass"
#define PENTAQUARK_VARIABLE_TITLE "J/#Psi #Lambda Mass"
#define PENTAQUARK_VARIABLE_DESCRIPTION "m(J/#Psi #Lambda) [GeV]"
#define MEV_PER_BIN 0.01

#endif /* pentaquark_h */
