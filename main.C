#define main_cxx
// The class definition in main.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("main.C")
// root> T->Process("main.C","some options")
// root> T->Process("main.C+")
//


#include "main.h"

void main::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
}

void main::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
	
	lb_mass_histo = new TH1F("lb_mass_histo","m(J/#psi#lambda_{0}) (GeV)", 100, 5.4, 5.84);
	mumu_mass_histo = new TH1F("mumu_mass_histo","J/#psi Mass (GeV)", 100, 2.95, 3.25);
	pionproton_mass_histo = new TH1F("pionproton_mass_histo","#lambda_{0} Mass (GeV)", 100, 1.1, 1.13);
	pionpion_mass_histo = new TH1F("pionpion_mass_histo","m(#pi^{-}#pi^{+}) (GeV)", 100, 0.44, 0.56);
	lb_mass_histo_2 = new TH1F("lb_mass_histo_2","m(J/#psi#lambda_{0}) (GeV)", 100, 4.2, 5.84);
	
	tree_candidatos_lambda_b = new TTree("candidatos_lambda_b", "Datos 2012 filtrados");
	tree_candidatos_lambda_b->Branch("lambda_b_mass", &lambda_b_invariant_mass, "lambda_b_mass/F");
	tree_candidatos_lambda_b->Branch("lambda_0_mass", &lambda_0_invariant_mass, "lambda_0_mass/F");
	tree_candidatos_lambda_b->Branch("ks_mass", &k_short_invariant_mass, "ks_mass/F");
	tree_candidatos_lambda_b->Branch("jpsi_b_mass", &jpsi_invariant_mass, "jpsi_mass/F");
	
	tree_candidatos_lambda_0 = new TTree("candidatos_lambda_0", "Candidatos Lambda 0");
	tree_candidatos_lambda_0->Branch("lambda_0_mass", &lambda_0_invariant_mass, "lambda_0_mass/F");
	
	tree_candidatos_jpsi = new TTree("candidatos_jpsi", "Candidatos J/Psi");
	tree_candidatos_jpsi->Branch("jpsi_mass", &jpsi_temp_mass, "jpsi_mass/F");
	
	tree_candidatos_ks = new TTree("candidatos_ks", "Candidatos Ks");
	tree_candidatos_ks->Branch("ks_mass", &k_short_invariant_mass, "ks_mass/F");
	
	tree_generador_ruido = new TTree("generador_ruido", "Ruido con eventos mezclados");
	tree_generador_ruido->Branch("B_J_px", &jpsi_p[0], "B_J_px/F");
	tree_generador_ruido->Branch("B_J_py", &jpsi_p[1], "B_J_py/F");
	tree_generador_ruido->Branch("B_J_pz", &jpsi_p[2], "B_J_pz/F");
	tree_generador_ruido->Branch("B_J_e", &jpsi_e, "B_J_e/F");
	tree_generador_ruido->Branch("B_lamb_px", &lambda_0_p[0], "B_lamb_px/F");
	tree_generador_ruido->Branch("B_lamb_py", &lambda_0_p[1], "B_lamb_py/F");
	tree_generador_ruido->Branch("B_lamb_pz", &lambda_0_p[2], "B_lamb_pz/F");
	tree_generador_ruido->Branch("B_lamb_e", &lambda_0_e, "B_lamb_e/F");
	
	fOutput->Add(mumu_mass_histo);
	fOutput->Add(lb_mass_histo);
	fOutput->Add(pionproton_mass_histo);
	fOutput->Add(pionpion_mass_histo);
	fOutput->Add(lb_mass_histo_2);
	
	fOutput->Add(tree_candidatos_lambda_b);
	fOutput->Add(tree_candidatos_lambda_0);
	fOutput->Add(tree_candidatos_jpsi);
	fOutput->Add(tree_candidatos_ks);
	fOutput->Add(tree_generador_ruido);
}

