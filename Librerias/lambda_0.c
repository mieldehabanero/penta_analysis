//
//  lambda_0.c
//  
//
//  Created by Ricardo Zamora on 28/1/18.
//

#include "lambda_0.h"
#include "fit.h"

int aplica_cortes_lambda_0(ProtonCandidate *proton, PionCandidate *pion, LambdaCandidate *lambda);
static int corte_d0_lambda_0(LambdaCandidate *lambda);
static int corte_chi2_lambda_0(LambdaCandidate *lambda);
static int corte_lxy_lambda_0(LambdaCandidate *lambda);
static int corte_pt_lambda_0(ProtonCandidate *proton, PionCandidate *pion, LambdaCandidate *lambda);
static int corte_prob_lambda_0(LambdaCandidate *lambda);
//static int corte_masa_lambda_0(LambdaCandidate *lambda);

int es_candidato_lambda_0(ProtonCandidate *proton, PionCandidate *pion, LambdaCandidate *lambda){
	
	//Todo esto es para calcular Lxy/sigma
//	float lambda_0_pt_gorro[2] = {lambda_0_pt[0]/lambda_0_pt_magnitude, lambda_0_pt[1]/lambda_0_pt_magnitude};
//	float sigma = calcula_sigma(L_xy_E);
//	float L_xy_magnitud = calcula_L_xy_magnitud(d_xy, lambda_0_pt_gorro);
//	float L_xy_sigma = L_xy_magnitud/sigma;
	
//	float sigma = calcula_sigma_nuevo(L_xy_E, d_xy);
//	float D_xy_magnitud = calcula_D_xy_magnitud_nuevo(d_xy);
//	float L_xy_sigma = D_xy_magnitud/sigma;
//
//	//Esto es para d0
//	float d0 = norma_dos(d_xy[0], d_xy[1]);
//	float d0_sigma = d0/sigma;
	
	int es_candidato = aplica_cortes_lambda_0(proton, pion, lambda);
	
	return es_candidato;
	
}


int aplica_cortes_lambda_0(ProtonCandidate *proton, PionCandidate *pion, LambdaCandidate *lambda) {
	
	int pasa_corte_d0 = corte_d0_lambda_0(lambda);
	if(!pasa_corte_d0) {
		return 0;
	}
	
	
//	//Se calcula si chi2 es menor a 7
	int pasa_corte_chi2 = corte_chi2_lambda_0(lambda);
	if(!pasa_corte_chi2) {
		return 0;
	}
	
	
	//L_xy/sigma >= 15
	int pasa_corte_l_xy = corte_lxy_lambda_0(lambda);
	if(!pasa_corte_l_xy){
		return 0;
	}
	
	//Se calcula si los pts están dentro del rango (pt_π > 0.3GeV, pt_p > 1.0GeV, y pt_pπ > 1.3GeV)
	int pasa_corte_pt = corte_pt_lambda_0(proton, pion, lambda);
	if(!pasa_corte_pt) {
		return 0;
	}
	
	int pasa_corte_prob = corte_prob_lambda_0(lambda);
	if(!pasa_corte_prob) {
		return 0;
	}
	
	//Se calcula si la masa del Lambda 0 esta dentro del rango (M_jPsi +- 9MeV)
//	int pasa_corte_masa = corte_masa_lambda_0(lambda);
//	if(!pasa_corte_masa) {
//		return 0;
//	}
	
	return 1;
}

static int corte_d0_lambda_0(LambdaCandidate *lambda) {
	if (lambda->getD0Sigma() > LAMBDA_0_D0_S_CUT){
		return 1;
	}
	return 0;
}

static int corte_chi2_lambda_0(LambdaCandidate *lambda) {
	if (lambda->getChi2() < LAMBDA_0_CHI2_CUT){
		return 1;
	}
	return 0;
}

static int corte_lxy_lambda_0(LambdaCandidate *lambda) {
	if (lambda->getDecayDistance()/lambda->getDecayDistanceSigma() >= LAMBDA_0_LXY_S_CUT){
		return 1;
	}
	return 0;
}

//Checa si el pt del Lambda 0 esta en el rango requerido, sí = 1, no = 0.
static int corte_pt_lambda_0(ProtonCandidate *proton, PionCandidate *pion, LambdaCandidate *lambda) {
	
	//Se calcula si los pts están dentro del rango (pt_π > 0.3GeV, pt_p > 1.0GeV, y pt_pπ > 1.3GeV)
	if (proton->getTransverseMomentum() > PROTON_PT_CUT && pion->getTransverseMomentum() > PION_PT_CUT && lambda->getTransverseMomentum() > LAMBDA_0_PT_CUT){
		return 1;
	}
	return 0;
}

//Checa si la probabilidad de que µ+µ- vengan del mismo vértice, sí = 1, no = 0.
static int corte_prob_lambda_0(LambdaCandidate *lambda) {
	//Valores en GeV
	
	//Se calcula si la probabilidad es mayor al cuttoff
	if (lambda->getProbability() > LAMBDA_0_PROB_CUT){
		return 1;
	}
	return 0;
}

//Checa si la masa del Lambda 0 esta en el rango requerido, sí = 1, no = 0.
int corte_masa_lambda_0(LambdaCandidate *lambda) {
	
	float valorInferior = (LAMBDA_0_MASS - LAMBDA_0_MASS_CUT);
	float valorSuperior = (LAMBDA_0_MASS + LAMBDA_0_MASS_CUT);
	
	if (valorInferior < lambda->getInvariantMass() && lambda->getInvariantMass() < valorSuperior){
		return 1;
	}
	return 0;
}

void fit_lambda_0(){
	std::string data_path = "Resultados/candidatos_lambda_0.root";
	std::string ntuple_name = "candidatos_lambda_0";
	std::string variable_name = "lambda_0_mass";
	std::string variable_title = "#p^{+} #pi^{-} Mass";
	std::string variable_description = "m(#p^{+} #pi^{-}) [GeV]";
	std::vector<float> variable_range = {1.10, 1.13};
	std::vector<float> mean_range = {1.10, 1.11593, 1.13};
	std::vector<float> sigma1_range = {0.0003, 0.001, 0.002};
	std::vector<float> sigma2_range = {0.003, 0.001, 0.004};
	std::vector<float> sigma_fraction = {0.5, 0., 1.};
	std::vector<float> background_fraction = {0.05, 0., 0.075};
	std::vector<vector<float>> poly_range = {{731062*2, 0, 664602*3}};
	unsigned int bin_number = 50;
	
//	fit_double_gauss(data_path, ntuple_name, variable_name, variable_title, variable_description, variable_range, mean_range, sigma1_range, sigma2_range, sigma_fraction, poly_range, background_fraction, bin_number);
}
