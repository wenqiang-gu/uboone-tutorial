void plot_numuCC1(){
  auto file = TFile::Open("checkout_prodgenie_bnb_nu_overlay_run1_PF.root");
  auto T_eval = (TTree*)file->Get("wcpselection/T_eval");
  auto T_BDTvars = (TTree*)file->Get("wcpselection/T_BDTvars");
  auto T_KINEvars = (TTree*)file->Get("wcpselection/T_KINEvars");
  T_eval->AddFriend(T_BDTvars,"T_BDTvars");
  T_eval->AddFriend(T_KINEvars,"T_KINEvars");

  auto c1 = new TCanvas("c1","",600,600);

  T_eval->Draw("T_KINEvars.kine_reco_Enu*1e-3 >> h1(50,0.0,2.5)","weight_cv* weight_spline* (T_BDTvars.numu_cc_flag>=0 && T_BDTvars.numu_score>0.9)");
  auto h1 = (TH1F*)gROOT->FindObject("h1");
  h1->GetXaxis()->SetTitle("E^{reco}_{#nu} (GeV)");
  h1->SetTitle("");

  T_eval->Draw("T_KINEvars.kine_reco_Enu*1e-3 >> h2(50,0.0,2.5)","weight_cv* weight_spline* (T_BDTvars.numu_cc_flag>=0 && T_BDTvars.numu_score>0.9 && match_completeness_energy<=0.1*truth_energyInside)"); // incorrect charge-flash matching
  T_eval->Draw("T_KINEvars.kine_reco_Enu*1e-3 >> h3(50,0.0,2.5)","weight_cv* weight_spline* (T_BDTvars.numu_cc_flag>=0 && T_BDTvars.numu_score>0.9 && match_completeness_energy>0.1*truth_energyInside && truth_nuPdg==14 && truth_isCC && truth_vtxInside)");  // numu CC in FV
  T_eval->Draw("T_KINEvars.kine_reco_Enu*1e-3 >> h4(50,0.0,2.5)","weight_cv* weight_spline* (T_BDTvars.numu_cc_flag>=0 && T_BDTvars.numu_score>0.9 && match_completeness_energy>0.1*truth_energyInside && truth_nuPdg==14 && ! truth_isCC && truth_vtxInside)");  // numu NC in FV
  auto h2 = (TH1F*)gROOT->FindObject("h2");
  auto h3 = (TH1F*)gROOT->FindObject("h3");
  auto h4 = (TH1F*)gROOT->FindObject("h4");

  auto hother = (TH1F*)h1->Clone("hother");
  hother->Add(h2,-1);
  hother->Add(h3,-1);
  hother->Add(h4,-1);

  h1->SetLineColor(1);
  h1->SetLineWidth(2);
  h1->Draw("hist");
  THStack *hs = new THStack("hs","");
  h3->SetFillColor(kBlue); hs->Add(h3);
  h4->SetFillColor(kGreen); hs->Add(h4);
  h2->SetFillColor(kRed); hs->Add(h2);
  hother->SetFillColor(kYellow); hs->Add(hother);
  hs->Draw("same hist");

  auto lg = new TLegend(0.5,0.6,0.8,0.8);
  lg->SetBorderSize(0);
  lg->AddEntry(h2,"cosmic (MC)","f");
  lg->AddEntry(h3,"#nu_{#mu} CC in FV","f");
  lg->AddEntry(h4,"#nu_{#mu} NC in FV","f");
  lg->AddEntry(hother,"others","f");
  lg->Draw();

}
