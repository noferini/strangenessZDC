void mctruthSPD_SD(int imc){
  const int nfile = 4;
  char *namefile[nfile] = {"LHC20i2a-Pythia8_Monash2013.root", "LHC16d3-EPOS.root", "LHC17h7a-Pythia6_Perugia2011.root", "LHC17h7b-Phojet.root"};
  
  TFile *f = new TFile(namefile[imc]);
  printf("open file %s\n",namefile[imc]);
  TTree *t = (TTree *) f->Get("fTree");
  int nev = t->GetEntries();

  int inelGT0;
  t->SetBranchAddress("inelGT0", &inelGT0);

  int nchEta;
  t->SetBranchAddress("nchEta", &nchEta);

  int npi0;
  t->SetBranchAddress("nPi0Eta", &npi0);

  float v0mPerc;
  t->SetBranchAddress("v0mPerc", &v0mPerc);

  float spdPerc;
  t->SetBranchAddress("multSPDcl", &spdPerc);

  int nmpi;
  t->SetBranchAddress("nmpi", &nmpi);

  int nLambdaEta;
  t->SetBranchAddress("nLambdaEta", &nLambdaEta);

  float sumPtLambda, sumptLambdaEta=0;
  t->SetBranchAddress("sumLambdaXi", &sumPtLambda); // bad name in task

  int nXiEta, nAntiXiEta;
  t->SetBranchAddress("nXiEta", &nXiEta);
  t->SetBranchAddress("nAntiXiEta", &nAntiXiEta);

  float ptXiEta[100], ptAntiXiEta[100], sumptXiEta=0, sumptXiEta2=0;
  t->SetBranchAddress("ptXiEta", ptXiEta);
  t->SetBranchAddress("ptAntiXiEta", ptAntiXiEta);

  int nXiEtaS;
  t->SetBranchAddress("nXiEtaFrag", &nXiEtaS);
  int nXiEtaU;
  t->SetBranchAddress("nXiEtaUp", &nXiEtaU);
  int nXiEtaD;
  t->SetBranchAddress("nXiEtaDown", &nXiEtaD);
  
  float ptXiEtaS[100], sumptXiEtaS=0;
  t->SetBranchAddress("ptXiEtaFrag", ptXiEtaS);
  float ptXiEtaU[100], sumptXiEtaU=0;
  t->SetBranchAddress("ptXiEtaUp", ptXiEtaU);
  float ptXiEtaD[100], sumptXiEtaD=0;
  t->SetBranchAddress("ptXiEtaDown", ptXiEtaD);

  int nOmegaEta;
  t->SetBranchAddress("nOmegaEta", &nOmegaEta);

  float effEnergy;
  t->SetBranchAddress("effEnergy", &effEnergy);

  float adcZDCN1[5],adcZDCN2[5],adcZDCP1[5],adcZDCP2[5];
  t->SetBranchAddress("adcZDCN1", adcZDCN1);
  t->SetBranchAddress("adcZDCN2", adcZDCN2);
  t->SetBranchAddress("adcZDCP1", adcZDCP1);
  t->SetBranchAddress("adcZDCP2", adcZDCP2);

  const int nbinMult = 10;
  double binMult[nbinMult+1] = {0,1.5,2.2,3.3,4.5,6.5,9,12,18,27,100};

  const int nbinZDC = 1;
//  double binZDC[nbinZDC+1] = {0,15,22,33,45,65,90,120,180,270,13000};
  double binZDC[nbinZDC+1] = {0,100};//,20,30,40,50,60,70,80,90,100};

  int nMB = 0;
  float multMB = 0;
  float zdcMB = 0;
  float xiMB = 0;
  float xiSMB = 0;
  float leadMB = 0;
  float lambdaMB = 0;

  TProfile *hZDCvsEE = new TProfile("hZDCvsEE",";EE; ZDC sum",100,0,13000);
  TH1F *hCumMult = new TH1F("hCumMult","",1000,0,100);
//  TH1F *hCumZDC = new TH1F("hCumZDC","",100,0,13000);
  TH1F *hCumZDC = new TH1F("hCumZDC","",404,0,101);

  for(int i=0; i < nev; i++){
    t->GetEvent(i);
    if(!inelGT0) continue;
    leadMB += -effEnergy;

    effEnergy += 13000;

    hCumMult->Fill(spdPerc);// nchEta);
    hCumZDC->Fill(v0mPerc);//effEnergy);//adcZDCN1[0] + adcZDCN2[0] + adcZDCP1[0] + adcZDCP2[0]);
    
    hZDCvsEE->Fill(effEnergy, adcZDCN1[0] + adcZDCN2[0] + adcZDCP1[0] + adcZDCP2[0]);

    nMB++;
    multMB += nchEta;
    zdcMB += adcZDCN1[0] + adcZDCN2[0] + adcZDCP1[0] + adcZDCP2[0];

    xiMB += nXiEta + nAntiXiEta;
    xiSMB += nXiEtaS;

    lambdaMB += nLambdaEta;
  }

  multMB /= nMB;
  zdcMB /= nMB;
  xiMB /= nMB;
  xiSMB /= nMB;
  leadMB /= nMB;
  lambdaMB /= nMB;

  printf("xiMB = %f\n",xiMB);
  
  xiMB /= multMB;
  xiSMB /= multMB;
  lambdaMB /= multMB;

  printf("xiMB/multMB = %f\n",xiMB);

  for(int i=2; i <= hCumMult->GetNbinsX(); i++){
    hCumMult->AddBinContent(i, hCumMult->GetBinContent(i-1));
  }
  hCumMult->Scale(1./hCumMult->GetBinContent(hCumMult->GetNbinsX()));
  hCumMult->Draw();

  for(int i=2; i <= hCumZDC->GetNbinsX(); i++){
    hCumZDC->AddBinContent(i, hCumZDC->GetBinContent(i-1));
  }
  hCumZDC->Scale(1./hCumZDC->GetBinContent(hCumZDC->GetNbinsX()));
  hCumZDC->Draw();

  int ibin = 1;
  for(int i = 1; i < nbinMult; i++){
    while(hCumMult->GetBinContent(ibin) < i*1. / nbinMult){
      ibin++;
    }
    binMult[i] = hCumMult->GetBinCenter(ibin)+hCumMult->GetBinWidth(ibin)*0.5;
    printf("Mult(%d) %f\n",i,binMult[i]);
  }

  ibin = 1;
  for(int i = 1; i < nbinZDC; i++){
    while(hCumZDC->GetBinContent(ibin) < i*1. / nbinZDC){
      ibin++;
    }
    binZDC[i] = hCumZDC->GetBinCenter(ibin)+hCumZDC->GetBinWidth(ibin)*0.5;//65;
    printf("Lead(%d) %f\n",i,binZDC[i]);
  }

  TH2F *hEEvsMult = new TH2F("hEEvsMult","",nbinMult,binMult,nbinZDC,binZDC);

  const int nsel = nbinMult * nbinZDC;
  int nEv[nsel];
  float xmult[nsel],exmult[nsel];
  float xzdc[nsel],exzdc[nsel];
  float xXi[nsel], exXi[nsel];
  float xXiS[nsel], exXiS[nsel];
  float xXiPtS[nsel], exXiPtS[nsel];
  float xXiPt[nsel], exXiPt[nsel];
  float xlead[nsel], exlead[nsel];
  float xLambda[nsel], exLambda[nsel];
  float xnmpi[nsel], exnmpi[nsel];

  for(int i=0; i < nsel; i++){
    nEv[i] = 0;
    xmult[i] = exmult[i] = 0;
    xzdc[i] = exzdc[i] = 0;
    xXi[i] = exXi[i] = 0;
    xXiS[i] = exXiS[i] = 0;
    xXiPtS[i] = exXiPtS[i] = 0;
    xXiPt[i] = exXiPt[i] = 0;
    xlead[i] = exlead[i] = 0;
    xLambda[i] = exLambda[i] = 0;
    xnmpi[i] = exnmpi[i] = 0;
  }
  
  for(int i=0; i < nev; i++){
    t->GetEvent(i);
    if(!inelGT0) continue;

    effEnergy += 13000;
    sumptXiEta = sumptXiEta2 = 0;

    for(int j=0; j < nXiEta; j++){
      sumptXiEta += ptXiEta[j];
      sumptXiEta2 += ptXiEta[j]*ptXiEta[j];
    }
    for(int j=0; j < nAntiXiEta; j++){
      sumptXiEta += ptAntiXiEta[j];
      sumptXiEta2 += ptAntiXiEta[j]*ptAntiXiEta[j];
    }
    nXiEta += nAntiXiEta;
    sumptLambdaEta += sumPtLambda;
    
    hEEvsMult->Fill(spdPerc, v0mPerc);//hZDCvsEE->Interpolate(effEnergy));
    int imult = hEEvsMult->GetXaxis()->FindBin(spdPerc/*nchEta*/)-1;
    int iee = hEEvsMult->GetYaxis()->FindBin(v0mPerc)-1;//effEnergy);
    int isel = imult * nbinZDC;// + iee;
    float sumzdc = adcZDCN1[0] + adcZDCN2[0] + adcZDCP1[0] + adcZDCP2[0];
    
    if(imult >= 0 && imult < nbinMult){ // selections
      nEv[isel]++;
      xmult[isel] += nchEta;
      exmult[isel] += nchEta*nchEta;
      xzdc[isel] += sumzdc;
      exzdc[isel] += sumzdc*sumzdc;
      xXi[isel] += nXiEta;
      exXi[isel] += nXiEta*nXiEta;
      xXiS[isel] += nXiEtaS;
      exXiS[isel] += nXiEtaS*nXiEtaS;
      xLambda[isel] += nLambdaEta;
      exLambda[isel] += nLambdaEta*nLambdaEta;
      xlead[isel] += (13000 - effEnergy);
      exlead[isel] += (effEnergy-13000)*(effEnergy-13000);
      xnmpi[isel] += nmpi;
      exnmpi[isel] += nmpi*nmpi;
      for(int j=0; j < nXiEtaS; j++){
	xXiPtS[isel] += ptXiEtaS[j];
	exXiPtS[isel] += ptXiEtaS[j]*ptXiEtaS[j];
      }
      xXiPt[isel] += sumptXiEta;
      exXiPt[isel] += sumptXiEta2;
    }
    else {
      printf("isel = %d - mult=%d (%d and %d)\n",isel,nchEta,imult,hEEvsMult->GetXaxis()->FindBin(nchEta));
    }
  }
  hEEvsMult->Draw("colz");

  for(int i=0; i < nsel; i++){
    if(nEv[i] < 50){
      xmult[i] = exmult[i] = 0;
      xzdc[i] = exzdc[i] = 0;
      xXi[i] = exXi[i] = 0;
      xXiS[i] = exXiS[i] = 0;
      xXiPtS[i] = exXiPtS[i] = 0;
      xXiPt[i] = exXiPt[i] = 0;
      xlead[i] = exlead[i] = 0;
      xnmpi[i] = exnmpi[i] = 0;
      continue;
    }
    xnmpi[i] /= nEv[i];
    exnmpi[i] /= nEv[i];
    exnmpi[i] = sqrt(exnmpi[i] - xnmpi[i]*xnmpi[i]) / sqrt(nEv[i] - 1);
    xmult[i] /= nEv[i];
    exmult[i] /= nEv[i];
    exmult[i] = sqrt(exmult[i] - xmult[i]*xmult[i]) / sqrt(nEv[i] - 1);
    xzdc[i] /= nEv[i];
    exzdc[i] /= nEv[i];
    exzdc[i] = sqrt(exzdc[i] - xzdc[i]*xzdc[i]) / sqrt(nEv[i] - 1);
    xlead[i] /= nEv[i];
    exlead[i] /= nEv[i];
    exlead[i] = sqrt(exlead[i] - xlead[i]*xlead[i]) / sqrt(nEv[i] - 1);
    xXiPtS[i] /= xXiS[i];
    exXiPtS[i] /= xXiS[i];
    exXiPtS[i] = sqrt(exXiPtS[i] - xXiPtS[i]*xXiPtS[i]) / sqrt(xXiS[i] - 1);
    xXiPt[i] /= xXi[i];
    exXiPt[i] /= xXi[i];
    exXiPt[i] = sqrt(exXiPt[i] - xXiPt[i]*xXiPt[i]) / sqrt(xXi[i] - 1);
    xXiS[i] /= nEv[i];
    exXiS[i] /= nEv[i];
    exXiS[i] = sqrt(exXiS[i] - xXiS[i]*xXiS[i]) / sqrt(nEv[i] - 1);
    xXi[i] /= nEv[i];
    exXi[i] /= nEv[i];
    exXi[i] = sqrt(exXi[i] - xXi[i]*xXi[i]) / sqrt(nEv[i] - 1);
    xLambda[i] /= nEv[i];
    exLambda[i] /= nEv[i];
    exLambda[i] = sqrt(exLambda[i] - xLambda[i]*xLambda[i]) / sqrt(nEv[i] - 1);
    xXi[i] /= xmult[i];
    exXi[i] /= xmult[i];
    xXiS[i] /= xmult[i];
    exXiS[i] /= xmult[i];
    xLambda[i] /= xmult[i];
    exLambda[i] /= xmult[i];

    xmult[i] /= multMB;
    exmult[i] /= multMB;
    xzdc[i] /= zdcMB;
    exzdc[i] /= zdcMB;
    xlead[i] /= leadMB;
    exlead[i] /= leadMB;
    xLambda[i] /= lambdaMB;
    exLambda[i] /= lambdaMB;

    printf("%d) Xi=%f - MB=%f w=%f\n",i, xXi[i], xiMB,xmult[i]*nEv[i]);
    xXi[i] /= xiMB;
    exXi[i] /= xiMB;
    xXiS[i] /= xiSMB;
    exXiS[i] /= xiSMB;
  }

  printf("npoints = %d - %f - %f\n",nsel,binZDC[0],binZDC[1]);

  const int ngraph = 16;
  TGraphErrors *g[ngraph];
  g[0] = new TGraphErrors(nsel,xmult,xzdc,exmult,exzdc);
  g[0]->SetName("gMultZDC");
  g[1] = new TGraphErrors(nsel,xmult,xXi,exmult,exXi);
  g[1]->SetName("gMultXi");
  g[2] = new TGraphErrors(nsel,xzdc,xXi,exzdc,exXi);
  g[2]->SetName("gZDCXi");
  g[3] = new TGraphErrors(nsel,xmult,xXiS,exmult,exXiS);
  g[3]->SetName("gMultXiS");
  g[4] = new TGraphErrors(nsel,xzdc,xXiS,exzdc,exXiS);
  g[4]->SetName("gZDCXiS");
  g[5] = new TGraphErrors(nsel,xmult,xXiPtS,exmult,exXiPtS);
  g[5]->SetName("gMultXiPtS");
  g[6] = new TGraphErrors(nsel,xzdc,xXiPtS,exzdc,exXiPtS);
  g[6]->SetName("gZDCXiPtS");
  g[7] = new TGraphErrors(nsel,xmult,xXiPt,exmult,exXiPt);
  g[7]->SetName("gMultXiPt");
  g[8] = new TGraphErrors(nsel,xzdc,xXiPt,exzdc,exXiPt);
  g[8]->SetName("gZDCXiPt");
  g[9] = new TGraphErrors(nsel,xzdc,xlead,exzdc,exlead);
  g[9]->SetName("gZDCLead");
  g[10] = new TGraphErrors(nsel,xlead,xXi,exlead,exXi);
  g[10]->SetName("gLeadXi");
  g[11] = new TGraphErrors(nsel,xlead,xXiS,exlead,exXiS);
  g[11]->SetName("gLeadXiS");
  g[12] = new TGraphErrors(nsel,xmult,xLambda,exmult,exLambda);
  g[12]->SetName("gMultLambda");
  g[13] = new TGraphErrors(nsel,xzdc,xLambda,exzdc,exLambda);
  g[13]->SetName("gZDCLambda");
  g[14] = new TGraphErrors(nsel,xmult,xnmpi,exmult,exnmpi);
  g[14]->SetName("gMultNmpi");
  g[15] = new TGraphErrors(nsel,xzdc,xnmpi,exzdc,exnmpi);
  g[15]->SetName("gZDCNmpi");

  TFile *fo = new TFile(Form("mctruthSD%d_SPD.root", imc),"RECREATE");
  hZDCvsEE->Write();
  hEEvsMult->Write();
  for(int i=0; i < ngraph; i++){
    g[i]->Write();
  }
  fo->Close();
}
