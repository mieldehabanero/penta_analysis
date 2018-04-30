//
//  pentaquark.c
//  
//
//  Created by Ricardo Zamora on 30/4/18.
//

#include "pentaquark.h"
#include "operaciones.h"
#include "fit.h"

void fit_pentaquark_breit_wigner(){
	std::string data_path = "Resultados/candidatos_lambda_b.root";
	std::string ntuple_name = "candidatos_lambda_b";
	std::string variable_name = "lambda_b_mass";
	std::string variable_description = "m(J/#Psi #Lambda) [GeV]";
	std::vector<float> variable_range = {JPSI_LAMBDA_THRESHOLD+0.004, 4.7};
	std::vector<float> mean_range = {4.3, JPSI_LAMBDA_THRESHOLD+0.01, 4.4};
	std::vector<float> gamma_range = {0.08, 0.0001, 0.3};
	std::vector<float> background_fraction = {0.1, 0, 1};
	std::vector<vector<float>> d0_params = {{JPSI_LAMBDA_THRESHOLD}, {-10, -0.75, 10}, {-100, 1.00, 10}, {-10, -0.40, 10}};
	unsigned int bin_number = 45;
	
	float mean_value = 4.319;
	float gamma_value = 0.035;
	
	fit_breit_wigner(data_path, ntuple_name, variable_name, variable_description, variable_range, mean_range, gamma_range, d0_params, background_fraction, bin_number);
	
	fit_breit_wigner_fija(data_path, ntuple_name, variable_name, variable_description, variable_range, mean_value, gamma_value, d0_params, background_fraction, bin_number);
}

void fit_pentaquark_breit_wigner_fija(){
	std::string data_path = "Resultados/candidatos_lambda_b.root";
	std::string ntuple_name = "candidatos_lambda_b";
	std::string variable_name = "lambda_b_mass";
	std::string variable_description = "m(J/#Psi #Lambda) [GeV]";
	std::vector<float> variable_range = {JPSI_LAMBDA_THRESHOLD+0.004, 4.7};
	float mean_value = 4.319;
	float gamma_value = 0.035;
	std::vector<float> background_fraction = {0.1, 0, 1};
	std::vector<vector<float>> d0_params = {{JPSI_LAMBDA_THRESHOLD}, {-10, -0.75, 10}, {-100, 1.00, 10}, {-10, -0.40, 10}};
	unsigned int bin_number = 45;
	
	fit_breit_wigner_fija(data_path, ntuple_name, variable_name, variable_description, variable_range, mean_value, gamma_value, d0_params, background_fraction, bin_number);
}

void fit_pentaquark_gauss_fija(){
	std::string data_path = "Resultados/candidatos_lambda_b.root";
	std::string ntuple_name = "candidatos_lambda_b";
	std::string variable_name = "lambda_b_mass";
	std::string variable_description = "m(J/#Psi #Lambda) [GeV]";
	std::vector<float> variable_range = {JPSI_LAMBDA_THRESHOLD+0.004, 4.7};
	float mean_value = 4.319;
	float sigma_value = 0.0156;
	std::vector<float> background_fraction = {0.1, 0, 1};
	std::vector<vector<float>> d0_params = {{JPSI_LAMBDA_THRESHOLD}, {-10, -0.75, 10}, {-100, 1.00, 10}, {-10, -0.40, 10}};
	unsigned int bin_number = 45;
	
	fit_gauss_fija(data_path, ntuple_name, variable_name, variable_description, variable_range, mean_value, sigma_value, d0_params, background_fraction, bin_number);
}

void fit_pentaquark_gauss(){
	std::string data_path = "Resultados/candidatos_lambda_b.root";
	std::string ntuple_name = "candidatos_lambda_b";
	std::string variable_name = "lambda_b_mass";
	std::string variable_description = "m(J/#Psi #Lambda) [GeV]";
	std::vector<float> variable_range = {JPSI_LAMBDA_THRESHOLD+0.004, 4.7};
	std::vector<float> mean_range = {4.3, JPSI_LAMBDA_THRESHOLD+0.01, 4.4};
	std::vector<float> sigma_range = {0.012, 0.001, 1};
	std::vector<float> background_fraction = {0.1, 0, 1};
	std::vector<vector<float>> d0_params = {{JPSI_LAMBDA_THRESHOLD}, {-10, -0.75, 10}, {-100, 1.00, 10}, {-10, -0.40, 10}};
	unsigned int bin_number = 45;
	
	fit_gauss(data_path, ntuple_name, variable_name, variable_description, variable_range, mean_range, sigma_range, d0_params, background_fraction, bin_number);
}

//para pruebas fit_pentaquark_ruido(0.130852, 2.07974, 0.00482206)
void fit_pentaquark_ruido(float c1, float c2, float b){
	std::string data_path = "Resultados/candidatos_lambda_b.root";
	std::string ntuple_name = "candidatos_lambda_b";
	std::string variable_name = "lambda_b_mass";
	std::string variable_title = "J/#Psi #Lambda Mass";
	std::string variable_description = "m(J/#Psi #Lambda) [GeV]";
	std::vector<float> variable_range = {JPSI_LAMBDA_THRESHOLD + 0.004, 4.7};
	std::vector<float> d0_params = {JPSI_LAMBDA_THRESHOLD, c1, c2, b};
	unsigned int bin_number = 45;
	 
	fit_polinomio_d0(data_path, ntuple_name, variable_name, variable_title, variable_description, variable_range, d0_params, bin_number);
}
