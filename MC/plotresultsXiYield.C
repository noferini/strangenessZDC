/*
classes:
0 --> v0m standalone
1 --> SPD 1020
2 --> SPD 4050
3 --> V0M 1020
4 --> V0M 4050
*/

void draw(TGraphErrors *gD, TGraphErrors *gS, int sD=kFullDiamond, int color=kBlack){
  gD->SetMarkerStyle(sD);
  gD->SetMarkerSize(3.8);
  gD->SetMarkerColor(color);
  gD->SetLineColor(color);

  if(gS){
    gS->SetLineColor(color);
    gS->SetLineWidth(3);
    
    for(int i=gS->GetN() - 1; i> 0; i--){
      if(gS->GetX()[i] < 0.1){
	gS->RemovePoint(i);
      }
    }
      
    gS->Draw("L SAME");
  }
  gD->Draw("SAME EP");
}

void plotresultsXiYield(int imc=0,bool s1020=true, bool s4050=true, bool v1020=true, bool v4050=true){
  bool sa=true;
  
  char *mcname[5] = {"Pythia8 Monash", "EPOS", "Pythia6 Perugia", "Phojet", "Pythia8 Ropes"};
  TFile *finput = new TFile(Form("comparison%d.root",imc));
  if(imc > 3) finput = new TFile(Form("comparison%d.root",0));

  TFile *fExt = 0;
  if(imc > 3){
    fExt = new TFile("myoutput.root");
  }
  
  TGraphErrors *gdata[5] = {0, 0, 0, 0, 0};
  TGraphErrors *gmc[5] = {0, 0, 0, 0, 0};
  TGraphErrors *gdataZ[5] = {0, 0, 0, 0, 0};
  TGraphErrors *gmcZ[5] = {0, 0, 0, 0, 0};

  int nlab = sa + s1020 + s4050 + v1020 + v4050;
  
  TPaveText *text = new TPaveText(0.5, 1.7 - 0.06*nlab, 2,1.7);
  text->SetFillStyle(0);
  text->SetBorderSize(0);
  if(sa){
    gdata[0] = (TGraphErrors *) finput->Get("gDataM");
    if(imc < 4) gmc[0] =  (TGraphErrors *) finput->Get("gV0M0100M");
    else gmc[0] = (TGraphErrors *) fExt->Get("V0M0100");
    gdataZ[0] = (TGraphErrors *) finput->Get("gDataZ");
    if(imc < 4) gmcZ[0] =  (TGraphErrors *) finput->Get("gV0M0100Z");
    text->AddText("V0M_standalone");
  }
  if(s1020){
    gdata[1] =  (TGraphErrors *) finput->Get("gDataSPD1020M");
    if(imc < 4) gmc[1] =  (TGraphErrors *) finput->Get("gSPD1020M");
    else gmc[1] = (TGraphErrors *) fExt->Get("SPD3");
    gdataZ[1] =  (TGraphErrors *) finput->Get("gDataSPD1020Z");
    if(imc < 4) gmcZ[1] =  (TGraphErrors *) finput->Get("gSPD1020Z");
    text->AddText("SPD_10_20");
  }
  if(s4050){
    gdata[2] =  (TGraphErrors *) finput->Get("gDataSPD4050M");
    if(imc < 4) gmc[2] =  (TGraphErrors *) finput->Get("gSPD4050M");
    else gmc[2] = (TGraphErrors *) fExt->Get("SPD1");
    gdataZ[2] =  (TGraphErrors *) finput->Get("gDataSPD4050Z");
    if(imc < 4) gmcZ[2] =  (TGraphErrors *) finput->Get("gSPD4050Z");
    text->AddText("SPD_40_50");
  }
  if(v1020){
    gdata[3] =  (TGraphErrors *) finput->Get("gDataV0M1020M");
    if(imc < 4) gmc[3] =  (TGraphErrors *) finput->Get("gV0M1020M");
    else gmc[3] = (TGraphErrors *) fExt->Get("V0M3");
    gdataZ[3] =  (TGraphErrors *) finput->Get("gDataV0M1020Z");
    if(imc < 4) gmcZ[3] =  (TGraphErrors *) finput->Get("gV0M1020Z");
    text->AddText("V0M_10_20");
  }
  if(v4050){
    gdata[4] =  (TGraphErrors *) finput->Get("gDataV0M4050M");
    if(imc < 4) gmc[4] =  (TGraphErrors *) finput->Get("gV0M4050M");
    else gmc[4] = (TGraphErrors *) fExt->Get("V0M1");
    gdataZ[4] =  (TGraphErrors *) finput->Get("gDataV0M4050Z");
    if(imc < 4) gmcZ[4] =  (TGraphErrors *) finput->Get("gV0M4050Z");
    text->AddText("V0M_40_50");
  }


  TCanvas* c1 = new TCanvas(Form("c1"),"",1800,800);
  c1->SetLeftMargin(0.2);
  c1->SetBottomMargin(0.18);
  c1->SetRightMargin(0.1);
  c1->SetTopMargin(0.1);
  c1->SetTicky();
  c1->SetTickx();
  TPad *pad1 = new TPad("pad1","pad1",0.,0.,0.54,1);
  TPad *pad2 = new TPad("pad2","pad2",0.54,0,1.,1);
  pad1->SetBorderMode(0);
  pad1->SetTopMargin(0.05);
  pad2->SetTopMargin(0.05);
  pad2->SetBottomMargin(0.15);
  pad1->SetRightMargin(0.02);
  pad2->SetRightMargin(0.05);
  pad1->SetLeftMargin(0.2);
  pad2->SetLeftMargin(0.01);
  pad1->SetBottomMargin(0.15);
  pad2->SetBorderMode(0);
  pad1->Draw();
  pad2->Draw();
  //
  pad1->cd();  
  pad1->SetFillColor(kWhite);
  pad1->SetTicky();
  pad1->SetTickx();
  TH1D* hL = new TH1D("hL","",10,0,4.);
  hL->SetStats(0);
  hL->GetXaxis()->SetTitle("<N_{ch}>/<N_{ch}_{MB}>");
  hL->GetYaxis()->SetTitle("#frac{h/#LT#it{n}_{ch}#GT_{|#it{#eta}|<0.5} }{( h/#LT#it{n}_{ch}#GT_{|#it{#eta}|<0.5} )_{INEL>0}} ");
  hL->GetXaxis()->SetTitleSize(0.06);
  hL->GetYaxis()->SetTitleSize(0.06);
  hL->GetYaxis()->SetLabelSize(0.04);
  hL->GetXaxis()->SetLabelSize(0.04);
  hL->GetYaxis()->SetTitleOffset(1.35);
  hL->GetYaxis()->SetRangeUser(0.2,1.8);
  hL->SetTitle("");
  hL->Draw();
  //
  if(gdata[0]) draw(gdata[0], gmc[0], kFullDiamond, kBlack);
  if(gdata[1])  draw(gdata[1], gmc[1], kFullCircle, kRed);
  if(gdata[2])  draw(gdata[2], gmc[2], kOpenCircle, kRed);
  if(gdata[3])  draw(gdata[3], gmc[3], kFullCircle, kBlue);
  if(gdata[4])  draw(gdata[4], gmc[4], kOpenCircle, kBlue);
    
  //
  // TLatex *xlabel = new TLatex();
  // xlabel->SetTextFont(42);
  // xlabel-> SetNDC();
  // xlabel-> SetTextColor(1);
  // xlabel-> SetTextSize(0.06);
  // xlabel-> SetTextAlign(22);
  // xlabel-> SetTextAngle(0);
  // xlabel-> DrawLatex(0.4, 0.87,Form("%s",text.Data()));
  //  text->Draw("SAME");
  
  //
  pad2->cd();  
  pad2->SetFillColor(kWhite);
  pad2->SetTicky();
  pad2->SetTickx();
  TH1D* h1L = new TH1D("h1L","",10,0,2);
  h1L->SetStats(0);
  h1L->GetXaxis()->SetTitle("<ZDC>/<ZDC>_{MB}");
  h1L->GetYaxis()->SetTitle("");
  h1L->GetXaxis()->SetTitleSize(0.06);
  h1L->GetYaxis()->SetTitleSize(0.06);
  h1L->GetYaxis()->SetLabelSize(0.04);
  h1L->GetXaxis()->SetLabelSize(0.04);
  h1L->GetYaxis()->SetTitleOffset(1.35);
  h1L->GetYaxis()->SetRangeUser(0.2,1.8);
  h1L->SetTitle("");
  h1L->GetYaxis()->SetLabelColor(kWhite);
  h1L->Draw();
  //
  if(gdataZ[0]) draw(gdataZ[0], gmcZ[0], kFullDiamond, kBlack);
  if(gdataZ[1])  draw(gdataZ[1], gmcZ[1], kFullCircle, kRed);
  if(gdataZ[2])  draw(gdataZ[2], gmcZ[2], kOpenCircle, kRed);
  if(gdataZ[3])  draw(gdataZ[3], gmcZ[3], kFullCircle, kBlue);
  if(gdataZ[4])  draw(gdataZ[4], gmcZ[4], kOpenCircle, kBlue);
  
  //
  TLegend* leg = new TLegend (0.6,0.87 - 0.05*nlab,0.9,0.87);
  leg->SetBorderSize(0);
  if(gdata[0]){
    leg->AddEntry(gdata[0] ,"data V0M SA","LEP");
    leg->AddEntry(gmc[0] ,mcname[imc],"L");
  }
  if(gdata[1]){
    leg->AddEntry(gdata[1] ,"SPD10-20","LEP");
  }
  if(gdata[2]){
    leg->AddEntry(gdata[2] ,"SPD40-50","LEP");
  }
  if(gdata[3]){
    leg->AddEntry(gdata[3] ,"V0M10-20","LEP");
  }
  if(gdata[4]){
    leg->AddEntry(gdata[4] ,"V0M40-50","LEP");
  }
  leg->SetTextSize(0.04);
  leg->SetTextFont(42);
  leg->Draw("SAME");
  
  //  c1->SaveAs(Form("comparisondatamc_%s.png",text.Data()));
  
}
