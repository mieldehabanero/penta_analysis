//
//  fit.h
//  
//
//  Created by Ricardo Zamora on 30/4/18.
//

#ifndef fit_h
#define fit_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <RooFit.h>
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooGenericPdf.h"
#include "RooAddPdf.h"
#include "RooPolynomial.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
#include "RooBreitWigner.h"
#include "RooHist.h"
#include "RooFitResult.h"
#include "TMath.h"
#include <algorithm>

using namespace std;
using namespace RooFit;

void fit_double_gauss(std::string data_path, std::string ntuple_name, std::string variable_name, std::string variable_title, std::string variable_description, std::vector<float> variable_range, std::vector<float> mean_range, std::vector<float> sigma1_range, std::vector<float> sigma2_range, std::vector<float> sigma_fraction, std::vector<vector<float>> poly_range, std::vector<float> background_fraction, unsigned int bin_number);

void fit_breit_wigner(std::string data_path, std::string ntuple_name, std::string variable_name, std::string variable_title, std::string variable_description, std::vector<float> variable_range, std::vector<float> mean_range, std::vector<float> gamma_range, std::vector<vector<float>> d0_range, std::vector<float> background_fraction, unsigned int bin_number);

void fit_breit_wigner_fija(std::string data_path, std::string ntuple_name, std::string variable_name, std::string variable_description, std::vector<float> variable_range, float mean_value, float gamma_value, std::vector<vector<float>> d0_params, std::vector<float> background_fraction, unsigned int bin_number);

void fit_gauss_fija(std::string data_path, std::string ntuple_name, std::string variable_name, std::string variable_description, std::vector<float> variable_range, float mean_value, float sigma_value, std::vector<vector<float>> d0_params, std::vector<float> background_fraction, unsigned int bin_number);

void fit_gauss(std::string data_path, std::string ntuple_name, std::string variable_name, std::string variable_title, std::string variable_description, std::vector<float> variable_range, std::vector<float> mean_range, std::vector<float> sigma_range, std::vector<vector<float>> d0_params, std::vector<float> background_fraction, unsigned int bin_number);

void fit_polinomio_d0(std::string data_path, std::string ntuple_name, std::string variable_name, std::string variable_title, std::string variable_description, std::vector<float> variable_range, std::vector<float> d0_params, unsigned int bin_number);

void solo_datos(std::string data_path, std::string ntuple_name, std::string variable_name, std::string variable_title, std::string variable_description, std::vector<float> variable_range, unsigned int bin_number);

#endif /* fit_h */
