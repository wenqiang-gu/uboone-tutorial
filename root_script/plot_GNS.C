void plot_GNS(){
  auto file = TFile::Open("checkout_prodgenie_bnb_nu_overlay_run1_PF.root");
  auto T_eval = (TTree*)file->Get("wcpselection/T_eval");
  auto T_BDTvars = (TTree*)file->Get("wcpselection/T_BDTvars");
  T_eval->AddFriend(T_BDTvars,"T_BDTvars");

  auto c1 = new TCanvas("c1","",600,600);

  T_eval->Draw("truth_nuEnergy*1e-3 >> h1(100,0.2,3.2)","truth_isCC && truth_vtxInside ");
  T_eval->Draw("truth_nuEnergy*1e-3 >> h2(100,0.2,3.2)","truth_isCC && truth_vtxInside && T_BDTvars.numu_cc_flag>=0"); // generic neutrino selection
  auto h1 = (TH1F*)gROOT->FindObject("h1");
  auto h2 = (TH1F*)gROOT->FindObject("h2");
  h2->GetXaxis()->SetTitle("E^{true}_{#nu} (GeV)");
  h2->GetYaxis()->SetTitle("Efficiency");
  h2->SetLineColor(4);

  // h1->Draw();
  // h2->Draw("same");
  cout << "overall efficiency: " << h2->Integral()/h1->Integral() << endl;

  h2->Divide(h1);
  h2->Draw();

}
