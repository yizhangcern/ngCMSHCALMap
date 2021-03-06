#include "HFAnalyzer.h"

void HFAnalyzer::HFNChannelBasicCheck()
{
  std::cout << "How many Channels do we have in HF ? " << NchHF_all << std::endl;
  std::cout << "Re-calculate from Front End: " << 2 * NrbxHF * NrmHF * Nrm_fiber * Nfiber_ch << std::endl;
  std::cout << "Re-calculate from Back End(VME): " << Ncrate * Nhtr * Nfpga * Nhtr_fiber * Nfiber_ch << std::endl;
  std::cout << "Re-calculate from Back End(uTCA): " << Ncrate * Nuhtr * Nufpga * Nuhtr_fiber * Nfiber_ch << std::endl;
  std::cout << "Re-calculate from Geometry: " << NHFside * (NHFetadphi2 * NHFphidphi2 + NHFetadphi4 * NHFphidphi4) * NHFdepth << std::endl;
  return ;
}

void HFAnalyzer::PlottingHFFEtoGeo(
                                   std::vector<HFFrontEnd> myHFFrontEnd,
                                   std::vector<HFGeometry> myHFGeometry
                                  )
{
  TCanvas *c = new TCanvas("c", "",0,51,4500,2000);
  c->Divide(3,2); c->SetFillColor(0); c->cd();

  TH2D *hfprbxphi = new TH2D("hfprbxphi", "Phi in HFP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfprbxeta = new TH2D("hfprbxeta", "Eta in HFP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfprbxdep = new TH2D("hfprbxdep", "Dep in HFP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);

  TH2D *hfmrbxphi = new TH2D("hfmrbxphi", "Phi in HFM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfmrbxeta = new TH2D("hfmrbxeta", "Eta in HFM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfmrbxdep = new TH2D("hfmrbxdep", "Dep in HFM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);

  for(auto i=0; i<NchHF_all; i++)
  {
    std::string thisrbx = (myHFFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zphi = (myHFGeometry.at(i)).phi;
    double zeta = (myHFGeometry.at(i)).side * (myHFGeometry.at(i)).eta;
    double zdepth = (myHFGeometry.at(i)).depth;

    double x = ((myHFFrontEnd.at(i)).rm_fiber-1)*3 + (myHFFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,....12 for HF,0, 2,4,6,8,10,12 for other HF,12

    double rmid = (myHFFrontEnd.at(i)).rm;
    double y = (rbxid-1)*3 + rmid;

    if( thisrbx.find("HFP") != std::string::npos ){ hfprbxphi->Fill(x,y,zphi); hfprbxeta->Fill(x,y,zeta); hfprbxdep->Fill(x,y,zdepth); }
    else if( thisrbx.find("HFM") != std::string::npos ){ hfmrbxphi->Fill(x,y,zphi); hfmrbxeta->Fill(x,y,zeta); hfmrbxdep->Fill(x,y,zdepth); }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    hfprbxphi->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); hfprbxeta->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); hfprbxdep->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]);
    hfmrbxphi->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); hfmrbxeta->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); hfmrbxdep->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxHF*NrmHF;i++) 
  { 
    hfprbxphi->GetYaxis()->SetBinLabel(i,HFPRBXlabel[i-1]); hfprbxeta->GetYaxis()->SetBinLabel(i,HFPRBXlabel[i-1]); hfprbxdep->GetYaxis()->SetBinLabel(i,HFPRBXlabel[i-1]);
    hfmrbxphi->GetYaxis()->SetBinLabel(i,HFMRBXlabel[i-1]); hfmrbxeta->GetYaxis()->SetBinLabel(i,HFMRBXlabel[i-1]); hfmrbxdep->GetYaxis()->SetBinLabel(i,HFMRBXlabel[i-1]);
  }

  hfprbxphi->SetStats(0); hfprbxeta->SetStats(0); hfprbxdep->SetStats(0);
  hfmrbxphi->SetStats(0); hfmrbxeta->SetStats(0); hfmrbxdep->SetStats(0);

  c->cd(1); hfprbxphi->Draw("colztext"); c->cd(2); hfprbxeta->Draw("colztext"); c->cd(3); hfprbxdep->Draw("colztext");
  c->cd(4); hfmrbxphi->Draw("colztext"); c->cd(5); hfmrbxeta->Draw("colztext"); c->cd(6); hfmrbxdep->Draw("colztext");

  //title->Draw("same");

  c->SaveAs( (dir+"_HFFEetaphidepth.png").c_str() );
  c->SaveAs( (dir+"_HFFEetaphidepth.pdf").c_str() );
  c->SaveAs( (dir+"_HFFEetaphidepth.C").c_str() );
  c->Close();

  return ;
}

