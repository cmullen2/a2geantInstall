#define npol_cxx
#include "npol.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TMatrixD.h>
#include <TVectorD.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <assert.h>

void TestClearnpol::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   TMatrixD sp_lab_vec(3,1);
   TMatrixD sn_lab_vec(3,1);
   TMatrixD inc_lab_vec(3,1);
   TMatrixD Rotx(3,3);
   TMatrixD Roty(3,3);
   TMatrixD Rotz(3,3);
   TMatrixD minusRotx(3,3);
   
   TMatrixD sp_scat_vec(3,1);
   TMatrixD sn_scat_vec(3,1);
   TMatrixD inc_scat_vec(3,1);
   
   Double_t p_zpos_diff;
   Double_t p_xpos_diff;
   Double_t p_ypos_diff;
   
   Double_t n_zpos_diff;
   Double_t n_xpos_diff;
   Double_t n_ypos_diff;
   
   Double_t p_theta;
   Double_t p_phi;
   
   Double_t n_theta;
   Double_t n_phi;
   
   Double_t p_degree_phi;
   Double_t p_degree_theta;
   
   Double_t n_degree_phi;
   Double_t n_degree_theta;
   

   //File to write to
   TFile* file0 = TFile::Open("./output/testtree0.root","RECREATE");
   TTree *tree0 = new TTree("NoNeutron","NoNeutron");
   TFile* file1 = TFile::Open("./output/testtree1.root", "RECREATE");
   TTree *tree1 = new TTree("NoProton","NoProton");
   TFile* file2 = TFile::Open("./output/testtree2.root", "RECREATE");
   TTree *tree2 = new TTree("BothNoCharge","BothNoCharge");
   TFile* file3 = TFile::Open("./output/testtree3.root","RECREATE");
   TTree *tree3 = new TTree("ChargeConBothObv","ChargeConBothObv");
   //Branches to be saved to the tree   
   tree0->Branch("SPScatterX", &sp_scat_vec(0,0),8000,0);
   tree0->Branch("SPScatterY", &sp_scat_vec(1,0),8000,0);
   tree0->Branch("SPScatterZ", &sp_scat_vec(2,0),8000,0);
   tree0->Branch("PTheta",&p_theta,"p_theta/D");
   tree0->Branch("PPhi",&p_phi,"p_phi/D");

   tree0->Branch("SNScatterX", &sn_scat_vec(0,0),8000,0);
   tree0->Branch("SNScatterY", &sn_scat_vec(1,0),8000,0);
   tree0->Branch("SNScatterZ", &sn_scat_vec(2,0),8000,0);
   tree0->Branch("NTheta",&n_theta,"n_theta/D");
   tree0->Branch("NPhi",&n_phi,"n_phi/D");

   tree1->Branch("SPScatterX", &sp_scat_vec(0,0),8000,0);
   tree1->Branch("SPScatterY", &sp_scat_vec(1,0),8000,0);
   tree1->Branch("SPScatterZ", &sp_scat_vec(2,0),8000,0);
   tree1->Branch("PTheta",&p_theta,"p_theta/D");
   tree1->Branch("PPhi",&p_phi,"p_phi/D");

   tree1->Branch("SNScatterX", &sn_scat_vec(0,0),8000,0);
   tree1->Branch("SNScatterY", &sn_scat_vec(1,0),8000,0);
   tree1->Branch("SNScatterZ", &sn_scat_vec(2,0),8000,0);
   tree1->Branch("NTheta",&n_theta,"n_theta/D");
   tree1->Branch("NPhi",&n_phi,"n_phi/D");
   
   tree2->Branch("SPScatterX", &sp_scat_vec(0,0),8000,0);
   tree2->Branch("SPScatterY", &sp_scat_vec(1,0),8000,0);
   tree2->Branch("SPScatterZ", &sp_scat_vec(2,0),8000,0);
   tree2->Branch("PTheta",&p_theta,"p_theta/D");
   tree2->Branch("PPhi",&p_phi,"p_phi/D");

   tree2->Branch("SNScatterX", &sn_scat_vec(0,0),8000,0);
   tree2->Branch("SNScatterY", &sn_scat_vec(1,0),8000,0);
   tree2->Branch("SNScatterZ", &sn_scat_vec(2,0),8000,0);
   tree2->Branch("NTheta",&n_theta,"n_theta/D");
   tree2->Branch("NPhi",&n_phi,"n_phi/D");
   
   
   tree3->Branch("SPScatterX", &sp_scat_vec(0,0),8000,0);
   tree3->Branch("SPScatterY", &sp_scat_vec(1,0),8000,0);
   tree3->Branch("SPScatterZ", &sp_scat_vec(2,0),8000,0);
   tree3->Branch("PTheta",&p_theta,"p_theta/D");
   tree3->Branch("PPhi",&p_phi,"p_phi/D");

   tree3->Branch("SNScatterX", &sn_scat_vec(0,0),8000,0);
   tree3->Branch("SNScatterY", &sn_scat_vec(1,0),8000,0);
   tree3->Branch("SNScatterZ", &sn_scat_vec(2,0),8000,0);
   tree3->Branch("NTheta",&n_theta,"n_theta/D");
   tree3->Branch("NPhi",&n_phi,"n_phi/D");
   
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      //Initial angles
      Double_t inc_theta = Inc->Theta();
      Double_t inc_phi = Inc->Phi();
   
   
      //Reaction positions
      Double_t inc_x = Inc->X();
      Double_t inc_y = Inc->Y();
      Double_t inc_z = Inc->Z();
   
      //TMatrixD inc_lab_vec(3,1);
      inc_lab_vec(0,0) = inc_x;
      inc_lab_vec(1,0) = inc_y;
      inc_lab_vec(2,0) = inc_z;
   

      //Rotation matrices
      Double_t c = cos(inc_theta); 
      Double_t s = sin(inc_theta);
   
      Double_t c2 = cos(inc_phi);
      Double_t s2 = sin(inc_phi);
      
