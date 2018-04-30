//
//  fits.c
//  
//
//  Created by Ricardo Zamora on 30/4/18.
//

#include <stdio.h>
#include "Librerias/kaon.h"
#include "Librerias/lambda_0.h"
#include "Librerias/lambda_b.h"
#include "Librerias/j_psi.h"
#include "Librerias/pentaquark.h"

void haz_el_fit(){
	fit_lambda_b();
	fit_jpsi();
	fit_lambda_0();
	fit_k_short();
}

void fits_pico(){
	fit_pentaquark_breit_wigner();
	fit_pentaquark_breit_wigner_fija();
	fit_pentaquark_gauss();
	fit_pentaquark_gauss_fija();
}
