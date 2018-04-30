//
//  j_psi.c
//  
//
//  Created by Ricardo Zamora on 28/1/18.
//

#include "j_psi.h"
#include "operaciones.h"
#include "fit.h"

static int aplica_cortes_jpsi(float muon_pt1, float muon_pt2, float jpsi_prob, float L_xy_sigma, float cos_alpha, float jpsi_pt, float mass);
static int corte_pt_muon(float muon_pt1, float muon_pt2);
static int corte_prob_jpsi(float prob);
static int corte_lxy_jpsi(float l_xy);
static int corte_pointing_angle(float cos_alhpa);
static int corte_pt_jpsi(float j_psi_pt);
static int corte_masa_jpsi(float masa);

int es_candidato_jpsi(std::vector<float>muon_p1, std::vector<float>muon_p2, float muon_prob, std::vector<float>jpsi_p, std::vector<float>jpsi_d_xy, std::vector<float>jpsi_L_xy_E, float jpsi_invariant_mass) {

	//PT son lascomponentes x,y del P
	float muon_pt1_magnitude = norma_dos(muon_p1[0], muon_p1[1]);
	float muon_pt2_magnitude = norma_dos(muon_p2[0], muon_p2[1]);
	float jpsi_pt_magnitude = norma_dos(jpsi_p[0], jpsi_p[1]);
	
	//Todo esto es para calcular Lxy/sigma
	float jpsi_pt_gorro[2] = {jpsi_p[0]/jpsi_pt_magnitude, jpsi_p[1]/jpsi_pt_magnitude};
//	float jpsi_sigma = calcula_sigma(jpsi_L_xy_E, jpsi_d_xy);
//	float jpsi_L_xy_magnitud = calcula_L_xy_magnitud(jpsi_d_xy, jpsi_pt_gorro);
//	float jpsi_L_xy_sigma = jpsi_L_xy_magnitud/jpsi_sigma;
//	float jpsi_cos_alpha = calcula_cos_alpha(jpsi_L_xy_magnitud, jpsi_d_xy);
	
	float jpsi_sigma = calcula_sigma_nuevo(jpsi_L_xy_E, jpsi_d_xy);
	float jpsi_D_xy_magnitud = calcula_D_xy_magnitud_nuevo(jpsi_d_xy);
	float jpsi_L_xy_sigma = jpsi_D_xy_magnitud/jpsi_sigma;
//	float jpsi_cos_alpha = calcula_cos_alpha(jpsi_D_xy_magnitud, jpsi_d_xy);
	float jpsi_cos_alpha = calcula_cos_alpha_nuevo(jpsi_d_xy, jpsi_p);
	
	int es_candidato = aplica_cortes_jpsi(muon_pt1_magnitude, muon_pt2_magnitude, muon_prob, jpsi_L_xy_sigma, jpsi_cos_alpha, jpsi_pt_magnitude, jpsi_invariant_mass);
	return es_candidato;
	
}

int aplica_cortes_jpsi(float muon_pt1, float muon_pt2, float jpsi_prob, float L_xy_sigma, float cos_alpha, float jpsi_pt, float mass) {
	
	//pt(µ) > 4.0 GeV
	int pasa_corte_pt_mu = corte_pt_muon(muon_pt1, muon_pt2);
	if(!pasa_corte_pt_mu){
		return 0;
	}
	
	//Se calcula si la probabilidad de un vertice común es >15%
	int pasa_corte_prob = corte_prob_jpsi(jpsi_prob);
	if(!pasa_corte_prob){
		return 0;
	}
	
	//L_xy/sigma > 3
	int pasa_corte_distancia = corte_lxy_jpsi(L_xy_sigma);
	if(!pasa_corte_distancia){
		return 0;
	}
	
	int pasa_corte_pointing_angle = corte_pointing_angle(cos_alpha);
	if(!pasa_corte_pointing_angle){
		return 0;
	}
	
	//pt(µ+µ-) > 8.0 GeV
	int pasa_corte_pt = corte_pt_jpsi(jpsi_pt);
	if(!pasa_corte_pt){
		return 0;
	}
	
	//Se calcula si la masa del J/Psi esta dentro del rango (M_jPsi +- 150MeV)
	int pasa_corte_masa = corte_masa_jpsi(mass);
	if(!pasa_corte_masa){
		return 0;
	}
	
	
	return 1;
}

