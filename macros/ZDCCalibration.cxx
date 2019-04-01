////////////////////////////////////////
//
//Iterative Calibration of ZDCs
//
///////////////////////////////////////

{ 
 
  TFile * Read = new TFile ("LeadingMerged12b.root");
  TTree * T = (TTree *)Read->Get("tEvents");
  
  Int_t bin = 1000;
  Double_t thrP = 0.9;
  Double_t thrP2 = 0.5;
  Double_t thrN = 0.9;
  Float_t ZDCP1[5], ZDCP1Sum, ZDCN1[5], ZDCN1Sum, ZDCP2[5], ZDCP2Sum, ZDCN2[5], ZDCN2Sum,diff,mean, diffN, meanN;
  Double_t cP1[5]={1,1,1,1,1};
  Double_t cP2[5]={1,1,1,1,1};
  Double_t cN1[5]={1,1,1,1,1};
  Double_t cN2[5]={1,1,1,1,1};
 
  T->SetBranchAddress("adcZDCP1",ZDCP1);
  T->SetBranchAddress("adcZDCN1",ZDCN1);
  T->SetBranchAddress("adcZDCP2",ZDCP2);
  T->SetBranchAddress("adcZDCN2",ZDCN2);

  //Histos
  TH2D * hZDCNP1= new TH2D("hZDCNP1","ZDCN1[0] vs ZDCP1[0];ZDCN1[0];ZDCP1[0];",bin,-1,2000,bin,-1,2000);
  TH2D * hZDCNP2= new TH2D("hZDCNP2","ZDCN2[0] vs ZDCP2[0];ZDCN2[0];ZDCP2[0];",bin,-1,2000,bin,-1,2000);
  
  TH2D * hZDCP1_ch01= new TH2D("hZDCP1_ch01","ZDCP1[1] > 0.9*(ZDCP1[1]+ZDCP1[2]+ZDCP1[3]+ZDCP1[4]);ZDCP1[0];ZDCP1Sum;",bin,-1,4000,bin,-1,4000);
  TH2D * hZDCP1_ch02= new TH2D("hZDCP1_ch02","ZDCP1[2] > 0.8*(ZDCP1[1]+ZDCP1[2]+ZDCP1[3]+ZDCP1[4]);ZDCP1[0];ZDCP1Sum;",bin,-1,4000,bin,-1,4000);
  TH2D * hZDCP1_ch03= new TH2D("hZDCP1_ch03","ZDCP1[3] > 0.8*(ZDCP1[1]+ZDCP1[2]+ZDCP1[3]+ZDCP1[4]);ZDCP1[0];ZDCP1Sum;",bin,-1,4000,bin,-1,4000);
  TH2D * hZDCP1_ch04= new TH2D("hZDCP1_ch04","ZDCP1[4] > 0.8*(ZDCP1[1]+ZDCP1[2]+ZDCP1[3]+ZDCP1[4]);ZDCP1[0];ZDCP1Sum;",bin,-1,4000,bin,-1,4000);

  TH2D * hZDCP2_ch01= new TH2D("hZDCP2_ch01","ZDCP2[1] > 0.8*(ZDCP2[1]+ZDCP2[2]+ZDCP2[3]+ZDCP2[4]);ZDCP2[0];ZDCP2Sum;",bin,-1,4000,bin,-1,4000);
  TH2D * hZDCP2_ch02= new TH2D("hZDCP2_ch02","ZDCP2[2] > 0.8*(ZDCP2[1]+ZDCP2[2]+ZDCP2[3]+ZDCP2[4]);ZDCP2[0];ZDCP2Sum;",bin,-1,4000,bin,-1,4000);
  TH2D * hZDCP2_ch03= new TH2D("hZDCP2_ch03","ZDCP2[3] > 0.8*(ZDCP2[1]+ZDCP2[2]+ZDCP2[3]+ZDCP2[4]);ZDCP2[0];ZDCP2Sum;",bin,-1,4000,bin,-1,4000);
  TH2D * hZDCP2_ch04= new TH2D("hZDCP2_ch04","ZDCP2[4] > 0.9*(ZDCP2[1]+ZDCP2[2]+ZDCP2[3]+ZDCP2[4]);ZDCP2[0];ZDCP2Sum;",bin,-1,4000,bin,-1,4000);

  TH2D * hZDCN1_ch01= new TH2D("hZDCN1_ch01","ZDCN1[1] > 0.9*(ZDCN1[1]+ZDCN1[2]+ZDCN1[3]+ZDCN1[4]);ZDCN1[0];ZDCN1Sum;",bin,-1,4000,bin,-1,4000);
  TH2D * hZDCN1_ch02= new TH2D("hZDCN1_ch02","ZDCN1[1] > 0.9*(ZDCN1[1]+ZDCN1[2]+ZDCN1[3]+ZDCN1[4]);ZDCN1[0];ZDCN1Sum;",bin,-1,4000,bin,-1,4000);
  TH2D * hZDCN1_ch03= new TH2D("hZDCN1_ch03","ZDCN1[1] > 0.9*(ZDCN1[1]+ZDCN1[2]+ZDCN1[3]+ZDCN1[4]);ZDCN1[0];ZDCN1Sum;",bin,-1,4000,bin,-1,4000);
  TH2D * hZDCN1_ch04= new TH2D("hZDCN1_ch04","ZDCN1[1] > 0.9*(ZDCN1[1]+ZDCN1[2]+ZDCN1[3]+ZDCN1[4]);ZDCN1[0];ZDCN1Sum;",bin,-1,4000,bin,-1,4000);
  
  TH2D * hZDCN2_ch01= new TH2D("hZDCN2_ch01","ZDCN2[1] > 0.9*(ZDCN2[1]+ZDCN2[2]+ZDCN2[3]+ZDCN2[4]);ZDCN2[0];ZDCN2Sum;",bin,-1,4000,bin,-1,4000);
  TH2D * hZDCN2_ch02= new TH2D("hZDCN2_ch02","ZDCN2[2] > 0.9*(ZDCN2[1]+ZDCN2[2]+ZDCN2[3]+ZDCN2[4]);ZDCN2[0];ZDCN2Sum;",bin,-1,4000,bin,-1,4000);
  TH2D * hZDCN2_ch03= new TH2D("hZDCN2_ch03","ZDCN2[3] > 0.9*(ZDCN2[1]+ZDCN2[2]+ZDCN2[3]+ZDCN2[4]);ZDCN2[0];ZDCN2Sum;",bin,-1,4000,bin,-1,4000);
  TH2D * hZDCN2_ch04= new TH2D("hZDCN2_ch04","ZDCN2[4] > 0.9*(ZDCN2[1]+ZDCN2[2]+ZDCN2[3]+ZDCN2[4]);ZDCN2[0];ZDCN2Sum;",bin,-1,4000,bin,-1,4000);

  TH2D * resP1= new TH2D("resP1","Resolution P1;sum-common (GeV);(sum+common)/2 (GeV);",bin,-1,4000,bin,-2000,2000);
  TH2D * resN1= new TH2D("resN1","Resolution N1;sum+comm /2 ;sum-common ;",bin,-1,4000,bin,-2000,2000);

  TH1D * hcP1_1 = new TH1D("hcP1_1","cP1_1",bin,-1,5);
  TH1D * hcP1_2 = new TH1D("hcP1_2","cP1_2",bin,-1,5);
  TH1D * hcP1_3 = new TH1D("hcP1_3","cP1_3",bin,-1,5);
  TH1D * hcP1_4 = new TH1D("hcP1_4","cP1_4",bin,-1,5);
  TH1D * hcP2_1 = new TH1D("hcP2_1","cP2_1",bin,-1,5);
  TH1D * hcP2_2 = new TH1D("hcP2_2","cP2_2",bin,-1,5);
  TH1D * hcP2_3 = new TH1D("hcP2_3","cP2_3",bin,-1,5);
  TH1D * hcP2_4 = new TH1D("hcP2_4","cP2_4",bin,-1,5);
  TH1D * hcN1_1 = new TH1D("hcN1_1","cN1_1",bin,-1,5);
  TH1D * hcN1_2 = new TH1D("hcN1_2","cN1_2",bin,-1,5);
  TH1D * hcN1_3 = new TH1D("hcN1_3","cN1_3",bin,-1,5);
  TH1D * hcN1_4 = new TH1D("hcN1_4","cN1_4",bin,-1,5);
  TH1D * hcN2_1 = new TH1D("hcN2_1","cN2_1",bin,-1,5);
  TH1D * hcN2_2 = new TH1D("hcN2_2","cN2_2",bin,-1,5);
  TH1D * hcN2_3 = new TH1D("hcN2_3","cN2_3",bin,-1,5);
  TH1D * hcN2_4 = new TH1D("hcN2_4","cN2_4",bin,-1,5);
   
  for (Int_t k=0; k<4; k++)//iterations for calibration
    {
      for(Int_t i=0; i<T->GetEntries();i++)//loop over Tree entries
	{
	  T->GetEvent(i);
	  
	  //P1
	  ZDCP1Sum = ZDCP1[1]/cP1[1]+ZDCP1[2]/cP1[2]+ZDCP1[3]/cP1[3]+ZDCP1[4]/cP1[4];
	  if(ZDCN1[0]<100 )// && ZDCN1[1]>150 && ZDCN1[2]>150 && ZDCN1[0]>150)
	    {
	      if (ZDCP1[1]>(thrP* (ZDCP1[1]+ZDCP1[2]+ZDCP1[3]+ZDCP1[4]))) hZDCP1_ch01->Fill(ZDCP1[0],ZDCP1Sum); 
	      if (ZDCP1[2]>(thrP2*(ZDCP1[1]+ZDCP1[2]+ZDCP1[3]+ZDCP1[4]))) hZDCP1_ch02->Fill(ZDCP1[0],ZDCP1Sum); 
	      if (ZDCP1[3]>(thrP2*(ZDCP1[1]+ZDCP1[2]+ZDCP1[3]+ZDCP1[4]))) hZDCP1_ch03->Fill(ZDCP1[0],ZDCP1Sum); 
	      if (ZDCP1[4]>(thrP2*(ZDCP1[1]+ZDCP1[2]+ZDCP1[3]+ZDCP1[4]))) hZDCP1_ch04->Fill(ZDCP1[0],ZDCP1Sum);
	    }
          //P2
	  ZDCP2Sum=ZDCP2[1]/cP2[1]+ZDCP2[2]/cP2[2]+ZDCP2[3]/cP2[3]+ZDCP2[4]/cP2[4];
	   if(ZDCN2[0]<100 )// && ZDCN1[1]>150 && ZDCN1[2]>150 && ZDCN1[0]>150)
	     {
	       if (ZDCP2[1]>(thrP2*(ZDCP2[1]+ZDCP2[2]+ZDCP2[3]+ZDCP2[4]))) hZDCP2_ch01->Fill(ZDCP2[0],ZDCP2Sum);
	       if (ZDCP2[2]>(thrP2*(ZDCP2[1]+ZDCP2[2]+ZDCP2[3]+ZDCP2[4]))) hZDCP2_ch02->Fill(ZDCP2[0],ZDCP2Sum);
	       if (ZDCP2[3]>(thrP2*(ZDCP2[1]+ZDCP2[2]+ZDCP2[3]+ZDCP2[4]))) hZDCP2_ch03->Fill(ZDCP2[0],ZDCP2Sum);
	       if (ZDCP2[4]>(thrP* (ZDCP2[1]+ZDCP2[2]+ZDCP2[3]+ZDCP2[4]))) hZDCP2_ch04->Fill(ZDCP2[0],ZDCP2Sum);
	     }
	   //N1
	  ZDCN1Sum=ZDCN1[1]/cN1[1]+ZDCN1[2]/cN1[2]+ZDCN1[3]/cN1[3]+ZDCN1[4]/cN1[4];
	  if(ZDCP1[0]<100 )// && ZDCN1[1]>150 && ZDCN1[2]>150 && ZDCN1[0]>150)
	    {
	      if (ZDCN1[1]>(thrN*(ZDCN1[1]+ZDCN1[2]+ZDCN1[3]+ZDCN1[4]))) hZDCN1_ch01->Fill(ZDCN1[0],ZDCN1Sum);
	      if (ZDCN1[2]>(thrN*(ZDCN1[1]+ZDCN1[2]+ZDCN1[3]+ZDCN1[4]))) hZDCN1_ch02->Fill(ZDCN1[0],ZDCN1Sum); 
	      if (ZDCN1[3]>(thrN*(ZDCN1[1]+ZDCN1[2]+ZDCN1[3]+ZDCN1[4]))) hZDCN1_ch03->Fill(ZDCN1[0],ZDCN1Sum); 
	      if (ZDCN1[4]>(thrN*(ZDCN1[1]+ZDCN1[2]+ZDCN1[3]+ZDCN1[4]))) hZDCN1_ch04->Fill(ZDCN1[0],ZDCN1Sum);
	    }
	  //N2
	  ZDCN2Sum=ZDCN2[1]/cN2[1]+ZDCN2[2]/cN2[2]+ZDCN2[3]/cN2[3]+ZDCN2[4]/cN2[4];
	  if(ZDCP2[0]<100 )// && ZDCN1[1]>150 && ZDCN1[2]>150 && ZDCN1[0]>150)
	    {
	      if (ZDCN2[1]>(thrN*(ZDCN2[1]+ZDCN2[2]+ZDCN2[3]+ZDCN2[4]))) hZDCN2_ch01->Fill(ZDCN2[0],ZDCN2Sum); 
	      if (ZDCN2[2]>(thrN*(ZDCN2[1]+ZDCN2[2]+ZDCN2[3]+ZDCN2[4]))) hZDCN2_ch02->Fill(ZDCN2[0],ZDCN2Sum); 
	      if (ZDCN2[3]>(thrN*(ZDCN2[1]+ZDCN2[2]+ZDCN2[3]+ZDCN2[4]))) hZDCN2_ch03->Fill(ZDCN2[0],ZDCN2Sum); 
	      if (ZDCN2[4]>(thrN*(ZDCN2[1]+ZDCN2[2]+ZDCN2[3]+ZDCN2[4]))) hZDCN2_ch04->Fill(ZDCN2[0],ZDCN2Sum);
	    }
	      //N vs P   
	  hZDCNP1->Fill(ZDCN1[0],ZDCP1[0]);
	  hZDCNP2->Fill(ZDCN2[0],ZDCP2[0]);
	  //
	  diff=ZDCP1Sum-ZDCP1[0];
	  mean=(ZDCP1Sum+ZDCP1[0])/2;
	  diffN=ZDCN1Sum-ZDCN1[0];
	  meanN=(ZDCN1Sum+ZDCN1[0])/2;
	  
	  resP1->Fill(mean,diff);
	  resN1->Fill(meanN,diffN);
	}
        
      TF1 *f = new TF1("f","[0]*x");

      //P1
      hZDCP1_ch01->Fit("f");
      hZDCP1_ch02->Fit("f");
      hZDCP1_ch03->Fit("f");
      hZDCP1_ch04->Fit("f");
      cP1[1] *= hZDCP1_ch01->GetFunction("f")->GetParameter(0);
      cP1[2] *= hZDCP1_ch02->GetFunction("f")->GetParameter(0);
      cP1[3] *= hZDCP1_ch03->GetFunction("f")->GetParameter(0);
      cP1[4] *= hZDCP1_ch04->GetFunction("f")->GetParameter(0);
      //P2
      hZDCP2_ch01->Fit("f");
      hZDCP2_ch02->Fit("f");
      hZDCP2_ch03->Fit("f");
      hZDCP2_ch04->Fit("f");
      cP2[1] *= hZDCP2_ch01->GetFunction("f")->GetParameter(0);
      cP2[2] *= hZDCP2_ch02->GetFunction("f")->GetParameter(0);
      cP2[3] *= hZDCP2_ch03->GetFunction("f")->GetParameter(0);
      cP2[4] *= hZDCP2_ch04->GetFunction("f")->GetParameter(0);
      //N1
      hZDCN1_ch01->Fit("f");
      hZDCN1_ch02->Fit("f");
      hZDCN1_ch03->Fit("f");
      hZDCN1_ch04->Fit("f");
      cN1[1] *= hZDCN1_ch01->GetFunction("f")->GetParameter(0);
      cN1[2] *= hZDCN1_ch02->GetFunction("f")->GetParameter(0);
      cN1[3] *= hZDCN1_ch03->GetFunction("f")->GetParameter(0);
      cN1[4] *= hZDCN1_ch04->GetFunction("f")->GetParameter(0);
      //N2
      hZDCN2_ch01->Fit("f");
      hZDCN2_ch02->Fit("f");
      hZDCN2_ch03->Fit("f");
      hZDCN2_ch04->Fit("f");
      cN2[1] *= hZDCN2_ch01->GetFunction("f")->GetParameter(0);
      cN2[2] *= hZDCN2_ch02->GetFunction("f")->GetParameter(0);
      cN2[3] *= hZDCN2_ch03->GetFunction("f")->GetParameter(0);
      cN2[4] *= hZDCN2_ch04->GetFunction("f")->GetParameter(0);
     
    }

  hcP1_1->Fill(cP1[1]);
  hcP1_2->Fill(cP1[2]);
  hcP1_3->Fill(cP1[3]);
  hcP1_4->Fill(cP1[4]);
  hcP2_1->Fill(cP2[1]);
  hcP2_2->Fill(cP2[2]);
  hcP2_3->Fill(cP2[3]);
  hcP2_4->Fill(cP2[4]);
  hcN1_1->Fill(cN1[1]);
  hcN1_2->Fill(cN1[2]);
  hcN1_3->Fill(cN1[3]);
  hcN1_4->Fill(cN1[4]);
  hcN2_1->Fill(cN2[1]);
  hcN2_2->Fill(cN2[2]);
  hcN2_3->Fill(cN2[3]);
  hcN2_4->Fill(cN2[4]);  
  
  TFile *Write = new TFile ("ZDCCalib_12b.root", "recreate");
  gStyle->SetOptFit();
  
  hZDCP1_ch01->Write();
  hZDCP1_ch02->Write();
  hZDCP1_ch03->Write();
  hZDCP1_ch04->Write();
  hZDCP2_ch01->Write();
  hZDCP2_ch02->Write();
  hZDCP2_ch03->Write();
  hZDCP2_ch04->Write();
  hZDCN1_ch01->Write();
  hZDCN1_ch02->Write();
  hZDCN1_ch03->Write();
  hZDCN1_ch04->Write();
  hZDCN2_ch01->Write();
  hZDCN2_ch02->Write();
  hZDCN2_ch03->Write();
  hZDCN2_ch04->Write();
  hZDCNP1->Write();
  hZDCNP2->Write();
  resP1->Write();
  resN1->Write();

  hcP1_1->Write();
  hcP1_2->Write();
  hcP1_3->Write();
  hcP1_4->Write();
  hcP2_1->Write();
  hcP2_2->Write();
  hcP2_3->Write();
  hcP2_4->Write();
  hcN1_1->Write();
  hcN1_2->Write();
  hcN1_3->Write();
  hcN1_4->Write();
  hcN2_1->Write();
  hcN2_2->Write();
  hcN2_3->Write();
  hcN2_4->Write();
   
  Write->Close();
}




 
