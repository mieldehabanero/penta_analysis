#define generador_ruido_cxx
#include "generador_ruido.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "Librerias/constantes.h"
#include "Librerias/operaciones.h"
#include <iostream>
#include <random>

float aplica_cortes(std::vector<float> jpsi_cuatrivector, std::vector<float> lambda_0_cuatrivector);
void generador_ruido::Loop()
{
//   In a ROOT session, you can do:
//      root> .L generador_ruido.C
//      root> generador_ruido t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, push_back statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

	TCanvas *c1 = new TCanvas("lb_mass_calculada","#lambda^{b}_{0} Mass (GeV)",200,10,700,500);
	TH1F *lb_mass_histo = new TH1F("ruido_histo","m(J/#psi#lambda_{0}) (GeV)", 100, 4.2, 5.84);
	TTree *tree_candidatos_lambda_b = new TTree("candidatos_lambda_b", "Ruido Generado con eventos combinados");
	
	std::vector<float> jpsi_cuatrivector, lambda_0_cuatrivector;
	std::vector<vector<float>> jpsi_candidates, lambda_0_candidates;
	int num_events, i, j;
	
	Long64_t jentry, ientry, nbytes = 0, nb = 0;
	
   for(jentry = 0; jentry < nentries; jentry++) {
       ientry = LoadTree(jentry);
	   
	   jpsi_cuatrivector = {B_J_px, B_J_py, B_J_pz, B_J_e};
	   lambda_0_cuatrivector = {B_lamb_px, B_lamb_py, B_lamb_pz, B_lamb_e};
	   
	   float es_candidato = aplica_cortes(jpsi_cuatrivector, lambda_0_cuatrivector);
	   if (es_candidato){
		   jpsi_candidates.push_back(jpsi_cuatrivector);
	   }
	   
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
	
	nbytes = 0, nb = 0;
	for(jentry = 0; jentry < nentries; jentry++) {
		ientry = LoadTree(jentry);
		
		jpsi_cuatrivector = {B_J_px, B_J_py, B_J_pz, B_J_e};
		lambda_0_cuatrivector = {B_lamb_px, B_lamb_py, B_lamb_pz, B_lamb_e};
		
		float es_candidato = aplica_cortes(jpsi_cuatrivector, lambda_0_cuatrivector);
		if (es_candidato){
			lambda_0_candidates.push_back(lambda_0_cuatrivector);
		}
		
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;
	}
	
	if(jpsi_candidates.size() < lambda_0_candidates.size()){
		cout << jpsi_candidates.size() << endl;
		cout << lambda_0_candidates.size() << endl;
		num_events = jpsi_candidates.size();
	} else {
		num_events = lambda_0_candidates.size();
	}
	
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, num_events-1); // define the range
	
	for (i = 0; i < num_events; i++) {
		j = distr(eng); //genera un numero al azar en el rango de num_events

		float es_candidato = aplica_cortes(jpsi_candidates[i], lambda_0_candidates[j]);
//		cout << es_candidato << endl;
		if (es_candidato){
			lb_mass_histo->Fill(es_candidato);
		}
	}
	
	TFile candidatos_lambda_b("Resultados/ruido_generado.root", "RECREATE");
	tree_candidatos_lambda_b->Write();
	candidatos_lambda_b.Close();
	c1->cd();
	gPad->SetTicks(1, 1);
	lb_mass_histo->Draw();
}

float aplica_cortes(std::vector<float> jpsi_cuatrivector, std::vector<float> lambda_0_cuatrivector){
	float jpsi_mass, lambda_b_p_magnitude, lambda_b_pt_magnitude, lambda_0_mass, lambda_b_mass;
	std::vector<float> lambda_b_cuatrivector;

	lambda_b_cuatrivector = {jpsi_cuatrivector[0] + lambda_0_cuatrivector[0], jpsi_cuatrivector[1] + lambda_0_cuatrivector[1], jpsi_cuatrivector[2] + lambda_0_cuatrivector[2], jpsi_cuatrivector[3] + lambda_0_cuatrivector[3]};
	lambda_b_p_magnitude = sqrt(pow(lambda_b_cuatrivector[0], 2) + pow(lambda_b_cuatrivector[1], 2) + pow(lambda_b_cuatrivector[2], 2));
	lambda_b_mass = sqrt(pow(lambda_b_cuatrivector[3], 2) - pow(lambda_b_p_magnitude,2));
	
	lambda_b_pt_magnitude = sqrt(pow(lambda_b_cuatrivector[0], 2) + pow(lambda_b_cuatrivector[1], 2));
	
	 if (lambda_b_pt_magnitude >= LAMBDA_B_PT_CUT && LAMBDA_B_MASS_LOWER_LIMIT < lambda_b_mass && lambda_b_mass < LAMBDA_B_MASS_UPPER_LIMIT){
//	if (lambda_b_pt_magnitude >= LAMBDA_B_PT_CUT){
		 //return 1;
		 return lambda_b_mass;
	 }
	return 0.0;
}
