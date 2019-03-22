{ 
  //12b178167pass1.root
  //12b178167pass2.root
  //12c182289pass2.root
  //12f188108pass2.root
  //18i288908pass1.root
  
  TFile * Read = new TFile ("18ipass1.root");
  TTree * T = (TTree *)Read->Get("tEvents");
  
  Int_t bin = 100;
  Double_t thrP = 0.9;
  Double_t thrP2 = 0.5;
  Double_t thrN = 0.9;
  Float_t ZDCP1[5], ZDCP1Sum, ZDCN1[5], ZDCN1Sum, ZDCP2[5], ZDCP2Sum, ZDCN2[5], ZDCN2Sum,diff,mean, diffN, meanN;
  Double_t cP1[5]={1,1,1,1,1};
  Double_t cP2[5]={1,1,1,1,1};
  Double_t cN1[5]={1,1,1,1,1};
  Double_t cN2[5]={1,1,1,1,1};
   Float_t V0M, V0A, V0C, CL0, CL1, SPDClusters, SPDTracklets, ZNA, ZNC, ZNApp, ZNCpp, RefMult08_p, RefMult05_p, V0MEstimator_p, V0CEstimator_p, V0AEstimator_p, RefMult08_abs, RefMult05_abs, V0MEstimator_abs, V0CEstimator_abs, V0AEstimator_abs;
  
  T->SetBranchAddress("adcZDCP1",ZDCP1);
  T->SetBranchAddress("adcZDCN1",ZDCN1);
  T->SetBranchAddress("adcZDCP2",ZDCP2);
  T->SetBranchAddress("adcZDCN2",ZDCN2);
  T->SetBranchAddress("V0M",&V0M);
  T->SetBranchAddress("V0A",&V0A);
  T->SetBranchAddress("V0C",&V0C);
  T->SetBranchAddress("CL0",&CL0);
  T->SetBranchAddress("CL1",&CL1);
  T->SetBranchAddress("SPDClusters",&SPDClusters);
  T->SetBranchAddress("SPDTracklets",&SPDTracklets);
  T->SetBranchAddress("ZNA",&ZNA);
  T->SetBranchAddress("ZNC",&ZNC);
  T->SetBranchAddress("ZNApp",&ZNApp);
  T->SetBranchAddress("ZNCpp",&ZNCpp);
  T->SetBranchAddress("RefMult08_p",&RefMult08_p);
  T->SetBranchAddress("RefMult05_p",&RefMult05_p);
  T->SetBranchAddress("V0MEstimator_p",&V0MEstimator_p);
  T->SetBranchAddress("V0AEstimator_p",&V0AEstimator_p);
  T->SetBranchAddress("V0CEstimator_p",&V0CEstimator_p);
  T->SetBranchAddress("RefMult08_abs",&RefMult08_abs);
  T->SetBranchAddress("RefMult05_abs",&RefMult05_abs);
  T->SetBranchAddress("V0MEstimator_abs",&V0MEstimator_abs);
  T->SetBranchAddress("V0AEstimator_abs",&V0AEstimator_abs);
  T->SetBranchAddress("V0CEstimator_abs",&V0CEstimator_abs);

  //Histos
  TH2D * hZDCNP1= new TH2D("hZDCNP1","ZDCN1[0] vs ZDCP1[0];ZDCN1[0];ZDCP1[0];",bin,-1,2000,bin,-1,2000);
  TH2D * hZDCNP2= new TH2D("hZDCNP2","ZDCN2[0] vs ZDCP2[0];ZDCN2[0];ZDCP2[0];",bin,-1,2000,bin,-1,2000);
  
  TH2D * hZDCP1_ch01= new TH2D("hZDCP1_ch01","ZDCP1[1] > 0.9*(ZDCP1[1]+ZDCP1[2]+ZDCP1[3]+ZDCP1[4]);ZDCP1[0];ZDCP1Sum;",bin,-1,2000,bin,-1,2000);
  TH2D * hZDCP1_ch02= new TH2D("hZDCP1_ch02","ZDCP1[2] > 0.8*(ZDCP1[1]+ZDCP1[2]+ZDCP1[3]+ZDCP1[4]);ZDCP1[0];ZDCP1Sum;",bin,-1,2000,bin,-1,2000);
  TH2D * hZDCP1_ch03= new TH2D("hZDCP1_ch03","ZDCP1[3] > 0.8*(ZDCP1[1]+ZDCP1[2]+ZDCP1[3]+ZDCP1[4]);ZDCP1[0];ZDCP1Sum;",bin,-1,2000,bin,-1,2000);
  TH2D * hZDCP1_ch04= new TH2D("hZDCP1_ch04","ZDCP1[4] > 0.8*(ZDCP1[1]+ZDCP1[2]+ZDCP1[3]+ZDCP1[4]);ZDCP1[0];ZDCP1Sum;",bin,-1,2000,bin,-1,2000);

  TH2D * hZDCP2_ch01= new TH2D("hZDCP2_ch01","ZDCP2[1] > 0.8*(ZDCP2[1]+ZDCP2[2]+ZDCP2[3]+ZDCP2[4]);ZDCP2[0];ZDCP2Sum;",bin,-1,2000,bin,-1,2000);
  TH2D * hZDCP2_ch02= new TH2D("hZDCP2_ch02","ZDCP2[2] > 0.8*(ZDCP2[1]+ZDCP2[2]+ZDCP2[3]+ZDCP2[4]);ZDCP2[0];ZDCP2Sum;",bin,-1,2000,bin,-1,2000);
  TH2D * hZDCP2_ch03= new TH2D("hZDCP2_ch03","ZDCP2[3] > 0.8*(ZDCP2[1]+ZDCP2[2]+ZDCP2[3]+ZDCP2[4]);ZDCP2[0];ZDCP2Sum;",bin,-1,2000,bin,-1,2000);
  TH2D * hZDCP2_ch04= new TH2D("hZDCP2_ch04","ZDCP2[4] > 0.9*(ZDCP2[1]+ZDCP2[2]+ZDCP2[3]+ZDCP2[4]);ZDCP2[0];ZDCP2Sum;",bin,-1,2000,bin,-1,2000);

  TH2D * hZDCN1_ch01= new TH2D("hZDCN1_ch01","ZDCN1[1] > 0.9*(ZDCN1[1]+ZDCN1[2]+ZDCN1[3]+ZDCN1[4]);ZDCN1[0];ZDCN1Sum;",bin,-1,2000,bin,-1,2000);
  TH2D * hZDCN1_ch02= new TH2D("hZDCN1_ch02","ZDCN1[1] > 0.9*(ZDCN1[1]+ZDCN1[2]+ZDCN1[3]+ZDCN1[4]);ZDCN1[0];ZDCN1Sum;",bin,-1,2000,bin,-1,2000);
  TH2D * hZDCN1_ch03= new TH2D("hZDCN1_ch03","ZDCN1[1] > 0.9*(ZDCN1[1]+ZDCN1[2]+ZDCN1[3]+ZDCN1[4]);ZDCN1[0];ZDCN1Sum;",bin,-1,2000,bin,-1,2000);
  TH2D * hZDCN1_ch04= new TH2D("hZDCN1_ch04","ZDCN1[1] > 0.9*(ZDCN1[1]+ZDCN1[2]+ZDCN1[3]+ZDCN1[4]);ZDCN1[0];ZDCN1Sum;",bin,-1,2000,bin,-1,2000);
  
  TH2D * hZDCN2_ch01= new TH2D("hZDCN2_ch01","ZDCN2[1] > 0.9*(ZDCN2[1]+ZDCN2[2]+ZDCN2[3]+ZDCN2[4]);ZDCN2[0];ZDCN2Sum;",bin,-1,2000,bin,-1,2000);
  TH2D * hZDCN2_ch02= new TH2D("hZDCN2_ch02","ZDCN2[2] > 0.9*(ZDCN2[1]+ZDCN2[2]+ZDCN2[3]+ZDCN2[4]);ZDCN2[0];ZDCN2Sum;",bin,-1,2000,bin,-1,2000);
  TH2D * hZDCN2_ch03= new TH2D("hZDCN2_ch03","ZDCN2[3] > 0.9*(ZDCN2[1]+ZDCN2[2]+ZDCN2[3]+ZDCN2[4]);ZDCN2[0];ZDCN2Sum;",bin,-1,2000,bin,-1,2000);
  TH2D * hZDCN2_ch04= new TH2D("hZDCN2_ch04","ZDCN2[4] > 0.9*(ZDCN2[1]+ZDCN2[2]+ZDCN2[3]+ZDCN2[4]);ZDCN2[0];ZDCN2Sum;",bin,-1,2000,bin,-1,2000);

   TH2D * resP1= new TH2D("resP1","Resolution P1;sum-common (GeV);(sum+common)/2 (GeV);",bin,-1,2000,bin,-1000,1000);
   TH2D * resN1= new TH2D("resN1","Resolution N1;sum+comm /2 ;sum-common ;",bin,-1,2000,bin,-1000,1000);
   //TH2D * hZDCP1Ref8= new TH2D("hZDCP1Ref8","title;ZDCP1[0];Ref8;",500,-1,2000,500,-1,700);
   TH2D *hNCV0A = new TH2D("hNCV0A",";ZDCN-C[0];V0A;",100,-1,2000,100,-1,700);
   TH2D *hNCV0C = new TH2D("hNCV0C",";ZDCN-C[0];V0C;",100,-1,2000,100,-1,700);
   TH2D *hNCV0M = new TH2D("hNCV0M",";ZDCN-C[0];V0M;",100,-1,2000,100,-1,700);
   TH2D *hNCeta8 = new TH2D("hNCeta8",";ZDCN-C[0];RefMult08;",100,-1,2000,100,-1,700);
   TH2D *hPCV0A = new TH2D("hPCV0A",";ZDCP-C[0];V0A;",100,-1,2000,100,-1,700);
   TH2D *hPCV0C = new TH2D("hPCV0C",";ZDCP-C[0];V0C;",100,-1,2000,100,-1,700);
   TH2D *hPCV0M = new TH2D("hPCV0M",";ZDCP-C[0];V0M;",100,-1,2000,100,-1,700);
   TH2D *hPCeta8 = new TH2D("hPCeta8",";ZDCP-C[0];RefMult08;",100,-1,2000,100,-1,700);
   TH2D *totCV0M = new TH2D("totCV0M",";ZDCP-C[0]+ZDCN-C[0];V0M;",100,-1,2000,100,-1,700);
   TH2D *totCeta8 = new TH2D("totCeta8",";ZDCP-C[0]+ZDCN-C[0];RefMult08;",100,-1,2000,100,-1,700);
   TH2D *totCV0A = new TH2D("totCV0A",";ZDCP-C[0]+ZDCN-C[0];V0A;",100,-1,2000,100,-1,700);
   TH2D *totCV0C = new TH2D("totCV0C",";ZDCP-C[0]+ZDCN-C[0];V0C;",100,-1,2000,100,-1,700);
   TH2D *ACV0M = new TH2D("ACV0M",";ZDCP+ZDCN;V0M;",100,-1,5000,100,-1,700);
   TH2D *ACeta8 = new TH2D("ACeta8",";ZDCP+ZDC;RefMult08;",100,-1,5000,100,-1,700);
   TH2D *ACV0A = new TH2D("ACV0A",";ZDCP+ZDCN;V0A;",100,-1,5000,100,-1,700);
   TH2D *ACV0C = new TH2D("ACV0C",";ZDCP+ZDCN;V0C;",100,-1,5000,100,-1,700);

  for (Int_t k=0; k<5; k++)//iterations for calibration
    {
      for(Int_t i=0; i<T->GetEntries();i++)//loop over Tree entries
	{
	  T->GetEvent(i);
	  
	  //P1
	  ZDCP1Sum = ZDCP1[1]/cP1[1]+ZDCP1[2]/cP1[2]+ZDCP1[3]/cP1[3]+ZDCP1[4]/cP1[4];
	  //hZDCP10Sum->Fill(ZDCP1[0],ZDCP1Sum);
	  if (ZDCP1[1]>(thrP* (ZDCP1[1]+ZDCP1[2]+ZDCP1[3]+ZDCP1[4]))) hZDCP1_ch01->Fill(ZDCP1[0],ZDCP1Sum); 
	  if (ZDCP1[2]>(thrP2*(ZDCP1[1]+ZDCP1[2]+ZDCP1[3]+ZDCP1[4]))) hZDCP1_ch02->Fill(ZDCP1[0],ZDCP1Sum); 
	  if (ZDCP1[3]>(thrP2*(ZDCP1[1]+ZDCP1[2]+ZDCP1[3]+ZDCP1[4]))) hZDCP1_ch03->Fill(ZDCP1[0],ZDCP1Sum); 
	  if (ZDCP1[4]>(thrP2*(ZDCP1[1]+ZDCP1[2]+ZDCP1[3]+ZDCP1[4]))) hZDCP1_ch04->Fill(ZDCP1[0],ZDCP1Sum); 
          //P2
	  ZDCP2Sum=ZDCP2[1]/cP2[1]+ZDCP2[2]/cP2[2]+ZDCP2[3]/cP2[3]+ZDCP2[4]/cP2[4];;
	  //hZDCP20Sum->Fill(ZDCP2[0],ZDCP2Sum);
	  if (ZDCP2[1]>(thrP2*(ZDCP2[1]+ZDCP2[2]+ZDCP2[3]+ZDCP2[4]))) hZDCP2_ch01->Fill(ZDCP2[0],ZDCP2Sum);
	  if (ZDCP2[2]>(thrP2*(ZDCP2[1]+ZDCP2[2]+ZDCP2[3]+ZDCP2[4]))) hZDCP2_ch02->Fill(ZDCP2[0],ZDCP2Sum);
	  if (ZDCP2[3]>(thrP2*(ZDCP2[1]+ZDCP2[2]+ZDCP2[3]+ZDCP2[4]))) hZDCP2_ch03->Fill(ZDCP2[0],ZDCP2Sum);
	  if (ZDCP2[4]>(thrP* (ZDCP2[1]+ZDCP2[2]+ZDCP2[3]+ZDCP2[4]))) hZDCP2_ch04->Fill(ZDCP2[0],ZDCP2Sum);
	  //N1
	  ZDCN1Sum=ZDCN1[1]/cN1[1]+ZDCN1[2]/cN1[2]+ZDCN1[3]/cN1[3]+ZDCN1[4]/cN1[4];
	  //hZDCN10Sum->Fill(ZDCN1[0],ZDCN1Sum);
	  if (ZDCN1[1]>(thrN*(ZDCN1[1]+ZDCN1[2]+ZDCN1[3]+ZDCN1[4]))) hZDCN1_ch01->Fill(ZDCN1[0],ZDCN1Sum);
	  if (ZDCN1[2]>(thrN*(ZDCN1[1]+ZDCN1[2]+ZDCN1[3]+ZDCN1[4]))) hZDCN1_ch02->Fill(ZDCN1[0],ZDCN1Sum); 
	  if (ZDCN1[3]>(thrN*(ZDCN1[1]+ZDCN1[2]+ZDCN1[3]+ZDCN1[4]))) hZDCN1_ch03->Fill(ZDCN1[0],ZDCN1Sum); 
	  if (ZDCN1[4]>(thrN*(ZDCN1[1]+ZDCN1[2]+ZDCN1[3]+ZDCN1[4]))) hZDCN1_ch04->Fill(ZDCN1[0],ZDCN1Sum); 
	  //N2
	  ZDCN2Sum=ZDCN2[1]/cN2[1]+ZDCN2[2]/cN2[2]+ZDCN2[3]/cN2[3]+ZDCN2[4]/cN2[4];
	  //hZDCN20Sum->Fill(ZDCN2[0],ZDCN2Sum);
	  if (ZDCN2[1]>(thrN*(ZDCN2[1]+ZDCN2[2]+ZDCN2[3]+ZDCN2[4]))) hZDCN2_ch01->Fill(ZDCN2[0],ZDCN2Sum); 
	  if (ZDCN2[2]>(thrN*(ZDCN2[1]+ZDCN2[2]+ZDCN2[3]+ZDCN2[4]))) hZDCN2_ch02->Fill(ZDCN2[0],ZDCN2Sum); 
	  if (ZDCN2[3]>(thrN*(ZDCN2[1]+ZDCN2[2]+ZDCN2[3]+ZDCN2[4]))) hZDCN2_ch03->Fill(ZDCN2[0],ZDCN2Sum); 
	  if (ZDCN2[4]>(thrN*(ZDCN2[1]+ZDCN2[2]+ZDCN2[3]+ZDCN2[4]))) hZDCN2_ch04->Fill(ZDCN2[0],ZDCN2Sum); 
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
	  // hZDCP1Ref8->Fill(ZDCP1[0],V0MEstimator_abs);

	  //Pcut
	  if(ZDCP1[0]<100)
	    {
	      hNCV0A->Fill(ZDCN1[0],V0AEstimator_abs);
	      hNCV0C->Fill(ZDCN1[0],V0CEstimator_abs);
	      hNCV0M->Fill(ZDCN1[0],V0MEstimator_abs);
	      hNCeta8->Fill(ZDCN1[0],RefMult08_abs);
	    }

	  //Ncut
	  if(ZDCN1[0]<20)
	    {
	      hPCV0A->Fill(ZDCP1[0],V0AEstimator_abs);
	      hPCV0C->Fill(ZDCP1[0],V0CEstimator_abs);
	      hPCV0M->Fill(ZDCP1[0],V0MEstimator_abs);
	      hPCeta8->Fill(ZDCP1[0],RefMult08_abs);
	    }
	  
	  totCV0M->Fill(ZDCN1[0]+ZDCP1[0],V0MEstimator_abs);
	  totCeta8->Fill(ZDCN1[0]+ZDCP1[0],RefMult08_abs);
	  totCV0A->Fill(ZDCN1[0]+ZDCP1[0],V0AEstimator_abs);
	  totCV0C->Fill(ZDCN1[0]+ZDCP1[0],V0CEstimator_abs);
	  ACV0M->Fill(ZDCN1[0]+ZDCP1[0]+ZDCN2[0]+ZDCP2[0],V0MEstimator_abs);
	  ACeta8->Fill(ZDCN1[0]+ZDCP1[0]+ZDCN2[0]+ZDCP2[0],RefMult08_abs);
	  ACV0A->Fill(ZDCN1[0]+ZDCP1[0]+ZDCN2[0]+ZDCP2[0],V0AEstimator_abs);
	  ACV0C->Fill(ZDCN1[0]+ZDCP1[0]+ZDCN2[0]+ZDCP2[0],V0CEstimator_abs);
	  
	  
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

  //ZDCCal12bpass1.root
  //ZDCCal12bpass2.root
  //ZDCCal12cpass2.root
  //ZDCCal12fpass2.root
  //ZDCCal18ipass1.root
  
  TFile *Write = new TFile ("prova18i.root", "recreate");
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
  // hZDCP1Ref8->Write();
  
  hNCV0A->Write();
  hNCV0A->ProfileY();
  hNCV0A->ProfileX();
  hNCV0A_pfy->Write();
  hNCV0A_pfx->Write();
  

  hNCV0C->Write();
  hNCV0C->ProfileY();
  hNCV0C->ProfileX();
  hNCV0C_pfy->Write();
  hNCV0C_pfx->Write();
  
  hNCV0M->Write();
  hNCV0M->ProfileY();
  hNCV0M->ProfileX();
  hNCV0M_pfy->Write();
  hNCV0M_pfx->Write();
  
  hNCeta8->Write();
  hNCeta8->ProfileY();
  hNCeta8->ProfileX();
  hNCeta8_pfy->Write();
  hNCeta8_pfx->Write();
  
  hPCV0A->Write();
  hPCV0A->ProfileY();
  hPCV0A->ProfileX();
  hPCV0A_pfy->Write();
  hPCV0A_pfx->Write();
  
  hPCV0C->Write();
  hPCV0C->ProfileY();
  hPCV0C->ProfileX();
  hPCV0C_pfy->Write();
  hPCV0C_pfx->Write();
  
  hPCV0M->Write();
  hPCV0M->ProfileY();
  hPCV0M->ProfileX();
  hPCV0M_pfy->Write();
  hPCV0M_pfx->Write();
  
  hPCeta8->Write();
  hPCeta8->ProfileY();
  hPCeta8->ProfileX();
  hPCeta8_pfy->Write();
  hPCeta8_pfx->Write();
  
  totCV0M->Write();
  totCV0M ->ProfileY();
  totCV0M->ProfileX();
  totCV0M_pfy->Write();
  totCV0M_pfx->Write();
  
  totCeta8->Write();
  totCeta8->ProfileY();
  totCeta8->ProfileX();
  totCeta8_pfy->Write();
  totCeta8_pfx->Write();
    
  totCV0A->Write();
  totCV0A ->ProfileY();
  totCV0A->ProfileX();
  totCV0A_pfy->Write();
  totCV0A_pfx->Write();
    
  totCV0C->Write();
  totCV0C ->ProfileY();
  totCV0C->ProfileX();
  totCV0C_pfy->Write();
  totCV0C_pfx->Write();

  ACV0M->Write();
  ACV0M ->ProfileY();
  ACV0M->ProfileX();
  ACV0M_pfy->Write();
  ACV0M_pfx->Write();
  
  ACeta8->Write();
  ACeta8->ProfileY();
  ACeta8->ProfileX();
  ACeta8_pfy->Write();
  ACeta8_pfx->Write();
    
  ACV0A->Write();
  ACV0A ->ProfileY();
  ACV0A->ProfileX();
  ACV0A_pfy->Write();
  ACV0A_pfx->Write();
    
  ACV0C->Write();
  ACV0C ->ProfileY();
  ACV0C->ProfileX();
  ACV0C_pfy->Write();
  ACV0C_pfx->Write();

  
  
  //cP1[5]->Wrire();
  //cP2[5]->Write();
  //cN1[5]->Write();
  //cN2[5]->Write();
  
      
   
  Write->Close();
}




 
