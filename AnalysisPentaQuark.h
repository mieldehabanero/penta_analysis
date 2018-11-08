//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Apr 22 13:12:56 2018 by ROOT version 6.13/02
// from TTree ntuple/Bs->J/psi lambda ntuple
// found on file: Datos/run_2012a.root
//////////////////////////////////////////////////////////

#ifndef AnalysisPentaQuark_h
#define AnalysisPentaQuark_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <vector>
#include <string>

#include "Librerias/constantes.h"
#include "Librerias/operaciones.h"

#include "Librerias/Particles/MuonCandidate.hpp"
#include "Librerias/Particles/JPsiCandidate.hpp"
#include "Librerias/Particles/ProtonCandidate.hpp"
#include "Librerias/Particles/PionCandidate.hpp"
#include "Librerias/Particles/KaonCandidate.hpp"
#include "Librerias/Particles/LambdaCandidate.hpp"
#include "Librerias/Particles/LambdaBCandidate.hpp"
#include "Librerias/Cuts/JPsiCuts.hpp"
#include "Librerias/Cuts/KaonCuts.hpp"
#include "Librerias/Cuts/LambdaCuts.hpp"
#include "Librerias/Cuts/LambdaBCuts.hpp"

class AnalysisPentaQuark : public TSelector {
public :
   TH1F           *lb_mass_histo;
   TH1F           *mumu_mass_histo;
   TH1F           *pionproton_mass_histo;
   TH1F           *pionpion_mass_histo;
   TH1F           *lb_mass_histo_2;
	
	TTree* tree_generador_ruido;
	TTree* tree_candidatos_lambda_b;
	TTree* tree_candidatos_lambda_0;
	TTree* tree_candidatos_jpsi;
	TTree* tree_candidatos_ks;
	
	JPsiCuts *jpsi_cuts;
	LambdaCuts *lambda_cuts;
	KaonCuts *kaon_cuts;
	LambdaBCuts *lambda_b_cuts;
	
	MuonCandidate *muon_1;
	MuonCandidate *muon_2;
	JPsiCandidate *jpsi;
	ProtonCandidate *proton;
	PionCandidate *pion;
	PionCandidate *pion_mismatched;
	LambdaCandidate *lambda;
	KaonCandidate *k_short;
	LambdaBCandidate *lambda_b;
	
	float jpsi_e;
	float lambda_0_e;
	
	std::vector<float> jpsi_p;
	std::vector<float> lambda_0_p;
	float charged_p1_magnitude;
	float charged_p2_magnitude;
	
	float jpsi_temp_mass;
	float jpsi_invariant_mass;
	float lambda_0_invariant_mass;
	float k_short_invariant_mass;
	float lambda_b_invariant_mass;
	
