//
//  kaon.c
//  
//
//  Created by Ricardo Zamora on 30/1/18.
//

#include "kaon.h"
#include "fit.h"

int es_candidato_k_short(KaonCandidate *k_short){
	float valorInferior = (K_SHORT_MASS - K_SHORT_MASS_CUT);
	float valorSuperior = (K_SHORT_MASS + K_SHORT_MASS_CUT);
	
	if (valorInferior < k_short->getInvariantMass() && k_short->getInvariantMass() < valorSuperior){
		return 1;
	}
	return 0;
}


void fit_k_short(){
	std::string data_path = "Resultados/candidatos_ks.root";
	std::string ntuple_name = "candidatos_ks";
	std::string variable_name = "ks_mass";
	std::string variable_title = "#pi^{+} #pi^{-}Mass";
	std::string variable_description = "m(#pi^{+} #pi^{-}) [GeV]";
	std::vector<float> variable_range = {0.44, 0.56};
	std::vector<float> mean_range = {0.4912, 0.44, 0.56};
	std::vector<float> sigma1_range = {0.012, 0.001, 1};
	std::vector<float> sigma2_range = {0.030, 0.001, 1};
	std::vector<float> sigma_fraction = {0.578, 0., 1.};
	std::vector<vector<float>> poly_range = {{-0.135, -10, 10}};
	std::vector<float> background_fraction = {0.525, 0., 1.};
	unsigned int bin_number = 48;
//	
//	fit_double_gauss(data_path, ntuple_name, variable_name, variable_title, variable_description, variable_range, mean_range, sigma1_range, sigma2_range, sigma_fraction, poly_range, background_fraction, bin_number);
}