void HFAnalyzer::PlottingHFFEtoBEVME(
                                     std::vector<HFFrontEnd> myHFFrontEnd,
                                     std::vector<HFBackEnd> myHFBackEnd
                                    )
{
  TCanvas *c = new TCanvas("c", "",0,51,6000,2000);
  c->Divide(4,2); c->SetFillColor(0); c->cd();

  TH2D *hfprbxcrate = new TH2D("hfprbxcrate", "Crate in HFP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfprbxhtr = new TH2D("hfprbxhtr", "HTR in HFP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfprbxfpga = new TH2D("hfprbxfpga", "FPGA in HFP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfprbxhtr_fiber = new TH2D("hfprbxhtr_fiber", "HTRfiber in HFP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfmrbxcrate = new TH2D("hfmrbxcrate", "Crate in HFM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfmrbxhtr = new TH2D("hfmrbxhtr", "HTR in HFM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfmrbxfpga = new TH2D("hfmrbxfpga", "FPGA in HFM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfmrbxhtr_fiber = new TH2D("hfmrbxhtr_fiber", "HTRfiber in HFM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);

  for(auto i=0; i<NchHF_all; i++)
  {
    std::string thisrbx = (myHFFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zcrate = (myHFBackEnd.at(i)).crate;
    double zhtr = (myHFBackEnd.at(i)).htr;
    double zfpga = 2000;
    ((myHFBackEnd.at(i)).fpga)=="top" ? zfpga = 1 : zfpga = -1;
    double zhtr_fiber = (myHFBackEnd.at(i)).htr_fiber;

    double x = ((myHFFrontEnd.at(i)).rm_fiber-1)*3 + (myHFFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,....12 for HF
    double rmid = (myHFFrontEnd.at(i)).rm;
    double y = (rbxid-1)*3 + rmid;
    
    if( thisrbx.find("HFP") != std::string::npos ){ hfprbxcrate->Fill(x,y,zcrate); hfprbxhtr->Fill(x,y,zhtr); hfprbxfpga->Fill(x,y,zfpga); hfprbxhtr_fiber->Fill(x,y,zhtr_fiber); }
    else if( thisrbx.find("HFM") != std::string::npos ){ hfmrbxcrate->Fill(x,y,zcrate); hfmrbxhtr->Fill(x,y,zhtr); hfmrbxfpga->Fill(x,y,zfpga); hfmrbxhtr_fiber->Fill(x,y,zhtr_fiber); }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    hfprbxcrate->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); hfprbxhtr->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); 
    hfprbxfpga->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); hfprbxhtr_fiber->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]);

    hfmrbxcrate->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); hfmrbxhtr->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]);
    hfmrbxfpga->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); hfmrbxhtr_fiber->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxHF*NrmHF;i++) 
  { 
    hfprbxcrate->GetYaxis()->SetBinLabel(i,HFPRBXlabel[i-1]); hfprbxhtr->GetYaxis()->SetBinLabel(i,HFPRBXlabel[i-1]); 
    hfprbxfpga->GetYaxis()->SetBinLabel(i,HFPRBXlabel[i-1]); hfprbxhtr_fiber->GetYaxis()->SetBinLabel(i,HFPRBXlabel[i-1]);
    
    hfmrbxcrate->GetYaxis()->SetBinLabel(i,HFMRBXlabel[i-1]); hfmrbxhtr->GetYaxis()->SetBinLabel(i,HFMRBXlabel[i-1]);
    hfmrbxfpga->GetYaxis()->SetBinLabel(i,HFMRBXlabel[i-1]); hfmrbxhtr_fiber->GetYaxis()->SetBinLabel(i,HFMRBXlabel[i-1]);
  }

  hfprbxcrate->SetStats(0); hfprbxhtr->SetStats(0); hfprbxfpga->SetStats(0); hfprbxhtr_fiber->SetStats(0);
  hfmrbxcrate->SetStats(0); hfmrbxhtr->SetStats(0); hfmrbxfpga->SetStats(0); hfmrbxhtr_fiber->SetStats(0);

  c->cd(1); hfprbxcrate->Draw("colztext"); c->cd(2); hfprbxhtr->Draw("colztext"); c->cd(3); hfprbxfpga->Draw("colztext"); c->cd(4); hfprbxhtr_fiber->Draw("colztext");
  c->cd(5); hfmrbxcrate->Draw("colztext"); c->cd(6); hfmrbxhtr->Draw("colztext"); c->cd(7); hfmrbxfpga->Draw("colztext"); c->cd(8); hfmrbxhtr_fiber->Draw("colztext");

  c->SaveAs( (dir+"_HFFEcratehtrfpgahtr_fiber.png").c_str() );
  c->SaveAs( (dir+"_HFFEcratehtrfpgahtr_fiber.pdf").c_str() );
  c->SaveAs( (dir+"_HFFEcratehtrfpgahtr_fiber.C").c_str() );
  c->Close();

  return ;
}