	int es_candidato_j_psi;
	int es_candidato_lambda0;
	int es_candidato_kaon;
	int es_candidato_lambda_b;
	
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<UInt_t> nB = {fReader, "nB"};
   TTreeReaderValue<UInt_t> nMu = {fReader, "nMu"};
   TTreeReaderArray<float> B_mass = {fReader, "B_mass"};
   TTreeReaderArray<float> B_px = {fReader, "B_px"};
   TTreeReaderArray<float> B_py = {fReader, "B_py"};
   TTreeReaderArray<float> B_pz = {fReader, "B_pz"};
   TTreeReaderArray<float> B_lamb_mass = {fReader, "B_lamb_mass"};
   TTreeReaderArray<float> B_lamb_px = {fReader, "B_lamb_px"};
   TTreeReaderArray<float> B_lamb_py = {fReader, "B_lamb_py"};
   TTreeReaderArray<float> B_lamb_pz = {fReader, "B_lamb_pz"};
   TTreeReaderArray<float> B_J_mass = {fReader, "B_J_mass"};
   TTreeReaderArray<float> B_J_px = {fReader, "B_J_px"};
   TTreeReaderArray<float> B_J_py = {fReader, "B_J_py"};
   TTreeReaderArray<float> B_J_pz = {fReader, "B_J_pz"};
   TTreeReaderArray<float> B_lamb_pt1 = {fReader, "B_lamb_pt1"};
   TTreeReaderArray<float> B_lamb_px1 = {fReader, "B_lamb_px1"};
   TTreeReaderArray<float> B_lamb_py1 = {fReader, "B_lamb_py1"};
   TTreeReaderArray<float> B_lamb_pz1 = {fReader, "B_lamb_pz1"};
   TTreeReaderArray<int> B_lamb_charge1 = {fReader, "B_lamb_charge1"};
   TTreeReaderArray<float> B_lamb_pt2 = {fReader, "B_lamb_pt2"};
   TTreeReaderArray<float> B_lamb_px2 = {fReader, "B_lamb_px2"};
   TTreeReaderArray<float> B_lamb_py2 = {fReader, "B_lamb_py2"};
   TTreeReaderArray<float> B_lamb_pz2 = {fReader, "B_lamb_pz2"};
   TTreeReaderArray<int> B_lamb_charge2 = {fReader, "B_lamb_charge2"};
   TTreeReaderArray<float> B_J_pt1 = {fReader, "B_J_pt1"};
   TTreeReaderArray<float> B_J_px1 = {fReader, "B_J_px1"};
   TTreeReaderArray<float> B_J_py1 = {fReader, "B_J_py1"};
   TTreeReaderArray<float> B_J_pz1 = {fReader, "B_J_pz1"};
   TTreeReaderArray<int> B_J_charge1 = {fReader, "B_J_charge1"};
   TTreeReaderArray<float> B_J_pt2 = {fReader, "B_J_pt2"};
   TTreeReaderArray<float> B_J_px2 = {fReader, "B_J_px2"};
   TTreeReaderArray<float> B_J_py2 = {fReader, "B_J_py2"};
   TTreeReaderArray<float> B_J_pz2 = {fReader, "B_J_pz2"};
   TTreeReaderArray<int> B_J_charge2 = {fReader, "B_J_charge2"};
   TTreeReaderArray<float> B_chi2 = {fReader, "B_chi2"};
   TTreeReaderArray<float> B_lamb_chi2 = {fReader, "B_lamb_chi2"};
   TTreeReaderArray<float> B_J_chi2 = {fReader, "B_J_chi2"};
   TTreeReaderArray<float> B_Prob = {fReader, "B_Prob"};
   TTreeReaderArray<float> B_lamb_Prob = {fReader, "B_lamb_Prob"};
   TTreeReaderArray<float> B_J_Prob = {fReader, "B_J_Prob"};
   TTreeReaderValue<Float_t> priVtxX = {fReader, "priVtxX"};
   TTreeReaderValue<Float_t> priVtxY = {fReader, "priVtxY"};
   TTreeReaderValue<Float_t> priVtxZ = {fReader, "priVtxZ"};
   TTreeReaderValue<Float_t> priVtxXE = {fReader, "priVtxXE"};
   TTreeReaderValue<Float_t> priVtxYE = {fReader, "priVtxYE"};
   TTreeReaderValue<Float_t> priVtxZE = {fReader, "priVtxZE"};
   TTreeReaderValue<Float_t> priVtxCL = {fReader, "priVtxCL"};
   TTreeReaderArray<float> pVtxX = {fReader, "pVtxX"};
   TTreeReaderArray<float> pVtxY = {fReader, "pVtxY"};
   TTreeReaderArray<float> pVtxZ = {fReader, "pVtxZ"};
   TTreeReaderArray<float> pVtxXE = {fReader, "pVtxXE"};
   TTreeReaderArray<float> pVtxYE = {fReader, "pVtxYE"};
   TTreeReaderArray<float> pVtxZE = {fReader, "pVtxZE"};
   TTreeReaderArray<float> pVtxCL = {fReader, "pVtxCL"};
   TTreeReaderValue<UInt_t> nVtx = {fReader, "nVtx"};
   TTreeReaderValue<Int_t> run = {fReader, "run"};
   TTreeReaderValue<Int_t> evt = {fReader, "evt"};
   TTreeReaderValue<Int_t> nTrgL = {fReader, "nTrgL"};
   TTreeReaderValue<Int_t> nTrgL1L = {fReader, "nTrgL1L"};
   TTreeReaderArray<Char_t> triggersL = {fReader, "triggersL"};
   TTreeReaderArray<Char_t> triggersL1L = {fReader, "triggersL1L"};
   TTreeReaderArray<std::string> triggersMuPL = {fReader, "triggersMuPL"};
   TTreeReaderArray<std::string> triggersMuML = {fReader, "triggersMuML"};
   TTreeReaderArray<std::string> triggersL1L2_MuPL = {fReader, "triggersL1L2_MuPL"};
   TTreeReaderArray<std::string> triggersL1L2_MuML = {fReader, "triggersL1L2_MuML"};
   TTreeReaderArray<float> priRfVtxX = {fReader, "priRfVtxX"};
   TTreeReaderArray<float> priRfVtxY = {fReader, "priRfVtxY"};
   TTreeReaderArray<float> priRfVtxZ = {fReader, "priRfVtxZ"};
   TTreeReaderArray<float> priRfVtxXE = {fReader, "priRfVtxXE"};
   TTreeReaderArray<float> priRfVtxYE = {fReader, "priRfVtxYE"};
   TTreeReaderArray<float> priRfVtxZE = {fReader, "priRfVtxZE"};
   TTreeReaderArray<float> priRfVtxCL = {fReader, "priRfVtxCL"};
   TTreeReaderArray<int> priRfNTrkDif = {fReader, "priRfNTrkDif"};
   TTreeReaderArray<float> bDecayVtxX = {fReader, "bDecayVtxX"};
   TTreeReaderArray<float> bDecayVtxY = {fReader, "bDecayVtxY"};
   TTreeReaderArray<float> bDecayVtxZ = {fReader, "bDecayVtxZ"};
   TTreeReaderArray<double> bDecayVtxXE = {fReader, "bDecayVtxXE"};
   TTreeReaderArray<double> bDecayVtxYE = {fReader, "bDecayVtxYE"};
   TTreeReaderArray<double> bDecayVtxZE = {fReader, "bDecayVtxZE"};
   TTreeReaderArray<float> bResMass = {fReader, "bResMass"};
   TTreeReaderArray<float> bResVtxCL = {fReader, "bResVtxCL"};
   TTreeReaderArray<float> bResPx = {fReader, "bResPx"};
   TTreeReaderArray<float> bResPy = {fReader, "bResPy"};
   TTreeReaderArray<float> bResPz = {fReader, "bResPz"};
   TTreeReaderArray<float> bResDecayVtxX = {fReader, "bResDecayVtxX"};
   TTreeReaderArray<float> bResDecayVtxY = {fReader, "bResDecayVtxY"};
   TTreeReaderArray<float> bResDecayVtxZ = {fReader, "bResDecayVtxZ"};
   TTreeReaderArray<float> bResDecayVtxXE = {fReader, "bResDecayVtxXE"};
   TTreeReaderArray<float> bResDecayVtxYE = {fReader, "bResDecayVtxYE"};
   TTreeReaderArray<float> bResDecayVtxZE = {fReader, "bResDecayVtxZE"};
   TTreeReaderArray<float> VDecayVtxX = {fReader, "VDecayVtxX"};
   TTreeReaderArray<float> VDecayVtxY = {fReader, "VDecayVtxY"};
   TTreeReaderArray<float> VDecayVtxZ = {fReader, "VDecayVtxZ"};
   TTreeReaderArray<float> VDecayVtxXE = {fReader, "VDecayVtxXE"};
   TTreeReaderArray<float> VDecayVtxYE = {fReader, "VDecayVtxYE"};
   TTreeReaderArray<float> VDecayVtxZE = {fReader, "VDecayVtxZE"};
   TTreeReaderArray<float> JDecayVtxX = {fReader, "JDecayVtxX"};
   TTreeReaderArray<float> JDecayVtxY = {fReader, "JDecayVtxY"};
   TTreeReaderArray<float> JDecayVtxZ = {fReader, "JDecayVtxZ"};
   TTreeReaderArray<float> JDecayVtxXE = {fReader, "JDecayVtxXE"};
   TTreeReaderArray<float> JDecayVtxYE = {fReader, "JDecayVtxYE"};
   TTreeReaderArray<float> JDecayVtxZE = {fReader, "JDecayVtxZE"};
   TTreeReaderArray<int> JmuOL = {fReader, "JmuOL"};
   TTreeReaderArray<float> mumD0 = {fReader, "mumD0"};
   TTreeReaderArray<float> mumD0E = {fReader, "mumD0E"};
   TTreeReaderArray<float> mumC2 = {fReader, "mumC2"};
   TTreeReaderArray<int> mumCat = {fReader, "mumCat"};
   TTreeReaderArray<int> mumME1 = {fReader, "mumME1"};
   TTreeReaderArray<int> mumAngT = {fReader, "mumAngT"};
   TTreeReaderArray<int> mumNHits = {fReader, "mumNHits"};
   TTreeReaderArray<int> mumNPHits = {fReader, "mumNPHits"};
   TTreeReaderArray<float> mupD0 = {fReader, "mupD0"};
   TTreeReaderArray<float> mupD0E = {fReader, "mupD0E"};
   TTreeReaderArray<float> mupC2 = {fReader, "mupC2"};
   TTreeReaderArray<int> mupCat = {fReader, "mupCat"};
   TTreeReaderArray<int> mupME1 = {fReader, "mupME1"};
   TTreeReaderArray<int> mupAngT = {fReader, "mupAngT"};
   TTreeReaderArray<int> mupNHits = {fReader, "mupNHits"};
   TTreeReaderArray<int> mupNPHits = {fReader, "mupNPHits"};


