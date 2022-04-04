void drawselcomp(int imc=0, const char* histo="gMultXiS", const char* histo2="gZDCXiS"){
  int multSel[2] = {8,5};
  int eeSel[2] = {1,4};
  TFile *f = new TFile(Form("mctruth%d.root",imc));
  TGraphErrors *g = (TGraphErrors *) f->Get(histo);
  TGraphErrors *gbis = (TGraphErrors *) f->Get(histo2);

  TFile *f2 = new TFile(Form("mctruthSD%d.root",imc));
  TGraphErrors *gsd = (TGraphErrors *) f2->Get(histo);
  TGraphErrors *gsd2 = (TGraphErrors *) f2->Get(histo2);

  // data
  TFile *fd100 = new TFile("XiYieldsV0M_SelectedWithSPDClusters0100.root");
  TGraphErrors	*gd1a = (TGraphErrors *) fd100->Get("NormYieldsNormNchStat");
  TGraphErrors	*gd1b = (TGraphErrors *) fd100->Get("NormYieldsNormZDCSumStat");
  TFile *fd1020S = new TFile("XiYieldsV0M_SelectedWithSPDClusters1020.root");
  TGraphErrors  *gd2a = (TGraphErrors *) fd1020S->Get("NormYieldsNormNchStat");
  TGraphErrors  *gd2b = (TGraphErrors *) fd1020S->Get("NormYieldsNormZDCSumStat");
  TFile *fd4050S = new TFile("XiYieldsV0M_SelectedWithSPDClusters4050.root");
  TGraphErrors  *gd3a = (TGraphErrors *) fd4050S->Get("NormYieldsNormNchStat");
  TGraphErrors  *gd3b = (TGraphErrors *) fd4050S->Get("NormYieldsNormZDCSumStat");
  TFile *fd1020V = new TFile("XiYieldsSPDClusters_SelectedWithV0M1020.root");
  TGraphErrors  *gd4a = (TGraphErrors *) fd1020V->Get("NormYieldsNormNchStat");
  TGraphErrors  *gd4b = (TGraphErrors *) fd1020V->Get("NormYieldsNormZDCSumStat");
  TFile *fd4050V = new TFile("XiYieldsSPDClusters_SelectedWithV0M4050.root");
  TGraphErrors  *gd5a = (TGraphErrors *) fd4050V->Get("NormYieldsNormNchStat");
  TGraphErrors  *gd5b = (TGraphErrors *) fd4050V->Get("NormYieldsNormZDCSumStat");

  gsd->SetMarkerStyle(20);
  gsd2->SetMarkerStyle(20);
  gsd->SetMarkerSize(2);
  gsd2->SetMarkerSize(2);


  int nMultSel[2] = {0,0};
  int nEeSel[2] = {0,0};

  float xMultSel[2][100];
  float yMultSel[2][100];
  float exMultSel[2][100];
  float eyMultSel[2][100];
  float xEeSel[2][100];
  float yEeSel[2][100];
  float exEeSel[2][100];
  float eyEeSel[2][100];

  float xmin = 10000;
  float xmax = -1;
  float ymin = 10000;
  float ymax = -1;

  for(int i=0; i < g->GetN(); i++){
    float x = g->GetX()[i];
    float ex = g->GetEX()[i];
    float y = g->GetY()[i];
    float ey = g->GetEY()[i];

    if(ymin > y && y > 0.1E-6) ymin=y;
    if(ymax < y) ymax=y;
    if(xmin > x && x > 0.1E-6) xmin=x;
    if(xmax < x) xmax=x;

    int iMult = i/10;
    int iEe = i%10;

    printf("%d: %d %d -> %f %f\n",i,iMult,iEe,x ,y);

    if(iMult == multSel[0]){
      xMultSel[0][nMultSel[0]] = x;
      exMultSel[0][nMultSel[0]] = ex;
      yMultSel[0][nMultSel[0]] = y;
      eyMultSel[0][nMultSel[0]] = ey;
      nMultSel[0]++;
    }
    if(iMult == multSel[1] && x > 0){
      xMultSel[1][nMultSel[1]] = x;
      exMultSel[1][nMultSel[1]] = ex;
      yMultSel[1][nMultSel[1]] = y;
      eyMultSel[1][nMultSel[1]] = ey;
      nMultSel[1]++;
    }
    if(iEe == eeSel[0] && x > 0){
      xEeSel[0][nEeSel[0]] = x;
      exEeSel[0][nEeSel[0]] = ex;
      yEeSel[0][nEeSel[0]] = y;
      eyEeSel[0][nEeSel[0]] = ey;
      nEeSel[0]++;
    }
    if(iEe == eeSel[1] && x > 0){
      xEeSel[1][nEeSel[1]] = x;
      exEeSel[1][nEeSel[1]] = ex;
      yEeSel[1][nEeSel[1]] = y;
      eyEeSel[1][nEeSel[1]] = ey;
      nEeSel[1]++;
    }

  }

  printf("%d %d %d %d\n",nMultSel[0],nMultSel[1],nEeSel[0],nEeSel[1]);

  TGraphErrors *g1 = new TGraphErrors(nMultSel[0], xMultSel[0], yMultSel[0], exMultSel[0], eyMultSel[0]);
  TGraphErrors *g2 = new TGraphErrors(nMultSel[1], xMultSel[1], yMultSel[1], exMultSel[1], eyMultSel[1]);
  TGraphErrors *g3 = new TGraphErrors(nEeSel[0], xEeSel[0], yEeSel[0], exEeSel[0], eyEeSel[0]);
  TGraphErrors *g4 = new TGraphErrors(nEeSel[1], xEeSel[1], yEeSel[1], exEeSel[1], eyEeSel[1]);

  g1->SetMarkerStyle(20);
  g2->SetMarkerStyle(24);
  g3->SetMarkerStyle(20);
  g4->SetMarkerStyle(24);
  g1->SetMarkerSize(2);
  g2->SetMarkerSize(2);
  g3->SetMarkerSize(2);
  g4->SetMarkerSize(2);
  g1->SetMarkerColor(2);
  g2->SetMarkerColor(2);
  g3->SetMarkerColor(4);
  g4->SetMarkerColor(4);
  g1->SetLineColor(2);
  g2->SetLineColor(2);
  g3->SetLineColor(4);
  g4->SetLineColor(4);

  TCanvas *c = new TCanvas;
  c->Divide(2,1);
  c->cd(1);
  TH1F *hb = new TH1F("hb",";<N_{ch}> / <N_{ch}>_{MB}",100,xmin*0.,xmax*1.5);
  hb->SetStats(0);
  hb->SetMaximum(2);
  hb->SetMinimum(0);
  hb->Draw();
  g1->Draw("P,SAME");
  g2->Draw("P,SAME");
  g3->Draw("P,SAME");
  g4->Draw("P,SAME");

  gd1a->Draw("L");
  gd1a->SetLineWidth(5);
  gd2a->Draw("L");
  gd2a->SetLineWidth(5);
  gd2a->SetLineColor(2);
  gd3a->Draw("L");
  gd3a->SetLineWidth(5);
  gd3a->SetLineColor(2);
  gd4a->Draw("L");
  gd4a->SetLineWidth(5);
  gd4a->SetLineColor(4);
  gd5a->Draw("L");
  gd5a->SetLineWidth(5);
  gd5a->SetLineColor(4);

  xmin = 10000;
  xmax = -1;
  ymin = 10000;
  ymax = -1;
  
  g=gbis;
  nMultSel[0] = 0;
  nEeSel[0] = 0;
  nMultSel[1] = 0;
  nEeSel[1] = 0;

  for(int i=0; i < g->GetN(); i++){
    float x = g->GetX()[i];
    float ex = g->GetEX()[i];
    float y = g->GetY()[i];
    float ey = g->GetEY()[i];

    if(ymin > y && y > 0.1E-6) ymin=y;
    if(ymax < y) ymax=y;
    if(xmin > x && x > 0.1E-6) xmin=x;
    if(xmax < x) xmax=x;

    int iMult = i/10;
    int iEe = i%10;

    printf("%d: %d %d -> %f %f\n",i,iMult,iEe,x ,y);

    if(iMult == multSel[0]){
      xMultSel[0][nMultSel[0]] = x;
      exMultSel[0][nMultSel[0]] = ex;
      yMultSel[0][nMultSel[0]] = y;
      eyMultSel[0][nMultSel[0]] = ey;
      nMultSel[0]++;
    }
    if(iMult == multSel[1] && x > 0){
      xMultSel[1][nMultSel[1]] = x;
      exMultSel[1][nMultSel[1]] = ex;
      yMultSel[1][nMultSel[1]] = y;
      eyMultSel[1][nMultSel[1]] = ey;
      nMultSel[1]++;
    }
    if(iEe == eeSel[0] && x > 0){
      xEeSel[0][nEeSel[0]] = x;
      exEeSel[0][nEeSel[0]] = ex;
      yEeSel[0][nEeSel[0]] = y;
      eyEeSel[0][nEeSel[0]] = ey;
      nEeSel[0]++;
    }
    if(iEe == eeSel[1] && x > 0){
      xEeSel[1][nEeSel[1]] = x;
      exEeSel[1][nEeSel[1]] = ex;
      yEeSel[1][nEeSel[1]] = y;
      eyEeSel[1][nEeSel[1]] = ey;
      nEeSel[1]++;
    }

  }

  printf("%d %d %d %d\n",nMultSel[0],nMultSel[1],nEeSel[0],nEeSel[1]);

  TGraphErrors *ga1=g1,*ga2=g2,*ga3=g3,*ga4=g4;

  c->cd(2);
  g1 = new TGraphErrors(nMultSel[0], xMultSel[0], yMultSel[0], exMultSel[0], eyMultSel[0]);
  g2 = new TGraphErrors(nMultSel[1], xMultSel[1], yMultSel[1], exMultSel[1], eyMultSel[1]);
  g3 = new TGraphErrors(nEeSel[0], xEeSel[0], yEeSel[0], exEeSel[0], eyEeSel[0]);
  g4 = new TGraphErrors(nEeSel[1], xEeSel[1], yEeSel[1], exEeSel[1], eyEeSel[1]);

  g1->SetMarkerStyle(20);
  g2->SetMarkerStyle(24);
  g3->SetMarkerStyle(20);
  g4->SetMarkerStyle(24);
  g1->SetMarkerSize(2);
  g2->SetMarkerSize(2);
  g3->SetMarkerSize(2);
  g4->SetMarkerSize(2);
  g1->SetMarkerColor(2);
  g2->SetMarkerColor(2);
  g3->SetMarkerColor(4);
  g4->SetMarkerColor(4);
  g1->SetLineColor(2);
  g2->SetLineColor(2);
  g3->SetLineColor(4);
  g4->SetLineColor(4);
  gsd->Draw("P,SAME");

  hb = new TH1F("hb2",";<ZDC sum> / <ZDC sum>_{MB}",100,xmin*0.,xmax*1.5);
  hb->SetStats(0);
  hb->SetMaximum(2);
  hb->SetMinimum(0);
  hb->Draw();
  g1->Draw("P,SAME");
  g2->Draw("P,SAME");
  g3->Draw("P,SAME");
  g4->Draw("P,SAME");
  gsd2->Draw("P,SAME");

  gd1b->Draw("L");
  gd1b->SetLineWidth(5);
  gd2b->Draw("L");
  gd2b->SetLineWidth(5);
  gd2b->SetLineColor(2);
  gd3b->Draw("L");
  gd3b->SetLineWidth(5);
  gd3b->SetLineColor(2);
  gd4b->Draw("L");
  gd4b->SetLineWidth(5);
  gd4b->SetLineColor(4);
  gd5b->Draw("L");
  gd5b->SetLineWidth(5);
  gd5b->SetLineColor(4);

  TFile *fout = new TFile(Form("comparison%d.root",imc), "RECREATE");
  gsd->SetName("gV0M0100M");
  gsd->SetTitle(";mult");
  gsd->Write();
  gsd2->SetName("gV0M0100Z");
  gsd2->SetTitle(";lead");
  gsd2->Write();
  ga1->SetName("gSPD1020M");
  ga1->SetTitle(";mult");
  ga1->Write();
  ga2->SetName("gSPD4050M");
  ga2->SetTitle(";mult");
  ga2->Write();
  ga3->SetName("gV0M1020M");
  ga3->SetTitle(";mult");
  ga3->Write();
  ga4->SetName("gV0M4050M");
  ga4->SetTitle(";mult");
  ga4->Write();
  g1->SetName("gSPD1020Z");
  g1->SetTitle(";lead");
  g1->Write();
  g2->SetName("gSPD4050Z");
  g2->SetTitle(";lead");
  g2->Write();
  g3->SetName("gV0M1020Z");
  g3->SetTitle(";lead");
  g3->Write();
  g4->SetName("gV0M4050Z");
  g4->SetTitle(";lead");
  g4->Write();

  gd1a->SetName("gDataM");
  gd1a->Write();
  gd2a->SetName("gDataSPD1020M");
  gd2a->Write();
  gd3a->SetName("gDataSPD4050M");
  gd3a->Write();
  gd4a->SetName("gDataV0M1020M");
  gd4a->Write();
  gd5a->SetName("gDataV0M4050M");
  gd5a->Write();
  gd1b->SetName("gDataZ");
  gd1b->Write();
  gd2b->SetName("gDataSPD1020Z");
  gd2b->Write();
  gd3b->SetName("gDataSPD4050Z");
  gd3b->Write();
  gd4b->SetName("gDataV0M1020Z");
  gd4b->Write();
  gd5b->SetName("gDataV0M4050Z");
  gd5b->Write();
  fout->Close();
}