//Checa si el pt de ambos µ esta en el rango requerido, sí = 1, no = 0.
int corte_pt_muon(float muon_pt1, float muon_pt2) {
	
	//Se calcula si los pts están dentro del rango (pt_µ > 4GeV)
	if (muon_pt1 > MUON_PT_CUT && muon_pt2 > MUON_PT_CUT){
		return 1;
	}
	return 0;
}

//Checa si la probabilidad de que µ+µ- vengan del mismo vértice, sí = 1, no = 0.
static int corte_prob_jpsi(float prob) {
	
	//Se calcula si la probabilidad es mayor al cuttoff
	if (prob > J_PSI_PROB_CUT){
		return 1;
	}
	return 0;
}

static int corte_lxy_jpsi(float l_xy) {
	if (l_xy > J_PSI_LXY_S_CUT){
		return 1;
	}
	return 0;
}

static int corte_pointing_angle(float cos_alpha) {
	if (cos_alpha > J_PSI_COS_ALPHA){
		return 1;
	}
	return 0;
}


//Checa si el pt del J/Psi esta en el rango requerido, sí = 1, no = 0.
static int corte_pt_jpsi(float j_psi_pt) {
	
	//Se calcula si los pts están dentro del rango (pt_µ > 4GeV, y pt_µ+µ- > 8GeV)
	if (j_psi_pt > J_PSI_PT_CUT){
		return 1;
	}
	return 0;
}

//Checa si la masa del J/Psi esta en el rango requerido, sí = 1, no = 0.
//masa esta en MeV
static int corte_masa_jpsi(float masa) {
	float valorInferior = (J_PSI_MASS - J_PSI_MASS_CUT);
	float valorSuperior = (J_PSI_MASS + J_PSI_MASS_CUT);
	
	if (valorInferior < masa && masa < valorSuperior){
		return 1;
	}
	return 0;
}

float calcula_energia_jpsi(std::vector<float>muon_p1, std::vector<float>muon_p2){
	float muon_p1_magnitude = norma_tres(muon_p1[0], muon_p1[1], muon_p1[2]);
	float muon_p2_magnitude = norma_tres(muon_p2[0], muon_p2[1], muon_p2[2]);
	float muon_e1 = calcula_energia_relativista(MUON_MASS, muon_p1_magnitude);
	float muon_e2 = calcula_energia_relativista(MUON_MASS, muon_p2_magnitude);
	
	return muon_e1 + muon_e2;
}

void fit_jpsi(){
	std::string data_path = "Resultados/candidatos_jpsi.root";
	std::string ntuple_name = "candidatos_jpsi";
	std::string variable_name = "jpsi_mass";
	std::string variable_title = "mu^{+} #mu^{-} Mass";
	std::string variable_description = "m(#mu^{+} #mu^{-}) [GeV]";
	std::vector<float> variable_range = {2.95, 3.25};
	std::vector<float> mean_range = {3.091, 2.95, 3.25};
	std::vector<float> sigma1_range = {0.065, 0.01, 0.4};
	std::vector<float> sigma2_range = {0.02, 0.01, 0.4};
	std::vector<float> sigma_fraction = {0.5, 0., 1.};
	std::vector<vector<float>> poly_range = {{0, -0.31, 0.31}};
	std::vector<float> background_fraction = {0.005, 0., 0.012};
	unsigned int bin_number = 30;
	
	fit_double_gauss(data_path, ntuple_name, variable_name, variable_title, variable_description, variable_range, mean_range, sigma1_range, sigma2_range, sigma_fraction, poly_range, background_fraction, bin_number);
}
