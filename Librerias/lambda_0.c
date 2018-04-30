//
//  lambda_0.c
//  
//
//  Created by Ricardo Zamora on 28/1/18.
//

#include "lambda_0.h"
#include "operaciones.h"
#include "fit.h"

int aplica_cortes_lambda_0(float d0_sigma, float chi2, float L_xy_sigma, float proton_pt, float pion_pt, float lambda_0_pt, float charged_prob, float l0_mass);
static int corte_d0_lambda_0(float d0_sigma);
static int corte_chi2_lambda_0(float chi2);
static int corte_lxy_lambda_0(float l_xy);
static int corte_pt_lambda_0(float lambda_0_pt, float pion_pt, float proton_pt);
static int corte_prob_lambda_0(float prob);
//static int corte_masa_lambda_0(float masa);

int es_candidato_lambda_0(float lambda_0_chi2, std::vector<float>lambda_0_p, std::vector<float>d_xy, std::vector<float>L_xy_E, float proton_pt_magnitude, float pion_pt_magnitude, float charged_prob, float l0_mass){
	
	float lambda_0_pt[2] = {lambda_0_p[0], lambda_0_p[1]};
	float lambda_0_pt_magnitude = norma_dos(lambda_0_pt[0], lambda_0_pt[1]);
	
	//Todo esto es para calcular Lxy/sigma
	float lambda_0_pt_gorro[2] = {lambda_0_pt[0]/lambda_0_pt_magnitude, lambda_0_pt[1]/lambda_0_pt_magnitude};
//	float sigma = calcula_sigma(L_xy_E);
//	float L_xy_magnitud = calcula_L_xy_magnitud(d_xy, lambda_0_pt_gorro);
//	float L_xy_sigma = L_xy_magnitud/sigma;
	
	float sigma = calcula_sigma_nuevo(L_xy_E, d_xy);
	float D_xy_magnitud = calcula_D_xy_magnitud_nuevo(d_xy);
	float L_xy_sigma = D_xy_magnitud/sigma;
	
	//Esto es para d0
	float d0 = norma_dos(d_xy[0], d_xy[1]);
	float d0_sigma = d0/sigma;
	
	int es_candidato = aplica_cortes_lambda_0(d0_sigma, lambda_0_chi2, L_xy_sigma, proton_pt_magnitude, pion_pt_magnitude, lambda_0_pt_magnitude, charged_prob, l0_mass);
	
	return es_candidato;
	
}


int aplica_cortes_lambda_0(float d0_sigma, float chi2, float L_xy_sigma, float proton_pt, float pion_pt, float lambda_0_pt, float charged_prob, float l0_mass) {
	
	int pasa_corte_d0 = corte_d0_lambda_0(d0_sigma);
	if(!pasa_corte_d0) {
		return 0;
	}
	
	
//	//Se calcula si chi2 es menor a 7
	int pasa_corte_chi2 = corte_chi2_lambda_0(chi2);
	if(!pasa_corte_chi2) {
		return 0;
	}
	
	
	//L_xy/sigma >= 15
	int pasa_corte_l_xy = corte_lxy_lambda_0(L_xy_sigma);
	if(!pasa_corte_l_xy){
		return 0;
	}
	
	//Se calcula si los pts están dentro del rango (pt_π > 0.3GeV, pt_p > 1.0GeV, y pt_pπ > 1.3GeV)
	int pasa_corte_pt = corte_pt_lambda_0(lambda_0_pt, pion_pt, proton_pt);
	if(!pasa_corte_pt) {
		return 0;
	}
	
	int pasa_corte_prob = corte_prob_lambda_0(charged_prob);
	if(!pasa_corte_prob) {
		return 0;
	}
	
	//Se calcula si la masa del Lambda 0 esta dentro del rango (M_jPsi +- 9MeV)
//	int pasa_corte_masa = corte_masa_lambda_0(l0_mass);
//	if(!pasa_corte_masa) {
//		return 0;
//	}
	
	return 1;
}

static int corte_d0_lambda_0(float d0_sigma) {
	if (d0_sigma > LAMBDA_0_D0_S_CUT){
		return 1;
	}
	return 0;
}

static int corte_chi2_lambda_0(float chi2) {
	if (chi2 < LAMBDA_0_CHI2_CUT){
		return 1;
	}
	return 0;
}

static int corte_lxy_lambda_0(float l_xy) {
	if (l_xy >= LAMBDA_0_LXY_S_CUT){
		return 1;
	}
	return 0;
}

//Checa si el pt del Lambda 0 esta en el rango requerido, sí = 1, no = 0.
static int corte_pt_lambda_0(float lambda_0_pt, float pion_pt, float proton_pt) {
	
	//Se calcula si los pts están dentro del rango (pt_π > 0.3GeV, pt_p > 1.0GeV, y pt_pπ > 1.3GeV)
	if (proton_pt > PROTON_PT_CUT && pion_pt > PION_PT_CUT && lambda_0_pt > LAMBDA_0_PT_CUT){
		return 1;
	}
	return 0;
}

//Checa si la probabilidad de que µ+µ- vengan del mismo vértice, sí = 1, no = 0.
static int corte_prob_lambda_0(float prob) {
	//Valores en GeV
	
	//Se calcula si la probabilidad es mayor al cuttoff
	if (prob > LAMBDA_0_PROB_CUT){
		return 1;
	}
	return 0;
}

//Checa si la masa del Lambda 0 esta en el rango requerido, sí = 1, no = 0.
int corte_masa_lambda_0(float masa) {
	
	float valorInferior = (LAMBDA_0_MASS - LAMBDA_0_MASS_CUT);
	float valorSuperior = (LAMBDA_0_MASS + LAMBDA_0_MASS_CUT);
	
	if (valorInferior < masa && masa < valorSuperior){
		return 1;
	}
	return 0;
}

float calcula_energia_lambda_0(std::vector<float>proton_p, std::vector<float>pion_p){
	float proton_p_magnitude = norma_tres(proton_p[0], proton_p[1], proton_p[2]);
	float pion_p_magnitude = norma_tres(pion_p[0], pion_p[1], pion_p[2]);
	
	float proton_e = calcula_energia_relativista(PROTON_MASS, proton_p_magnitude);
	float pion_e = calcula_energia_relativista(PION_MASS, pion_p_magnitude);
	float lambda_0_e = proton_e + pion_e;
	return lambda_0_e;
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
	
	fit_double_gauss(data_path, ntuple_name, variable_name, variable_title, variable_description, variable_range, mean_range, sigma1_range, sigma2_range, sigma_fraction, poly_range, background_fraction, bin_number);
}