void HFAnalyzer::PlottingHFFEtoBEuTCA(
                                      std::vector<HFFrontEnd> myHFFrontEnd,
                                      std::vector<HFBackEnd> myHFBackEnd
                                     )
{
  TCanvas *c = new TCanvas("c", "",0,51,6000,2000);
  c->Divide(4,2); c->SetFillColor(0); c->cd();

  TH2D *hfprbxucrate = new TH2D("hfprbxucrate", "uCrate in HFP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfprbxuhtr = new TH2D("hfprbxuhtr", "uHTR in HFP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfprbxufpga = new TH2D("hfprbxufpga", "uFPGA in HFP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfprbxuhtr_fiber = new TH2D("hfprbxuhtr_fiber", "uHTRfiber in HFP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfmrbxucrate = new TH2D("hfmrbxucrate", "uCrate in HFM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfmrbxuhtr = new TH2D("hfmrbxuhtr", "uHTR in HFM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfmrbxufpga = new TH2D("hfmrbxufpga", "uFPGA in HFM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);
  TH2D *hfmrbxuhtr_fiber = new TH2D("hfmrbxuhtr_fiber", "uHTRfiber in HFM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHF*NrmHF, 1, NrbxHF*NrmHF+1);

  for(auto i=0; i<NchHF_all; i++)
  {
    std::string thisrbx = (myHFFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zucrate = (myHFBackEnd.at(i)).ucrate;
    double zuhtr = (myHFBackEnd.at(i)).uhtr;
    double zufpga = 2000;
    ((myHFBackEnd.at(i)).ufpga)=="uHTR" ? zufpga = 10 : zufpga = -10;
    double zuhtr_fiber = (myHFBackEnd.at(i)).uhtr_fiber;

    double x = ((myHFFrontEnd.at(i)).rm_fiber-1)*3 + (myHFFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,....12 for HF,0, 2,4,6,8,10,12 for other HF,12
    double rmid = (myHFFrontEnd.at(i)).rm;
    double y = (rbxid-1)*3 + rmid;
    
    if( thisrbx.find("HFP") != std::string::npos ){ hfprbxucrate->Fill(x,y,zucrate); hfprbxuhtr->Fill(x,y,zuhtr); hfprbxufpga->Fill(x,y,zufpga); hfprbxuhtr_fiber->Fill(x,y,zuhtr_fiber); }
    else if( thisrbx.find("HFM") != std::string::npos ){ hfmrbxucrate->Fill(x,y,zucrate); hfmrbxuhtr->Fill(x,y,zuhtr); hfmrbxufpga->Fill(x,y,zufpga); hfmrbxuhtr_fiber->Fill(x,y,zuhtr_fiber); }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    hfprbxucrate->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); hfprbxuhtr->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); 
    hfprbxufpga->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); hfprbxuhtr_fiber->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]);

    hfmrbxucrate->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); hfmrbxuhtr->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]);
    hfmrbxufpga->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]); hfmrbxuhtr_fiber->GetXaxis()->SetBinLabel(i,HFRMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxHF*NrmHF;i++) 
  { 
    hfprbxucrate->GetYaxis()->SetBinLabel(i,HFPRBXlabel[i-1]); hfprbxuhtr->GetYaxis()->SetBinLabel(i,HFPRBXlabel[i-1]); 
    hfprbxufpga->GetYaxis()->SetBinLabel(i,HFPRBXlabel[i-1]); hfprbxuhtr_fiber->GetYaxis()->SetBinLabel(i,HFPRBXlabel[i-1]);
    
    hfmrbxucrate->GetYaxis()->SetBinLabel(i,HFMRBXlabel[i-1]); hfmrbxuhtr->GetYaxis()->SetBinLabel(i,HFMRBXlabel[i-1]);
    hfmrbxufpga->GetYaxis()->SetBinLabel(i,HFMRBXlabel[i-1]); hfmrbxuhtr_fiber->GetYaxis()->SetBinLabel(i,HFMRBXlabel[i-1]);
  }

  hfprbxucrate->SetStats(0); hfprbxuhtr->SetStats(0); hfprbxufpga->SetStats(0); hfprbxuhtr_fiber->SetStats(0);
  hfmrbxucrate->SetStats(0); hfmrbxuhtr->SetStats(0); hfmrbxufpga->SetStats(0); hfmrbxuhtr_fiber->SetStats(0);

  c->cd(1); hfprbxucrate->Draw("colztext"); c->cd(2); hfprbxuhtr->Draw("colztext"); c->cd(3); hfprbxufpga->Draw("colztext"); c->cd(4); hfprbxuhtr_fiber->Draw("colztext");
  c->cd(5); hfmrbxucrate->Draw("colztext"); c->cd(6); hfmrbxuhtr->Draw("colztext"); c->cd(7); hfmrbxufpga->Draw("colztext"); c->cd(8); hfmrbxuhtr_fiber->Draw("colztext");

  c->SaveAs( (dir+"_HFFEucrateuhtrufpgauhtr_fiber.png").c_str() );
  c->SaveAs( (dir+"_HFFEucrateuhtrufpgauhtr_fiber.pdf").c_str() );
  c->SaveAs( (dir+"_HFFEucrateuhtrufpgauhtr_fiber.C").c_str() );
  c->Close();

  return ;
}

