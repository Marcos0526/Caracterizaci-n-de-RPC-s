void RPC_CHARGE_TIME_TRIGGERS_Histo2(string file)
{
  //root.exe RPC_CHARGE_TIME_TRIGGERS_Histo2.C("/Users/marcosbautista/Desktop/Datos2023_2/datos_obtenidos/acorde3_middle/position1/CT_rpc_pad2.txt")
  //root.exe RPC_CHARGE_TIME_TRIGGERS_Histo2.C'("/home/yael/shared-drives/E:/Pruebas_YAVB/RPC_11.8KV_CHARGE_TIME2.txt")'
  //root.exe RPC_CHARGE_TIME_TRIGGERS_Histo2.C'("/home/yael/shared-drives/E:/Pruebas_YAVB/RPC_Apagado.txt")'

  TCanvas *can1 = new TCanvas("c1","Cosmic Rays Test - Time Resolution",200,10,600,400);
  TCanvas *can2 = new TCanvas("c2","Cosmic Rays Test - Charge",200,10,600,400);
  TCanvas *can3 = new TCanvas("c3","Cosmic Rays Test - Charge PMTs - RPC",200,10,600,400);
  TCanvas *can4 = new TCanvas("c4","Cosmic Rays Test - Charge PMTs - RPC",200,10,600,400);

    

    
    
    
  gStyle->SetOptFit(1);
  can1->Divide(3, 1);
  can2->Divide(1, 1);
  can3->Divide(3, 1);
  can4->Divide(1, 1);
    


  //  ifstream in1;
//  ifstream in1;
 std::ifstream in1 (file);

 //cout<<setprecision(3)<<fixed;
  float t1, t2,t3,t4, two, three, two2=0, three2=0, area, areaUp, areaDown, meanUp, meanDown, meanRPC;   //t1=trigger1 t2=trigger2 t3=sipm
  Int_t LimI=-100, LimS=100,LBin=100, group;
  auto h1 = new TH1F("h1", "PMT UP - PMT DOWN", LBin, LimI, LimS);
  auto h2 = new TH1F("h2", "PMT UP - RPC", LBin, LimI, LimS);
  auto h3 = new TH1F("h3", "PMT DOWN - RPC", LBin, LimI, LimS);

  Int_t LimIa=-100, LimSa=1000,LBina=100, LimIb=-100000, LimSb=2000000,LBinb=100,LBinc=10000,pmin;
  auto h5 = new TH1F("h5", "Charge", LBinc, LimIb, LimSb);

  Int_t LimI2=-100000, LimS2=1000000;
  auto h7 = new TH2F("h7", "Charge Up vs Charge Down", LBinb, LimI2, LimS2,  LBinb, LimI2, LimS2);
  auto h8 = new TH2F("h8", "Charge Up vs Charge RPC", LBinb, LimI2, LimS2,  LBinb, LimIb, LimSb);
  auto h9 = new TH2F("h9", "Charge Down vs Charge RPC", LBinb, LimI2, LimS2,  LBinb, LimIb, LimSb);
  auto h10 = new TH3F("h10", "Charge PMTs - RPC", LBinb, LimI2, LimS2/2,  LBinb, LimI2, LimS2/2, LBinb, LimI2, LimS2/2);

    
  auto h12 = new TH1F("h12", "PMT UP - PMT DOWN", LBin, LimI, LimS);
  auto h13 = new TH1F("h13", "PMT UP - RPC", LBin, LimI, LimS);
  auto h14 = new TH1F("h14", "PMT DOWN - RPC", LBin, LimI, LimS);
  
  auto hAmplitude = new TH1F("hAmplitude", "Amplitude Distribution", 100, 0, 80000);
    
    

  while(!in1.eof()){
    in1 >> t1 >> t2 >> t3 >> area >> areaUp >> areaDown >> group >> two >> three;

  // if(areaUp > 100000 && areaUp < 500000 && areaDown > 100000 && areaDown<500000 && area > 90000 && area < 170000)
    {
      //if((t4-t3) > 200 && (t4-t3) < 900 && area > 25000 && area < 900000)
      //if(t3<t1 && t3<t2)
      {
      if(t3!=0)//&& areaUp< 7000 )//&& areaUp >3550 && areaDown < 3770 && areaDown > 3550) // t1-t2>-3 && t1-t2<3 &&
        {
        h1->Fill(t1-t2);
        h2->Fill(t1-t3);
        h3->Fill(t2-t3);
        h5->Fill((area));
        h7->Fill((areaUp), (areaDown));
        h8->Fill((areaUp), (area));
        h9->Fill((areaDown), (area));
        h10->Fill((areaUp), (areaDown), (area));
        hAmplitude->Fill(area);
        }
      //if(((t4-t3)) > 600 && ((t4-t3)) < 700) { cout << group<< endl; }
      }
    }
  }
  meanRPC = h5 -> GetMean(1);
  meanUp = h7 -> GetMean(1);
  meanDown = h7 -> GetMean(2);

  in1.clear();
  in1.seekg(0,std::ios::beg);
  h1->Reset("ICESM");
  h2->Reset("ICESM");
  h3->Reset("ICESM");
  h5->Reset("ICESM");
  h7->Reset("ICESM");
  h8->Reset("ICESM");
  h9->Reset("ICESM");
  h10->Reset("ICESM");

  while(!in1.eof()){
    in1 >> t1 >> t2 >> t3 >> area >> areaUp >> areaDown >> group >> two >> three;

      //if(areaUp > 100000 && areaUp < 500000 && areaDown > 100000 && areaDown<500000 && area > 0)
      two2++;

      //if(area > 90000 && area < 170000)
      //if((pow((meanUp-areaUp),2)+pow((meanSiPM-area),2)) < 10000000000) //&& area > 100000 && area<200000
      {
        //if((pow((meanDown-areaDown),2)+pow((meanSiPM-area),2)) < 10000000000) //&& area > 100000 && area<200000
        //if((pow((meanDown-areaDown),2)+pow((meanSiPM-area),2)) < 10000000000) //&& area > 100000 && area<200000
        {

          //if((pow((meanUp-areaUp),2)+pow((meanDown-areaDown),2)) < 5000000000) //&& area > 100000 && area<200000
          {
            //if((t4-t3) > 200 && (t4-t3) < 900 && area > 25000 && area < 900000)

            {
            if(t3!=0)//&& areaUp< 7000 )//&& areaUp >3550 && areaDown < 3770 && areaDown > 3550) // t1-t2>-3 && t1-t2<3 &&    modificar el pedestal
            {
            three2++;
            h1->Fill((t1-t2)/5);
            h2->Fill((t1-t3)/5);
            h3->Fill((t2-t3)/5);
            h5->Fill((area));
            h7->Fill((areaUp), (areaDown));
            h8->Fill((areaUp), (area));
            h9->Fill((areaDown), (area));
            h10->Fill((areaUp), (areaDown), (area));
            hAmplitude->Fill(area);
            }
          //if(((area)) > 400000 && ((area)) < 700000) { cout << group<< endl; }
          }
        }
      }
    }
  }

  can1->cd(1);
  double bin = h1->GetMaximumBin();
  //cout<<bin*(LimS-LimI)/LBin<<endl;
  TF1 *f1 = new TF1("f1","gaus", LimI,LimS);//bin*(LimS-LimI)/LBin-4, bin*(LimS-LimI)/LBin+4);
  h1->Fit("f1","R");
  h1->Draw("e1");
  h1->SetMarkerStyle(20); h1->SetMarkerColor(kBlack); //h3->SetMarkerSize(1);
  h1->GetXaxis()->SetTitle("Time ns");
  h1->GetYaxis()->SetTitle("Counts");
  h1->SetMaximum(h1->GetMaximum() + 0.1*h1->GetMaximum());

  can1->cd(2);
  double bin2 = h2->GetMaximumBin();
  TF1 *f2 = new TF1("f2","gaus", LimI,LimS);//bin2*(LimS-LimI)/LBin-4, bin2*(LimS-LimI)/LBin+4);
  h2->Fit("f2","R");
  h2->Draw("e1");
  h2->SetMarkerStyle(20); h2->SetMarkerColor(kBlack); //h3->SetMarkerSize(1);
  h2->GetXaxis()->SetTitle("Time ns");
  h2->GetYaxis()->SetTitle("Counts");
  h2->SetMaximum(h2->GetMaximum() + 0.1*h2->GetMaximum());

  can1->cd(3);
  double bin3 = h3->GetMaximumBin();
  TF1 *f3 = new TF1("f3","gaus", LimI,LimS);//bin3*(LimS-LimI)/LBin-4, bin3*(LimS-LimI)/LBin+4);
  h3->Fit("f3","R");
  h3->Draw("e1");
  h3->SetMarkerStyle(20); h3->SetMarkerColor(kBlack); //h3->SetMarkerSize(1);
  h3->GetXaxis()->SetTitle("Time ns");
  h3->GetYaxis()->SetTitle("Counts");
  h3->SetMaximum(h3->GetMaximum() + 0.1*h3->GetMaximum());

  can2->cd(1);
  TF1 *f5 = new TF1("f5","landau", LimIb,LimSb);
  h5->Fit("f5","R");
  h5->Draw("e1");
  h5->SetMarkerStyle(20); h1->SetMarkerColor(kBlack);
  h5->GetXaxis()->SetTitle("Charge");
  h5->GetYaxis()->SetTitle("Counts");
  h5->SetMaximum(h5->GetMaximum() + 0.1*h5->GetMaximum());

  can3->cd(1);
  gStyle->SetPalette(53);
  h7->Draw("colz");
  //h3->SetMarkerStyle(20); h1->SetMarkerColor(kBlack);
  h7->GetXaxis()->SetTitle("Charge PMT Up");
  h7->GetYaxis()->SetTitle("Charge PMT Down");

  can3->cd(2);
  gStyle->SetPalette(53);
  h8->Draw("colz");
  //h3->SetMarkerStyle(20); h1->SetMarkerColor(kBlack);
  h8->GetXaxis()->SetTitle("Charge PMT Up");
  h8->GetYaxis()->SetTitle("Charge RPC");

  can3->cd(3);
  gStyle->SetPalette(53);
  h9->Draw("colz");
  //h3->SetMarkerStyle(20); h1->SetMarkerColor(kBlack);
  h9->GetXaxis()->SetTitle("Charge PMT Down");
  h9->GetYaxis()->SetTitle("Charge RPC");

  can4->cd(1);
  gStyle->SetPalette(53);
  h10->Draw("box2z");
  //h3->SetMarkerStyle(20); h1->SetMarkerColor(kBlack);
  h10->GetXaxis()->SetTitle("Charge PMT Up");
  h10->GetYaxis()->SetTitle("Charge PMT Down");
  h10->GetZaxis()->SetTitle("Charge RPC");

    
    
    
    
  TCanvas *canAmplitude = new TCanvas("canAmplitude", "Amplitude vs Event Count", 1200, 1000);
  hAmplitude->Draw();
  hAmplitude->GetXaxis()->SetTitle("Amplitude");
  hAmplitude->GetYaxis()->SetTitle("Event Count");
  canAmplitude->Draw();

    
    

  double sigma1 = f1->GetParameter(2);
  double error1 = f1->GetParError(2);
  double sigma2 = f2->GetParameter(2);
  double error2 = f2->GetParError(2);
  double sigma3 = f3->GetParameter(2);
  double error3 = f3->GetParError(2);
  double mean = f1->GetParameter(1); // Parámetro 1 es la media (el centro) de la gaussiana
  double FWHM1 = 2 * sqrt(2 * log(2))* sigma1;
  double FWHM2 = 2 * sqrt(2 * log(2))* sigma2;
  double FWHM3 = 2 * sqrt(2 * log(2))* sigma3;
    
 // int a = h1->FindFirstBinAbove(h1->GetMaximum()/2);
//  double b = h1->FindLastBinAbove(h1->GetMaximum()/2);
 // double fwhm = h1->GetBinCenter(b) - h1->GetBinCenter(a);
    
  float TR = sqrt((pow(sigma2,2)+ pow(sigma3,2)- pow(sigma1,2))/2);
  float ERR = sqrt((pow(error2,2)+ pow(error3,2)- pow(error1,2))/2);
  float EFF = (float)three2/(float)two2*100;
  cout<<"TR="<<TR<<" +/- "<<ERR<<endl;
  cout<<"EFF="<<EFF<<endl;
  cout<<"MeanUp= "<<meanUp<<" MeanDown= "<<meanDown<<" MeanRPC= "<<meanRPC<<endl;
    
// Imprimir el FWHM
  cout << "FWHM1: " << FWHM1 << " ns" << endl;
  cout << "FWHM2: " << FWHM2 << " ns" << endl;
  cout << "FWHM3: " << FWHM3 << " ns" << endl;
}





// voltaje vs resolicion temporal
// eficienmcias vs voltajes
//amplitud vs voltajes 
// dejar ceros y mejorar el binning
// Cuenta de github
