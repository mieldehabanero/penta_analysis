//
//  operaciones.h
//  
//
//  Created by Ricardo Zamora on 28/1/18.
//

#ifndef operaciones_h
#define operaciones_h

#include <cmath>

float norma(std::vector<float>vector);
float norma_dos(float x1, float x2);
float norma_tres(float x1, float x2, float x3);
float calcula_pt(float px, float py);
float delta_pt_pt_calculado(float pt, float pt_calculado);
float calcula_energia_relativista(float m, float p);
float calcula_energia_relativista_nueva(float mass, std::vector<float>p);
float calcula_masa_invariante(float e, std::vector<float>p);
float calcula_error(float valor_dado, float valor_calculado);
float calcula_desplazamiento(std::vector<float>vtx1, std::vector<float>vtx2);
float calcula_L_xy_magnitud(std::vector<float>d_xy_vtx, std::vector<float>pt_gorro_vtx);
float calcula_sigma (std::vector<float>l_xy_E);
float calcula_cos_alpha(float L_xy_magnitude, std::vector<float>d_xy);
float calcula_sigma_nuevo(std::vector<float>l_xy_E, std::vector<float>jpsi_d_xy);
float calcula_D_xy_magnitud_nuevo(std::vector<float>d_xy_vtx);
float calcula_cos_alpha_nuevo(std::vector<float>d_xy, std::vector<float>p_xy);

#endif /* operaciones_h */
