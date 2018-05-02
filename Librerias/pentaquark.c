//
//  pentaquark.c
//  
//
//  Created by Ricardo Zamora on 30/4/18.
//

#include "pentaquark.h"
#include "fit.h"

std::string data_path = PENTAQUARK_DATA_PATH;
std::string ntuple_name = PENTAQUARK_NTUPLE_NAME;
std::string variable_name = PENTAQUARK_VARIABLE_NAME;
std::string variable_title = PENTAQUARK_VARIABLE_TITLE;
std::string variable_description = PENTAQUARK_VARIABLE_DESCRIPTION;

void fit_pentaquark_breit_wigner(){
	std::vector<float> variable_range = {JPSI_LAMBDA_THRESHOLD+0.004, 4.7};
	std::vector<float> mean_range = {4.3, JPSI_LAMBDA_THRESHOLD+0.01, 4.4};
	std::vector<float> gamma_range = {0.08, 0.0001, 0.3};
	std::vector<float> background_fraction = {0.1, 0, 1};
	std::vector<vector<float>> d0_params = {{JPSI_LAMBDA_THRESHOLD}, {0.130852, 0.0, 10.0}, {2.07974, 0.0, 10.0}, {0.00482206, -1.0, 10.0}};
	unsigned int bin_number = 45;
	
	float mean_value = 4.319;
	float gamma_value = 0.035;
	
	fit_breit_wigner(data_path, ntuple_name, variable_name, variable_title, variable_description, variable_range, mean_range, gamma_range, d0_params, background_fraction, bin_number);
}

void fit_pentaquark_breit_wigner_fija(){
	std::vector<float> variable_range = {JPSI_LAMBDA_THRESHOLD+0.004, 4.7};
	float mean_value = 4.319;
	float gamma_value = 0.035;
	std::vector<float> background_fraction = {0.1, 0, 1};
	std::vector<vector<float>> d0_params = {{JPSI_LAMBDA_THRESHOLD}, {-10, -0.75, 10}, {-100, 1.00, 10}, {-10, -0.40, 10}};
	unsigned int bin_number = 45;
	
	fit_breit_wigner_fija(data_path, ntuple_name, variable_name, variable_description, variable_range, mean_value, gamma_value, d0_params, background_fraction, bin_number);
}

void fit_pentaquark_gauss_fija(){
	std::vector<float> variable_range = {JPSI_LAMBDA_THRESHOLD+0.004, 4.7};
	float mean_value = 4.319;
	float sigma_value = 0.0156;
	std::vector<float> background_fraction = {0.1, 0, 1};
	std::vector<vector<float>> d0_params = {{JPSI_LAMBDA_THRESHOLD}, {-10, -0.75, 10}, {-100, 1.00, 10}, {-10, -0.40, 10}};
	unsigned int bin_number = 45;
	
	fit_gauss_fija(data_path, ntuple_name, variable_name, variable_description, variable_range, mean_value, sigma_value, d0_params, background_fraction, bin_number);
}

//fit_pentaquark_gauss(0.275, 2.7, 0.002)
void fit_pentaquark_gauss(float c1, float c2, float b){
	std::vector<float> variable_range = {JPSI_LAMBDA_THRESHOLD+0.004, 4.7};
	std::vector<float> mean_range = {4.3, JPSI_LAMBDA_THRESHOLD+0.01, 4.4};
	std::vector<float> sigma_range = {0.012, 0.001, 1};
	std::vector<float> background_fraction = {0.1, 0, 1};
	std::vector<vector<float>> d0_params = {{JPSI_LAMBDA_THRESHOLD}, {c1, 0.0, 10.0}, {c2, 0.0, 10.0}, {b, -1.0, 10.0}};
	unsigned int bin_number = 45;
	
	fit_gauss(data_path, ntuple_name, variable_name, variable_title, variable_description, variable_range, mean_range, sigma_range, d0_params, background_fraction, bin_number);
}

//para pruebas fit_pentaquark_ruido(0.130852, 2.07974, 0.00482206)
void fit_pentaquark_ruido(float c1, float c2, float b){
	std::vector<float> variable_range = {JPSI_LAMBDA_THRESHOLD + 0.004, 5.4};
	std::vector<float> d0_params = {JPSI_LAMBDA_THRESHOLD, c1, c2, b};
	unsigned int bin_number = 45;
	 
	fit_polinomio_d0(data_path, ntuple_name, variable_name, variable_title, variable_description, variable_range, d0_params, bin_number);
}

void pentaquark_distribucion_masa(float lower_limit, float upper_limit){
	std::vector<float> variable_range = {lower_limit, upper_limit};
	unsigned int bin_number = (variable_range[1]-variable_range[0])/MEV_PER_BIN;
	
	solo_datos(data_path, ntuple_name, variable_name, variable_title, variable_description, variable_range, bin_number);
}
