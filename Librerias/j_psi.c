//
//  j_psi.c
//  
//
//  Created by Ricardo Zamora on 28/1/18.
//

#include "j_psi.h"
#include "fit.h"
#include "Particles/MuonCandidate.hpp"
#include "Particles/JPsiCandidate.hpp"

static int aplica_cortes_jpsi(MuonCandidate *muon1, MuonCandidate *muon2, JPsiCandidate *jpsi);
static int corte_pt_muon(MuonCandidate *muon1, MuonCandidate *muon2);
static int corte_prob_jpsi(JPsiCandidate *jpsi);
static int corte_lxy_jpsi(JPsiCandidate *jpsi);
static int corte_pointing_angle(JPsiCandidate *jpsi);
static int corte_pt_jpsi(JPsiCandidate *jpsi);
static int corte_masa_jpsi(JPsiCandidate *jpsi);

int es_candidato_jpsi(MuonCandidate *muon1, MuonCandidate *muon2, JPsiCandidate *jpsi) {

	
	//Todo esto es para calcular Lxy/sigma
//	float jpsi_pt_gorro[2] = {jpsi_p[0]/jpsi_pt_magnitude, jpsi_p[1]/jpsi_pt_magnitude};
//	float jpsi_sigma = calcula_sigma(jpsi_L_xy_E, jpsi_d_xy);
//	float jpsi_L_xy_magnitud = calcula_L_xy_magnitud(jpsi_d_xy, jpsi_pt_gorro);
//	float jpsi_L_xy_sigma = jpsi_L_xy_magnitud/jpsi_sigma;
//	float jpsi_cos_alpha = calcula_cos_alpha(jpsi_L_xy_magnitud, jpsi_d_xy);
	
	float jpsi_sigma = jpsi->getDecayDistanceSigma();
	float jpsi_D_xy_magnitud = jpsi->getDecayDistance();
	float jpsi_L_xy_sigma = jpsi_D_xy_magnitud/jpsi_sigma;
	
	int es_candidato = aplica_cortes_jpsi(muon1, muon2, jpsi);
	return es_candidato;
	
}

int aplica_cortes_jpsi(MuonCandidate *muon1, MuonCandidate *muon2, JPsiCandidate *jpsi) {
	
	//pt(µ) > 4.0 GeV
	int pasa_corte_pt_mu = corte_pt_muon(muon1, muon2);
	if(!pasa_corte_pt_mu){
		return 0;
	}
	
	//Se calcula si la probabilidad de un vertice común es >15%
	int pasa_corte_prob = corte_prob_jpsi(jpsi);
	if(!pasa_corte_prob){
		return 0;
	}
	
	//L_xy/sigma > 3
	int pasa_corte_distancia = corte_lxy_jpsi(jpsi);
	if(!pasa_corte_distancia){
		return 0;
	}
	
	int pasa_corte_pointing_angle = corte_pointing_angle(jpsi);
	if(!pasa_corte_pointing_angle){
		return 0;
	}
	
	//pt(µ+µ-) > 8.0 GeV
	int pasa_corte_pt = corte_pt_jpsi(jpsi);
	if(!pasa_corte_pt){
		return 0;
	}
	
	//Se calcula si la masa del J/Psi esta dentro del rango (M_jPsi +- 150MeV)
	int pasa_corte_masa = corte_masa_jpsi(jpsi);
	if(!pasa_corte_masa){
		return 0;
	}
	
	
	return 1;
}

//Checa si el pt de ambos µ esta en el rango requerido, sí = 1, no = 0.
int corte_pt_muon(MuonCandidate *muon1, MuonCandidate *muon2) {
	
	//Se calcula si los pts están dentro del rango (pt_µ > 4GeV)
	if (muon1->getTransverseMomentum() > MUON_PT_CUT && muon2->getTransverseMomentum() > MUON_PT_CUT){
		return 1;
	}
	return 0;
}

//Checa si la probabilidad de que µ+µ- vengan del mismo vértice, sí = 1, no = 0.
static int corte_prob_jpsi(JPsiCandidate *jpsi) {
	
	//Se calcula si la probabilidad es mayor al cuttoff
	if (jpsi->getProbability() > J_PSI_PROB_CUT){
		return 1;
	}
	return 0;
}

static int corte_lxy_jpsi(JPsiCandidate *jpsi) {
	if (jpsi->getDecayDistance()/jpsi->getDecayDistanceSigma() > J_PSI_LXY_S_CUT){
		return 1;
	}
	return 0;
}

static int corte_pointing_angle(JPsiCandidate *jpsi) {
	if (jpsi->getCosAlpha() > J_PSI_COS_ALPHA){
		return 1;
	}
	return 0;
}


//Checa si el pt del J/Psi esta en el rango requerido, sí = 1, no = 0.
static int corte_pt_jpsi(JPsiCandidate *jpsi) {
	
	//Se calcula si los pts están dentro del rango (pt_µ > 4GeV, y pt_µ+µ- > 8GeV)
	if (jpsi->getTransverseMomentum() > J_PSI_PT_CUT){
		return 1;
	}
	return 0;
}

//Checa si la masa del J/Psi esta en el rango requerido, sí = 1, no = 0.
//masa esta en MeV
static int corte_masa_jpsi(JPsiCandidate *jpsi) {
	float valorInferior = (J_PSI_MASS - J_PSI_MASS_CUT);
	float valorSuperior = (J_PSI_MASS + J_PSI_MASS_CUT);
	
	if (valorInferior < jpsi->getInvariantMass() && jpsi->getInvariantMass() < valorSuperior){
		return 1;
	}
	return 0;
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
	
//	fit_double_gauss(data_path, ntuple_name, variable_name, variable_title, variable_description, variable_range, mean_range, sigma1_range, sigma2_range, sigma_fraction, poly_range, background_fraction, bin_number);
}
