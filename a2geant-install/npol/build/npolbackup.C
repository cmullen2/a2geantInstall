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

void npol::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L npol.C
//      Root > npol t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   
   //Making general need to put all the inc stuff in loop, need 3 rotation matrices, apply all even if angle zero.
   
   //Init(npol);
   
/*   //Initial angles, We do not create these inside the loop as will be the same everytime in this case. Later when varying can use a function for the rotation matrix creation but need to get an entry here!
   GetEntry(1);
   Double_t inc_theta = t.Inc.Theta();
   Double_t inc_phi = Inc.Phi();
   
   cout <<inc_theta <<"Split"<<inc_phi << endl;
   
   //Reaction positions
   Double_t inc_x = Inc.X();
   Double_t inc_y = Inc.Y();
   Double_t inc_z = Inc.Z();
   
   TMatrixD inc_lab_vec(3,1);
   inc_lab_vec(0,0) = inc_x;
   inc_lab_vec(1,0) = inc_y;
   inc_lab_vec(2,0) = inc_z;
   
   
   
   //Rotation matrices
   Double_t c = cos(inc_theta); 
   Double_t s = sin(inc_theta);
   
   
   TMatrixD Rotx(3,3);
   
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
   
 */  
   //TMatrixD Attempt(3,1);
   TMatrixD sp_lab_vec(3,1);
   TMatrixD sn_lab_vec(3,1);
   TMatrixD inc_lab_vec(3,1);
   TMatrixD Rotx(3,3);
   TMatrixD Roty(3,3);
   TMatrixD Rotz(3,3);
   
   
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
   //Branches to be saved to the tree		Want to save the scattered positions and angles, do I want to convert them to TLorentzVectors and just use the other tree data apart from the frame dependent values?
   //						Could always store them as TMatrices and theta as individual leaves
   
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
   
/*   tree1->Branch("SNScatterX", &sn_scat_vec(0,0),8000,0);
   tree1->Branch("SNScatterY", &sn_scat_vec(1,0),8000,0);
   tree1->Branch("SNScatterZ", &sn_scat_vec(2,0),8000,0);
   tree1->Branch("NTheta",&n_theta,"n_theta/D");
   
   tree0->Branch("SPScatterX", &sp_scat_vec(0,0),8000,0);
   tree0->Branch("SPScatterY", &sp_scat_vec(1,0),8000,0);
   tree0->Branch("SPScatterZ", &sp_scat_vec(2,0),8000,0);
   tree0->Branch("PTheta",&p_theta,"p_theta/D");
*/

   gDirectory->pwd();
   file0->cd();
   gDirectory->pwd();
   file1->cd();
   gDirectory->pwd();
   file2->cd();
   gDirectory->pwd();
   file3->cd();
   gDirectory->pwd();
   
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      //analysis here?? General case so need multiple rotation matrices. reaction is incoming proton hits carbon goes to scattered proton and neutron and nucleus
      //need Inc,SP,SN, try Theta from SP first(in interactive mode t.Inc.Theta() gives theta.
      
      
      //Initial angles
      Double_t inc_theta = Inc->Theta();
      Double_t inc_phi = Inc->Phi();
   
  //    cout <<inc_theta <<"Split"<<inc_phi << endl;
   
      //Reaction positions
      Double_t inc_x = Inc->X();
      Double_t inc_y = Inc->Y();
      Double_t inc_z = Inc->Z();
   
      //TMatrixD inc_lab_vec(3,1);
      inc_lab_vec(0,0) = inc_x;
      inc_lab_vec(1,0) = inc_y;
      inc_lab_vec(2,0) = inc_z;
   
      //std::cout<< "   " <<__LINE__<<std::endl;

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
      sp_scat_vec = Rotx * sp_lab_vec; 
      sn_scat_vec = Rotx * sn_lab_vec;
      inc_scat_vec = Rotx * inc_lab_vec;
      
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
	//cout <<__FILE__ <<"  "<< __LINE__ << endl;
//	cout << sn_lab_vec(0,0)<< sn_lab_vec(1,0)<< sn_lab_vec(2,0)<< endl;
//	cout << sn_lab_vec(0,0)<< sn_lab_vec(1,0)<< sn_lab_vec(2,0)<< endl;
	file0->cd();
	tree0->Fill();
//	file0->cd();
//	gDirectory->pwd();
	//cout <<__FILE__ <<"  "<< __LINE__ << endl;
	
	
	
      }
      
      else if (( sp_lab_vec(0,0)==0 )&&( sp_lab_vec(1,0)==0 )&&( sp_lab_vec(2,0)==0 )) {     //may need a new iif statement for this see notes about this reaction(not convinced that we wouldn't see a proton
	//cout <<__FILE__ <<"  "<< __LINE__ << endl;
	cout <<"SP HEre "<< endl;
	file1->cd();
	tree1->Fill();
//	
//	gDirectory->pwd();
	//cout <<__FILE__ <<"  "<< __LINE__ << endl;
	
      }
      
      else if(p_degree_theta  > 0 && p_degree_theta <90){
	//cout <<__FILE__ <<"  "<< __LINE__ << endl;
	cout <<"THETA  "<< endl;
	file2->cd();
	tree2->Fill();
//	gDirectory->pwd();
	cout <<__FILE__ <<"  "<< __LINE__ << endl;
	
      }
      else{
	//cout <<__FILE__ <<"  "<< __LINE__ << endl;
	cout <<"ELSE  "<< endl;
	file3->cd();
	tree3->Fill();
	
//	gDirectory->pwd();
	//cout <<__FILE__ <<"  "<< __LINE__ << endl;
	
      }
      
//      tree1->Fill();
//      tree2->Fill();
      
     // std::cout <<"Worked" << p_degree_theta<<" <-tPp-> "<<p_degree_phi<<"   "<< n_degree_theta<<" <-tNp->  "<<n_degree_phi << " xyz "<< sn_x<<"   "<< sn_y<< "  "  << sn_z << std::endl;
     //std::cout << inc_x <<"    "<< inc_y << "    "<< inc_z << "    "<< inc_theta <<"    "<< inc_phi << sp_theta << " Work "<< sp_phi <<"    "<< sp_x <<"  " << sp_y << "  " << sp_z <<" Hello darkness "<<Rotx(1,1) <<" Blah "<<ientry<<std::endl;
      
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
 //Changed the name to the 200thou file in .h to check to see if its working properly. Also changed the names of the output files now and running the 200thou30cm one. Changed back to examplepolqf call trees example...