Bool_t main::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

	fReader.SetLocalEntry(entry);
		
	jpsi_cuts = new JPsiCuts();
	lambda_cuts = new LambdaCuts();
	kaon_cuts = new KaonCuts();
	lambda_b_cuts = new LambdaBCuts();
	
	for(unsigned int i = 0; i < *nB; i++){
		muon_1 = new MuonCandidate(B_J_px1.At(i), B_J_py1.At(i), B_J_pz1.At(i));
		muon_2 = new MuonCandidate(B_J_px2.At(i), B_J_py2.At(i), B_J_pz2.At(i));
		
		jpsi = new JPsiCandidate(muon_1, muon_2);
		jpsi->setProbability(B_J_Prob.At(i));
		
		//Vector desde el vértice primario al vértice de decaimiento del J/Psi: d_xy
		//No se usa z, porque se elimina en el producto punto con pt
		jpsi->setDecayDistance(JDecayVtxX.At(i)-*priVtxX, JDecayVtxY.At(i)-*priVtxY);
		jpsi->setDecayDistanceError(JDecayVtxXE.At(i), JDecayVtxYE.At(i), *priVtxXE, *priVtxYE);
		
		//Se le aplicó una correción a los momentos de los muones para que den exactamente la masa del J/Psi
		es_candidato_j_psi = jpsi_cuts->applyCuts(jpsi);

		//Si es un candidato a J/Psi, continúa
		if(es_candidato_j_psi){
			jpsi_temp_mass = B_J_mass.At(i);
			tree_candidatos_jpsi->Fill();
			mumu_mass_histo->Fill(jpsi_temp_mass);
		}

		//Estos valores se calculan aquí porque se necesitan en calculos ajenos al Lambda_0
		charged_p1_magnitude = norma_tres(B_lamb_px1.At(i), B_lamb_py1.At(i), B_lamb_pz1.At(i));
		charged_p2_magnitude = norma_tres(B_lamb_px2.At(i), B_lamb_py2.At(i), B_lamb_pz2.At(i));

		//Se distingue entre pión y protón (p_p > p_π)
		if (charged_p1_magnitude > charged_p2_magnitude){
			proton = new ProtonCandidate(B_lamb_px1.At(i), B_lamb_py1.At(i), B_lamb_pz1.At(i));
			pion = new PionCandidate(B_lamb_px2.At(i), B_lamb_py2.At(i), B_lamb_pz2.At(i));
			pion_mismatched = new PionCandidate(B_lamb_px1.At(i), B_lamb_py1.At(i), B_lamb_pz1.At(i));
		} else {
			proton = new ProtonCandidate(B_lamb_px2.At(i), B_lamb_py2.At(i), B_lamb_pz2.At(i));
			pion = new PionCandidate(B_lamb_px1.At(i), B_lamb_py1.At(i), B_lamb_pz1.At(i));
			pion_mismatched = new PionCandidate(B_lamb_px2.At(i), B_lamb_py2.At(i), B_lamb_pz2.At(i));
		}

		//Vector desde el vértice primario al vértice de decaimiento del Lambda_0: d_xy
		//No se usa z, porque se elimina en el producto punto con pt
		lambda = new LambdaCandidate(proton, pion);
		lambda->setProbability(B_lamb_Prob.At(i));
		lambda->setDecayDistance(VDecayVtxX.At(i)-*priVtxX, VDecayVtxY.At(i)-*priVtxY);
		lambda->setDecayDistanceError(VDecayVtxXE.At(i), VDecayVtxYE.At(i), *priVtxXE, *priVtxYE);
		lambda->setChi2(B_lamb_chi2.At(i));
		
		k_short = new KaonCandidate(pion, pion_mismatched);

		es_candidato_lambda0 = lambda_cuts->applyCuts(lambda);

		es_candidato_kaon = kaon_cuts->applyCuts(k_short);
		pionpion_mass_histo->Fill(k_short->getInvariantMass());
		tree_candidatos_ks->Fill();

		//Si es un candidato a Lambda_0, continúa
		if(!es_candidato_kaon && es_candidato_lambda0){
			tree_candidatos_lambda_0->Fill();
			pionproton_mass_histo->Fill(lambda->getInvariantMass());
		}

		//Checa que sea un candidate de Lambda^b_0
		//Valores calculados en el GRID
		lambda_b = new LambdaBCandidate(jpsi, lambda);
		lambda_b->setProbability(B_Prob.At(i));

		es_candidato_lambda_b = lambda_b_cuts->applyCuts(lambda_b);

		if(es_candidato_j_psi && !es_candidato_kaon && es_candidato_lambda0 && es_candidato_lambda_b){
			lb_mass_histo->Fill(lambda_b->getInvariantMass());
			lb_mass_histo_2->Fill(lambda_b->getInvariantMass());
			tree_candidatos_lambda_b->Fill();
			tree_generador_ruido->Fill();
		}
		
	}

   return kTRUE;
}