   AnalysisPentaQuark(TTree * /*tree*/ =0);
   virtual ~AnalysisPentaQuark() { }
   void    Reset();
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(AnalysisPentaQuark,0);

};

#endif

#ifdef AnalysisPentaQuark_cxx
AnalysisPentaQuark::AnalysisPentaQuark(TTree * /*tree*/)
{
	// Constructor
	
	Reset();
}
//_____________________________________________________________________
void AnalysisPentaQuark::Reset()
{
	// Reset the data members to theit initial value
	JPsiCuts *jpsi_cuts = 0;
	LambdaCuts *lambda_cuts = 0;
	KaonCuts *kaon_cuts = 0;
	LambdaBCuts *lambda_b_cuts = 0;
	
	MuonCandidate *muon_1 = 0;
	MuonCandidate *muon_2 = 0;
	JPsiCandidate *jpsi = 0;
	ProtonCandidate *proton = 0;
	PionCandidate *pion = 0;
	PionCandidate *pion_mismatched = 0;
	LambdaCandidate *lambda = 0;
	KaonCandidate *k_short = 0;
	LambdaBCandidate *lambda_b = 0;
	
	lb_mass_histo = 0;
	mumu_mass_histo = 0;
	pionproton_mass_histo = 0;
	pionpion_mass_histo = 0;
	lb_mass_histo_2 = 0;
	
	tree_candidatos_lambda_b = 0;
	tree_candidatos_lambda_0 = 0;
	tree_candidatos_jpsi = 0;
	tree_candidatos_ks = 0;
	tree_generador_ruido = 0;
	
	jpsi_cuts = 0;
	lambda_cuts = 0;
	kaon_cuts = 0;
	lambda_b_cuts = 0;

	jpsi_e = 0;
	jpsi_p = {0, 0, 0};
	jpsi_invariant_mass = 0;
	jpsi_temp_mass = 0;
	es_candidato_j_psi = 0;
	
	charged_p1_magnitude = 0;
	charged_p2_magnitude = 0;
	lambda_0_e = 0;
	lambda_0_p = {0, 0, 0};
	lambda_0_invariant_mass = 0;
	
	k_short_invariant_mass = 0;
	
	es_candidato_lambda0 = 0;
	es_candidato_kaon = 0;
	
	lambda_b_invariant_mass = 0;
	es_candidato_lambda_b = 0;
}

void AnalysisPentaQuark::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t AnalysisPentaQuark::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef AnalysisPentaQuark_cxx