/*      Double_t c3 = cos(); //need to think about the Z rotation angle
      Double_t s3 = sin();
*/   
      //TMatrixD Rotx(3,3);
   
      //Loop to fill matrices?
      Rotx(0,0) = 1;
      Rotx(1,0) = 0;
      Rotx(2,0) = 0;
      Rotx(0,1) = 0;
      Rotx(0,2) = 0;
      Rotx(1,1) = c;
      Rotx(1,2) = -s;
      Rotx(2,1) = s;
      Rotx(2,2) = c;
      
   
      Roty(0,0) = c2;
      Roty(1,0) = 0;
      Roty(2,0) = -s2;
      Roty(0,1) = 0;
      Roty(0,2) = s2;
      Roty(1,1) = 1;
      Roty(1,2) = 0;
      Roty(2,1) = 0;
      Roty(2,2) = c;
   
      
/*      Rotz(0,0) = c3;
      Rotz(1,0) = s3;
      Rotz(2,0) = 0;
      Rotz(0,1) = -s3;
      Rotz(0,2) = 0;
      Rotz(1,1) = c3;
      Rotz(1,2) = 0;
      Rotz(2,1) = 0;
      Rotz(2,2) = 1;
*/     
      minusRotx(0,0) = -1;
      minusRotx(1,0) = 0;
      minusRotx(2,0) = 0;
      minusRotx(0,1) = 0;
      minusRotx(0,2) = 0;
      minusRotx(1,1) = -c;
      minusRotx(1,2) = s;
      minusRotx(2,1) = -s;
      minusRotx(2,2) = -c;     
      

      
      //Get the angles of the scattered Particles in the Lab frame.  SP is scattered proton, SN neutron
      Double_t sp_theta =SP->Theta();
      Double_t sn_theta =SN->Theta();
      Double_t sp_phi =SP->Phi();
      Double_t sn_phi =SN->Phi();
      
      //proton and neutron final positions
      Double_t sp_x = SP->X();
      Double_t sp_y = SP->Y();
      Double_t sp_z = SP->X();
      
      Double_t sn_x = SN->X();
      Double_t sn_y = SN->Y();
      Double_t sn_z = SN->Z();

      
      sp_lab_vec(0,0)= sp_x;
      sp_lab_vec(1,0)= sp_y;
      sp_lab_vec(2,0)= sp_z;
      
      sn_lab_vec(0,0) = sn_x;
      sn_lab_vec(1,0) = sn_y;
      sn_lab_vec(2,0) = sn_z;
      
      //Applying rotation (only 1D and for proton at moment).
      sp_scat_vec = minusRotx * sp_lab_vec; 
      sn_scat_vec = minusRotx * sn_lab_vec;
      inc_scat_vec = minusRotx * inc_lab_vec;
      
      //Calculating position differences of proton, Can use if statement to correct negative sign if needed .
      p_zpos_diff = sp_scat_vec(2,0) - inc_scat_vec(2,0);
      p_ypos_diff = sp_scat_vec(1,0) - inc_scat_vec(1,0);
      p_xpos_diff = sp_scat_vec(0,0) - inc_scat_vec(0,0);
      
      
      //Postion differences for neutron
      n_zpos_diff = sn_scat_vec(2,0) - inc_scat_vec(2,0);
      n_ypos_diff = sn_scat_vec(1,0) - inc_scat_vec(1,0);
      n_xpos_diff = sn_scat_vec(0,0) - inc_scat_vec(0,0);
      
      //Proton scattered frame angle calculations
      p_theta = atan(p_ypos_diff/p_zpos_diff);
      p_phi = atan(p_ypos_diff/p_xpos_diff);
      
      
      //neuton scattered frame angle calculations.
      n_theta = atan(n_ypos_diff/n_zpos_diff);
      n_phi = atan(n_ypos_diff/n_zpos_diff);
      
      
      //Converting to degrees for debugging
      p_degree_theta = 180*p_theta/3.1415926;
      p_degree_phi = 180*p_phi/3.1415926;
      
      n_degree_theta = 180*n_theta/3.1415926;
      n_degree_phi = 180*n_phi/3.1415926;
      
      
      if ( ( sn_lab_vec(0,0)==0 )&&( sn_lab_vec(1,0)==0 )&&( sn_lab_vec(2,0)==0 )){
	file0->cd();
	tree0->Fill();
	
      }
      
      else if (( sp_lab_vec(0,0)==0 )&&( sp_lab_vec(1,0)==0 )&&( sp_lab_vec(2,0)==0 )) {     //may need a new if statement for this see notes about this reaction(not convinced that we wouldn't see a proton
	file1->cd();
	tree1->Fill();
	
      }
      
      else if(p_degree_theta  > 0 && p_degree_theta <90){
	file2->cd();
	tree2->Fill();	
      }
      else{
	file3->cd();
	tree3->Fill();
	
      }
      
   }//end of entries loop
   
   file0->cd();
   tree0->Write();
   file1->cd();
   tree1->Write();
   file2->cd();
   tree2->Write();
   file3->cd();
   tree3->Write();
   
}//end of npol::Loop()












