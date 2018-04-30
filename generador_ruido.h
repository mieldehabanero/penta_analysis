//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Apr 27 20:31:47 2018 by ROOT version 6.13/02
// from TTree generador_ruido/Ruido con eventos mezclados
// found on file: Resultados/generador_ruido.root
//////////////////////////////////////////////////////////

#ifndef generador_ruido_h
#define generador_ruido_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class generador_ruido {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         B_J_px;
   Float_t         B_J_py;
   Float_t         B_J_pz;
   Float_t         B_J_e;
   Float_t         B_lamb_px;
   Float_t         B_lamb_py;
   Float_t         B_lamb_pz;
   Float_t         B_lamb_e;

   // List of branches
   TBranch        *b_B_J_px;   //!
   TBranch        *b_B_J_py;   //!
   TBranch        *b_B_J_pz;   //!
   TBranch        *b_B_J_e;   //!
   TBranch        *b_B_lamb_px;   //!
   TBranch        *b_B_lamb_py;   //!
   TBranch        *b_B_lamb_pz;   //!
   TBranch        *b_B_lamb_e;   //!

   generador_ruido(TTree *tree=0);
   virtual ~generador_ruido();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef generador_ruido_cxx
generador_ruido::generador_ruido(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Resultados/generador_ruido.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Resultados/generador_ruido.root");
      }
      f->GetObject("generador_ruido",tree);

   }
   Init(tree);
}

generador_ruido::~generador_ruido()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t generador_ruido::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t generador_ruido::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void generador_ruido::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("B_J_px", &B_J_px, &b_B_J_px);
   fChain->SetBranchAddress("B_J_py", &B_J_py, &b_B_J_py);
   fChain->SetBranchAddress("B_J_pz", &B_J_pz, &b_B_J_pz);
   fChain->SetBranchAddress("B_J_e", &B_J_e, &b_B_J_e);
   fChain->SetBranchAddress("B_lamb_px", &B_lamb_px, &b_B_lamb_px);
   fChain->SetBranchAddress("B_lamb_py", &B_lamb_py, &b_B_lamb_py);
   fChain->SetBranchAddress("B_lamb_pz", &B_lamb_pz, &b_B_lamb_pz);
   fChain->SetBranchAddress("B_lamb_e", &B_lamb_e, &b_B_lamb_e);
   Notify();
}

Bool_t generador_ruido::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void generador_ruido::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t generador_ruido::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef generador_ruido_cxx
