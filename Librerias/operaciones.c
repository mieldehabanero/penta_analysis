//
//  operaciones.c
//  
//
//  Created by Ricardo Zamora on 28/1/18.
//

#include "operaciones.h"

float norma(std::vector<float>vector){
	
	int n = sizeof(vector)/sizeof(vector[0]);
	float norma = 0;
	
	for(int i = 0; i < n; i++){
		norma += pow(vector[i], 2.0);
	}
	norma = sqrt(norma);
	return norma;
}

float norma_dos(float x1, float x2){
	float cuadrado_1 = x1*x1;
	float cuadrado_2 = x2*x2;
	return sqrt(cuadrado_1 + cuadrado_2);
}

float norma_tres(float x1, float x2, float x3){
	float cuadrado_1 = x1*x1;
	float cuadrado_2 = x2*x2;
	float cuadrado_3 = x3*x3;
	return sqrt(cuadrado_1 + cuadrado_2 + cuadrado_3);
}

float calcula_pt(float px, float py) {
	float pt_calculado = norma_dos(px, py);
	return pt_calculado;
}

float delta_pt_pt_calculado(float pt, float pt_calculado) {
	float delta = pt-pt_calculado;
	return delta;
}

float calcula_energia_relativista(float m, float p){
	return sqrt(m*m + p*p);
}

float calcula_energia_relativista_nueva(float mass, std::vector<float>p){
	float p_magnitude = norma_tres(p[0], p[1], p[2]);
	float e = sqrt(mass*mass + p_magnitude*p_magnitude);
	return e;
}

float calcula_masa_invariante(float e, std::vector<float>p){
	float p_magnitude = norma_tres(p[0], p[1], p[2]);
	return sqrt(e*e - p_magnitude*p_magnitude);
}

float calcula_error(float valor_dado, float valor_calculado){
	return (valor_dado - valor_calculado)/valor_dado * 100;
}

float calcula_desplazamiento(std::vector<float>vtx1, std::vector<float>vtx2){
	float desplazamiento_x = vtx2[0] - vtx1[0];
	float desplazamiento_y = vtx2[1] - vtx1[1];
	float desplazamiento_z = vtx2[2] - vtx1[2];
	float magnitud_desplazamiento = norma_tres(desplazamiento_x, desplazamiento_y, desplazamiento_z);
	return magnitud_desplazamiento;
}


float calcula_L_xy_magnitud(std::vector<float>d_xy_vtx, std::vector<float>pt_gorro_vtx){
	float L_xy = (d_xy_vtx[0]*pt_gorro_vtx[0] + d_xy_vtx[1]*pt_gorro_vtx[1]);
	return L_xy;
}

float calcula_D_xy_magnitud_nuevo(std::vector<float>d_xy_vtx){
	float d_xy_norma = norma_dos(d_xy_vtx[0], d_xy_vtx[1]);
	return d_xy_norma;
}

float calcula_sigma(std::vector<float>l_xy_E) {
	float sigma = sqrt(l_xy_E[0]*l_xy_E[0] + l_xy_E[1]*l_xy_E[1] + l_xy_E[2]*l_xy_E[2] + l_xy_E[3]*l_xy_E[3]);
	return sigma;
}

float calcula_sigma_nuevo(std::vector<float>l_xy_E, std::vector<float>jpsi_d_xy) {
	float d_xy_norma = norma_dos(jpsi_d_xy[0], jpsi_d_xy[1]);
	float sigma = sqrt(
						pow(jpsi_d_xy[0], 2) * (pow(l_xy_E[0], 2) + pow(l_xy_E[2], 2))
						+ pow(jpsi_d_xy[1], 2) * (pow(l_xy_E[1], 2) + pow(l_xy_E[3], 2)));
	sigma = sigma/d_xy_norma;
	return sigma;
}

float calcula_cos_alpha(float L_xy_magnitude, std::vector<float>d_xy){
	float d_xy_magnitude = norma_dos(d_xy[0], d_xy[1]);
	return L_xy_magnitude/d_xy_magnitude;
}

float calcula_cos_alpha_nuevo(std::vector<float>d_xy, std::vector<float>p_xy){
	float p_xy_magnitud = norma_dos(p_xy[0], p_xy[1]);
	float d_xy_magnitude = norma_dos(d_xy[0], d_xy[1]);
	float dot_product = p_xy[0]*d_xy[0] + d_xy[1]*p_xy[1];
	
	return dot_product/(d_xy_magnitude * p_xy_magnitud);
}
