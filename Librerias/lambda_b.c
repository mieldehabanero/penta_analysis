//
//  lambda_b.c
//  
//
//  Created by Ricardo Zamora on 28/1/18.
//

#include <stdio.h>
#include <string>
#include "lambda_b.h"
#include "operaciones.h"
#include "fit.h"

int aplica_cortes_lambda_b(float lb_pt, float lb_prob, float lb_mass);
int corte_pt_lambda_b(float lb_pt);
int corte_prob_lambda_b(float prob);
int corte_masa_lambda_b(float masa);

int es_candidato_lambda_b(std::vector<float>jpsi_p, std::vector<float>lambda_0_p, float lb_prob, float lb_mass) {
	
	float lambda_b_p[3] = {jpsi_p[0] + lambda_0_p[0], jpsi_p[1] + lambda_0_p[1], jpsi_p[2] + lambda_0_p[2]};
	float lambda_b_pt[3] = {lambda_b_p[0], lambda_b_p[1]};
	float lambda_b_pt_magnitude = norma_dos(lambda_b_pt[0], lambda_b_pt[1]);
	
	int es_candidato = aplica_cortes_lambda_b(lambda_b_pt_magnitude, lb_prob, lb_mass);
	return es_candidato;
}

int aplica_cortes_lambda_b(float lb_pt, float lb_prob, float lb_mass) {
	//Se calcula si el pt están dentro del rango (pL_b > 10GeV)
	int pasa_corte_pt = corte_pt_lambda_b(lb_pt);
	if(!pasa_corte_pt) {
		return 0;
	}
	
	//Se calcula si la probabilidad de un vertice común es >??
	int pasa_corte_prob = corte_prob_lambda_b(lb_prob);
	if(!pasa_corte_prob) {
		return 0;
	}
	
	//Se calcula si la masa del Lambda b esta dentro del rango (5.40GeV < M_jPsi < 5.84GeV)
	int pasa_corte_masa = corte_masa_lambda_b(lb_mass);
	if(!pasa_corte_masa) {
		return 0;
	}
	
	return 1;
}


//Checa si el pt del Lambda b esta en el rango requerido, sí = 1, no = 0.
int corte_pt_lambda_b(float lb_pt) {
	//Valores en GeV
	
	//Se calcula si los pts están dentro del rango (pt_π > 0.3GeV, pt_p > 1.0GeV, y pt_pπ > 1.3GeV)
	if (lb_pt > LAMBDA_B_PT_CUT){
		return 1;
	}
	return 0;
}

//Checa si la probabilidad de que µ+µ- vengan del mismo vértice, sí = 1, no = 0.
int corte_prob_lambda_b(float prob) {
	//Valores en GeV
	
	//Se calcula si la probabilidad es mayor al cuttoff
	if (prob > LAMBDA_B_PROB_CUT){
		return 1;
	}
	return 0;
}

//Checa si la masa del Lambda b esta en el rango requerido, sí = 1, no = 0.
//masa esta en MeV
int corte_masa_lambda_b(float masa) {
	//Valores en GeV
	if (LAMBDA_B_MASS_LOWER_LIMIT < masa && masa < LAMBDA_B_MASS_UPPER_LIMIT){
		return 1;
	}
	return 0;
}

void fit_lambda_b(){
	std::string data_path = "Resultados/candidatos_lambda_b.root";
	std::string ntuple_name = "candidatos_lambda_b";
	std::string variable_name = "lambda_b_mass";
	std::string variable_title = "J/#Psi #Lambda Mass";
	std::string variable_description = "m(J/#Psi #Lambda) [GeV]";
	std::vector<float> variable_range = {5.4, 5.84};
	std::vector<float> mean_range = {5.619, 5.4, 5.84};
	std::vector<float> sigma1_range = {0.012, 0.001, 1};
	std::vector<float> sigma2_range = {0.030, 0.001, 1};
	std::vector<float> sigma_fraction = {0.578, 0., 1.};
	std::vector<float> background_fraction = {0.525, 0., 1.};
	std::vector<vector<float>> poly_range = {{-0.135, -10, 10}};
	unsigned int bin_number = 45;
	
	fit_double_gauss(data_path, ntuple_name, variable_name, variable_title, variable_description, variable_range, mean_range, sigma1_range, sigma2_range, sigma_fraction, poly_range, background_fraction, bin_number);
}
