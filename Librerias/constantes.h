//
//  constantes.h
//  Todos los valores en [GeV] o [%]
//
//  Created by Ricardo Zamora on 28/1/18.
//

#ifndef constantes_h
#define constantes_h


//Valores obtenidos por el PDG.
#define MUON_MASS 0.1056583745
#define PROTON_MASS 0.938272081
#define PION_MASS 0.13957018

#define J_PSI_MASS 3.096916
#define J_PSI_MASS_DELTA 0.000011

#define LAMBDA_0_MASS 1.115683
#define LAMBDA_0_MASS_DELTA 0.000006


//Valores de los cortes definidos en el paper de CMS.
//Cortes para candidatos J/Psi
#define MUON_PT_CUT 4.0
#define J_PSI_PROB_CUT 0.15 //[%]
#define J_PSI_LXY_S_CUT 3.0
#define J_PSI_COS_ALPHA 0.95
#define J_PSI_PT_CUT 8.0
#define J_PSI_MASS_CUT 0.150

//Cortes para candidatos Lambda_0
#define LAMBDA_0_D0_S_CUT 2.0
#define LAMBDA_0_CHI2_CUT 7.0
#define LAMBDA_0_LXY_S_CUT 15.0
#define PROTON_PT_CUT 1.0
#define PION_PT_CUT 0.3
#define LAMBDA_0_PT_CUT 1.3
#define LAMBDA_0_PROB_CUT 0.02 //[%]
#define LAMBDA_0_MASS_CUT 0.009
#define K_SHORT_MASS 0.497611
#define K_SHORT_MASS_CUT 0.020

//Cortes para candidatos Lambda_b
#define LAMBDA_B_PT_CUT 10.0
#define LAMBDA_B_PROB_CUT 0.03 //[%]
#define LAMBDA_B_MASS_UPPER_LIMIT 5.840
//#define LAMBDA_B_MASS_UPPER_LIMIT 6.5
#define LAMBDA_B_MASS_LOWER_LIMIT 4.200

//Valor original de la ventana de masa
//#define LAMBDA_B_MASS_LOWER_LIMIT 5.40

#endif /* constantes_h */