void main::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void main::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
	
	lb_mass_histo = dynamic_cast<TH1F*>(fOutput->FindObject("lb_mass_histo"));
	mumu_mass_histo = dynamic_cast<TH1F*>(fOutput->FindObject("mumu_mass_histo"));
	pionproton_mass_histo = dynamic_cast<TH1F*>(fOutput->FindObject("pionproton_mass_histo"));
	pionpion_mass_histo = dynamic_cast<TH1F*>(fOutput->FindObject("pionpion_mass_histo"));
	lb_mass_histo_2 = dynamic_cast<TH1F*>(fOutput->FindObject("lb_mass_histo_2"));
	
	tree_candidatos_lambda_b = dynamic_cast<TTree*>(fOutput->FindObject("candidatos_lambda_b"));
	tree_candidatos_lambda_0 = dynamic_cast<TTree*>(fOutput->FindObject("candidatos_lambda_0"));
	tree_candidatos_jpsi = dynamic_cast<TTree*>(fOutput->FindObject("candidatos_jpsi"));
	tree_candidatos_ks = dynamic_cast<TTree*>(fOutput->FindObject("candidatos_ks"));
	tree_generador_ruido = dynamic_cast<TTree*>(fOutput->FindObject("generador_ruido"));
	
	TCanvas *c1 = new TCanvas("lb_mass_calculada","#lambda^{b}_{0} Mass (GeV)",200,10,700,500);
	TCanvas *c2 = new TCanvas("jpsi_mass_calculada","J/#psi Mass (GeV)",200,10,700,500);
	TCanvas *c3 = new TCanvas("l0_mass_calculada","#lambda_{0} Mass (GeV)",200,10,700,500);
	TCanvas *c4 = new TCanvas("k^0_s_mass_calculada","#K^{d}_{0} Mass (GeV)",200,10,700,500);
	TCanvas *c5 = new TCanvas("lb_mass_calculada_2","#lambda^{b}_{0} Mass (GeV)",200,10,700,500);
	
	c1->cd();
	gPad->SetTicks(1, 1);
	lb_mass_histo->Draw();
	c1->Print("Resultados/Histogramas/lb_mass_calculada.png");
	c1->Print("Resultados/Histogramas/lb_mass_calculada.root");
	
	c2->cd();
	gPad->SetTicks(1, 1);
	mumu_mass_histo->Draw();
	c2->Print("Resultados/Histogramas/jpsi_mass_calculada.png");
	c2->Print("Resultados/Histogramas/jpsi_mass_calculada.root");
	
	c3->cd();
	gPad->SetTicks(1, 1);
	pionproton_mass_histo->Draw();
	c3->Print("Resultados/Histogramas/l0_mass_calculada.png");
	c3->Print("Resultados/Histogramas/l0_mass_calculada.root");
	
	c4->cd();
	gPad->SetTicks(1, 1);
	pionpion_mass_histo->Draw();
	c4->Print("Resultados/Histogramas/pionpion_mass.png");
	c4->Print("Resultados/Histogramas/pionpion_mass.root");
	
	c5->cd();
	gPad->SetTicks(1, 1);
	lb_mass_histo_2->Draw();
	c5->Print("Resultados/Histogramas/lb_mass_extendida.png");
	c5->Print("Resultados/Histogramas/lb_mass_extendida.root");
	
	TFile candidatos_lambda_b("Resultados/candidatos_lambda_b.root", "RECREATE");
	tree_candidatos_lambda_b->Write();
	candidatos_lambda_b.Close();
	
	TFile candidatos_lambda_0("Resultados/candidatos_lambda_0.root", "RECREATE");
	tree_candidatos_lambda_0->Write();
	candidatos_lambda_0.Close();
	
	TFile candidatos_jpsi("Resultados/candidatos_jpsi.root", "RECREATE");
	tree_candidatos_jpsi->Write();
	candidatos_jpsi.Close();
	
	TFile candidatos_ks("Resultados/candidatos_ks.root", "RECREATE");
	tree_candidatos_ks->Write();
	candidatos_ks.Close();
	
	TFile generador_ruido("Resultados/generador_ruido.root", "RECREATE");
	tree_generador_ruido->Write();
	generador_ruido.Close();
	
}
