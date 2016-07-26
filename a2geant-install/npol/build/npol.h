//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jan 26 13:27:30 2016 by ROOT version 5.34/28
// from TTree npol/npolillator Output
// found on file: Examplepolqf.root
//////////////////////////////////////////////////////////

#ifndef npol_h
#define npol_h

#include <TMath.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TLorentzVector.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class npol {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   TLorentzVector  *Inc;
   TLorentzVector  *SP;
   TLorentzVector  *SN;
   TLorentzVector  *RealS;
   Float_t         edep;
   Float_t         time;

   // List of branches
   TBranch        *b_Inc;   //!
   TBranch        *b_SP;   //!
   TBranch        *b_SN;   //!
   TBranch        *b_RealS;   //!
   TBranch        *b_fedep;   //!
   TBranch        *b_ftime;   //!

   npol(TTree *tree=0);
   virtual ~npol();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef npol_cxx
npol::npol(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("polqf20mil50cm.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("polqf20mil50cm.root");
      }
      f->GetObject("npol",tree);

   }
   Init(tree);
}

npol::~npol()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t npol::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t npol::LoadTree(Long64_t entry)
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

void npol::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   Inc = 0;
   SP = 0;
   SN = 0;
   RealS = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Inc", &Inc, &b_Inc);
   fChain->SetBranchAddress("SP", &SP, &b_SP);
   fChain->SetBranchAddress("SN", &SN, &b_SN);
   fChain->SetBranchAddress("RealS", &RealS, &b_RealS);
   fChain->SetBranchAddress("edep", &edep, &b_fedep);
   fChain->SetBranchAddress("time", &time, &b_ftime);
   Notify();
}

Bool_t npol::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void npol::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t npol::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef npol_cxx
