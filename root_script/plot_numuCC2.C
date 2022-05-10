void plot_numuCC2(){
  auto file = TFile::Open("checkout_prodgenie_bnb_nu_overlay_run1_PF.root");
  auto T_eval = (TTree*)file->Get("wcpselection/T_eval");
  auto T_PFeval = (TTree*)file->Get("wcpselection/T_PFeval");
  auto T_BDTvars = (TTree*)file->Get("wcpselection/T_BDTvars");
  auto T_KINEvars = (TTree*)file->Get("wcpselection/T_KINEvars");
  T_eval->AddFriend(T_PFeval,"T_PFeval");
  T_eval->AddFriend(T_BDTvars,"T_BDTvars");
  T_eval->AddFriend(T_KINEvars,"T_KINEvars");

  auto c1 = new TCanvas("c1","",600,600);

  T_eval->Draw("T_KINEvars.kine_reco_Enu*1e-3 >> h1(50,0.0,2.5)","weight_cv * weight_spline * (T_BDTvars.numu_cc_flag>=0 && T_BDTvars.numu_score>0.9)");
  auto h1 = (TH1F*)gROOT->FindObject("h1");
  h1->GetXaxis()->SetTitle("E^{reco}_{#nu} (GeV)");
  h1->SetTitle("");

  T_eval->Draw("T_KINEvars.kine_reco_Enu*1e-3 >>  h2(50,0.0,2.5)","weight_cv * weight_spline * (T_BDTvars.numu_cc_flag>=0 && T_BDTvars.numu_score>0.9 && match_completeness_energy<=0.1*truth_energyInside)"); // cosmic from incorrect flash matching 

  T_eval->Draw("T_KINEvars.kine_reco_Enu*1e-3 >>  h3(50,0.0,2.5)","weight_cv * weight_spline * (T_BDTvars.numu_cc_flag>=0 && T_BDTvars.numu_score>0.9 && match_completeness_energy>0.1*truth_energyInside && T_PFeval.truth_nuScatType==1 && truth_isCC) "); // CC QE
  T_eval->Draw("T_KINEvars.kine_reco_Enu*1e-3 >>  h4(50,0.0,2.5)","weight_cv * weight_spline * (T_BDTvars.numu_cc_flag>=0 && T_BDTvars.numu_score>0.9 && match_completeness_energy>0.1*truth_energyInside && T_PFeval.truth_nuScatType==1 && !truth_isCC) "); // NC QE
  T_eval->Draw("T_KINEvars.kine_reco_Enu*1e-3 >>  h5(50,0.0,2.5)","weight_cv * weight_spline * (T_BDTvars.numu_cc_flag>=0 && T_BDTvars.numu_score>0.9 && match_completeness_energy>0.1*truth_energyInside && T_PFeval.truth_nuScatType==4 && truth_isCC) "); // CC RES
  T_eval->Draw("T_KINEvars.kine_reco_Enu*1e-3 >>  h6(50,0.0,2.5)","weight_cv * weight_spline * (T_BDTvars.numu_cc_flag>=0 && T_BDTvars.numu_score>0.9 && match_completeness_energy>0.1*truth_energyInside && T_PFeval.truth_nuScatType==4 && !truth_isCC) "); // NC RES
  T_eval->Draw("T_KINEvars.kine_reco_Enu*1e-3 >>  h7(50,0.0,2.5)","weight_cv * weight_spline * (T_BDTvars.numu_cc_flag>=0 && T_BDTvars.numu_score>0.9 && match_completeness_energy>0.1*truth_energyInside && T_PFeval.truth_nuScatType==3 && truth_isCC) "); // CC DIS
  T_eval->Draw("T_KINEvars.kine_reco_Enu*1e-3 >>  h8(50,0.0,2.5)","weight_cv * weight_spline * (T_BDTvars.numu_cc_flag>=0 && T_BDTvars.numu_score>0.9 && match_completeness_energy>0.1*truth_energyInside && T_PFeval.truth_nuScatType==3 && !truth_isCC) "); // NC DIS
  T_eval->Draw("T_KINEvars.kine_reco_Enu*1e-3 >>  h9(50,0.0,2.5)","weight_cv * weight_spline * (T_BDTvars.numu_cc_flag>=0 && T_BDTvars.numu_score>0.9 && match_completeness_energy>0.1*truth_energyInside && T_PFeval.truth_nuScatType==10 && truth_isCC) "); // CC MEC
  T_eval->Draw("T_KINEvars.kine_reco_Enu*1e-3 >> h10(50,0.0,2.5)","weight_cv * weight_spline * (T_BDTvars.numu_cc_flag>=0 && T_BDTvars.numu_score>0.9 && match_completeness_energy>0.1*truth_energyInside && T_PFeval.truth_nuScatType==10 && !truth_isCC) "); // CC MEC

  auto h2 = (TH1F*)gROOT->FindObject("h2");
  auto h3 = (TH1F*)gROOT->FindObject("h3");
  auto h4 = (TH1F*)gROOT->FindObject("h4");
  auto h5 = (TH1F*)gROOT->FindObject("h5");
  auto h6 = (TH1F*)gROOT->FindObject("h6");
  auto h7 = (TH1F*)gROOT->FindObject("h7");
  auto h8 = (TH1F*)gROOT->FindObject("h8");
  auto h9 = (TH1F*)gROOT->FindObject("h9");
  auto h10 = (TH1F*)gROOT->FindObject("h10");

  auto hother = (TH1F*)h1->Clone("hother");
  hother->Add(h2,-1);
  hother->Add(h3,-1);
  hother->Add(h4,-1);
  hother->Add(h5,-1);
  hother->Add(h6,-1);
  hother->Add(h7,-1);
  hother->Add(h8,-1);
  hother->Add(h9,-1);
  hother->Add(h10,-1);

  h1->SetLineColor(1);
  h1->SetLineWidth(2);
  h1->Draw("hist");
  THStack *hs = new THStack("hs","");
  h2->SetFillColor(2); hs->Add(h2);
  h4->SetFillColor(4); hs->Add(h4);
  h6->SetFillColor(6); hs->Add(h6);
  h7->SetFillColor(7); hs->Add(h7);
  h8->SetFillColor(8); hs->Add(h8);
  h10->SetFillColor(10); hs->Add(h10);
  h9->SetFillColor(9); hs->Add(h9);
  h5->SetFillColor(5); hs->Add(h5);
  h3->SetFillColor(3); hs->Add(h3);
  hother->SetFillColor(11); hs->Add(hother);

  hs->Draw("same hist");

  auto lg = new TLegend(0.5,0.6,0.8,0.8);
  lg->SetBorderSize(0);
  lg->AddEntry(h2,"cosmic (MC)","f");
  lg->AddEntry(h3,"CC QE","f");
  lg->AddEntry(h4,"NC QE","f");
  lg->AddEntry(h5,"CC RES","f");
  lg->AddEntry(h6,"NC RES","f");
  lg->AddEntry(h7,"CC DIS","f");
  lg->AddEntry(h8,"NC DIS","f");
  lg->AddEntry(h9,"CC MEC","f");
  lg->AddEntry(h10,"NC MEC","f");
  lg->AddEntry(hother,"others","f");
  lg->Draw();

}
