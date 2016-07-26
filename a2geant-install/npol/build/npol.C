#define npol_cxx
#include "npol.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TMatrixD.h>
#include <TVectorD.h>
#include <TVector.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <assert.h>



   TVector3 CalculateScatVec(TVector3 income,TVector3 ScatLab);
   TVector3 zprime; 
   TVector3 yprime;
   TVector3 xprime;
   TVector3 income;
   TVector3 xlab(1,0,0);
   TVector3 ylab(0,1,0);
   TVector3 zlab(0,0,1);
   TVector3 ScatP;
   TVector3 ScatN;
   Double_t Nmomentum;
   Double_t RotM[3][3];



void npol::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
  
  
   
 

   //File to write to
   TFile* file0 = TFile::Open("./output/Thetatest.root","RECREATE");
   TTree* tree0 = new TTree("All","tree title");
   
/*   TVector3 zprime; 
   TVector3 yprime;
   TVector3 xprime;
   TVector3 income;
   TVector3 xlab(1,0,0);
   TVector3 ylab(0,1,0);
   TVector3 zlab(0,0,1);
   TVector3 ScatP;
   TVector3 ScatN;
 */
   Double_t PSFrameAngleThetaDeg;
   Double_t PSFrameAnglePhiDeg;
   
   Double_t NSFrameAngleThetaDeg;
   Double_t NSFrameAnglePhiDeg;
   
//   Double_t Nmomentum;
//   Double_t RotM[3][3];
   
  

   //Branches to be saved to the tree   primes will be same everytime due to function so remove not true see position of loop.
   TBranch *branchZP = tree0->Branch("ZPrime.", &zprime,8000,0);
   TBranch *branchYP = tree0->Branch("YPrime.", &yprime,8000,0);
   TBranch *branchXP = tree0->Branch("XPrime.", &xprime,8000,0);
 
   TBranch *branchSPATD = tree0->Branch("PSFrameAngleThetaDeg", &PSFrameAngleThetaDeg,"PSFrameAngleThetaDeg/D");
   TBranch *branchSPAPD = tree0->Branch("PSFrameAnglePhiDeg", &PSFrameAnglePhiDeg,"PSFrameAnglePhiDeg/D");
   TBranch *branchOP = tree0->Branch("ScatP", &ScatP,8000,0);

   TBranch *branchSNATD = tree0->Branch("NSFrameAngleThetaDeg", &NSFrameAngleThetaDeg,"NSFrameAngleThetaDeg/D");
   TBranch *branchSNAPD = tree0->Branch("NSFrameAnglePhiDeg", &NSFrameAnglePhiDeg,"NSFrameAnglePhiDeg/D");
   TBranch *branchON = tree0->Branch("ScatN", &ScatN,8000,0);


/*   tree1->Branch("SPScatterX", &sp_scat_vec(0,0),8000,0);
   tree1->Branch("SPScatterY", &sp_scat_vec(1,0),8000,0);
   tree1->Branch("SPScatterZ", &sp_scat_vec(2,0),8000,0);
   tree1->Branch("PTheta",&p_degree_theThetata,"p_theta/D");
   tree1->Branch("PPhi",&p_degree_phi,"p_phi/D");

   tree1->Branch("SNScatterX", &sn_scat_vec(0,0),8000,0);
   tree1->Branch("SNScatterY", &sn_scat_vec(1Theta,0),8000,0);
   tree1->Branch("SNScatterZ", &sn_scat_vec(2,0),8000,0);
   tree1->Branch("NTheta",&n_degree_theta,"n_theta/D");
   tree1->Branch("NPhi",&n_degree_phi,"n_phi/D");
   
   
*/   
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
            
      //Getting the lab vectors
      income =  Inc->Vect();
      ScatP =  SP->Vect();
      ScatN = SN->Vect();
  
      
      TVector3 ProtonSFrame = CalculateScatVec(income,ScatP);
      TVector3 NeutronSFrame = CalculateScatVec(income,ScatP);
      
      // Getting the momentum of the neutron
      Nmomentum = SN->Rho();
     // Nenergy = Sn->(Energy);
      
      PSFrameAngleThetaDeg  = ProtonSFrame.Angle(zprime)*TMath::RadToDeg();
      PSFrameAnglePhiDeg  = ProtonSFrame.Angle(xprime)*TMath::RadToDeg();
      
      NSFrameAngleThetaDeg = NeutronSFrame.Angle(zprime)*TMath::RadToDeg();
      NSFrameAnglePhiDeg = NeutronSFrame.Angle(xprime)*TMath::RadToDeg();
      
        
      std::cout << zprime(0) << " " << zprime(1) << " " << zprime(2) <<" Z" <<std::endl;
      std::cout << yprime(0) << " " << yprime(1) << " " << yprime(2) <<" Y" << std::endl;
      std::cout << xprime(0) << " " << xprime(1) << " " << xprime(2) <<" X" <<std::endl;
      std::cout << zprime.Angle(xprime) << "   " << zprime.Angle(yprime) <<" YX " << yprime.Angle(xprime)*TMath::RadToDeg() << std::endl;
      //v1.DOt(v2)
      //Notes
      // Need to use TMath::RadtoDeg() to convert to degrees rather than current method.
      //Steps: degrees, selection, energy + mass thingymay  
      
      
      
      
      if (Nmomentum > 0){
	tree0->Fill();
	//std::cout<<Nmomentum<<std::endl;
//	if (Nenergy > 200) {
//	  tree0->Fill();
//	}
      }
     
      
   }//end of entries loop
   
   
   //file0->cd();
   tree0->Write();
   file0->Close();

}//end of npol::Loop()






TVector3 CalculateScatVec(TVector3 Incoming ,TVector3 ScatLab){
  
      //What is quicker passing in same value each time or defining value here each time?
      
      zprime = income.Unit();
      yprime = zlab.Cross(-income);
      yprime = yprime.Unit();
      xprime = yprime.Cross(zprime);    
      xprime = xprime.Unit();
  
  
      RotM[0][0] = xlab.Dot(xprime) ;
      RotM[0][1] = xlab.Dot(yprime);
      RotM[0][2] = xlab.Dot(zprime);
      RotM[1][0] = ylab.Dot(xprime);
      RotM[1][1] = ylab.Dot(yprime) ;
      RotM[1][2] = ylab.Dot(zprime) ;
      RotM[2][0] = zlab.Dot(xprime);
      RotM[2][1] = zlab.Dot(yprime);
      RotM[2][2] = zlab.Dot(zprime);
      
      TVector3 ScatNuc;
      //This is different from the Reconstruct file so is likely incorrect, indices of the matrix are switched around.
      ScatNuc(0) = (RotM[0][0]*ScatLab(0) +  RotM[1][0]*ScatLab(1) + RotM[2][0]*ScatLab(2) );
      ScatNuc(1) = (RotM[0][1]*ScatLab(0) +  RotM[1][1]*ScatLab(1) + RotM[2][1]*ScatLab(2) );
      ScatNuc(2) = (RotM[0][2]*ScatLab(0) +  RotM[1][2]*ScatLab(1) + RotM[2][2]*ScatLab(2) );
      
      //std::cout << zprime(0) << " " << zprime(1) << " " << zprime(2) <<std::endl;
      return ScatNuc;
  
}





