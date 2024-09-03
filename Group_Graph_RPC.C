//This code reads a file with the lines of four signals, belonging to the same selected group.
//All of them are plotted and shown in a canvas in order to be analized.

void Group_Graph_RPC(string file)
{

  //root.exe Group_Graph_RPC.C("/Users/marcosbautista/Desktop/Datos2023_2/datos_obtenidos/acorde3_middle/pedestal/GE_RPC_pad2.txt")

  TCanvas *can1 = new TCanvas("c1","Canvas",200,10,600,400);
  auto gr1 = new TGraph(1024); gr1->SetMarkerColor(kRed); gr1 -> SetLineColor(kRed); gr1->SetMarkerStyle(20); gr1->SetMarkerSize(0.8);
  auto gr2 = new TGraph(1024); gr2->SetMarkerColor(kBlue); gr2 -> SetLineColor(kBlue); gr2->SetMarkerStyle(21); gr2->SetMarkerSize(0.8);
  auto gr3 = new TGraph(1024); gr3->SetMarkerColor(kBlack); gr3 -> SetLineColor(kBlack); gr3->SetMarkerStyle(22); gr3->SetMarkerSize(0.8);
  auto gr4 = new TGraph(1024); gr4->SetMarkerColor(6); gr4 -> SetLineColor(6); gr4->SetMarkerStyle(23); gr4->SetMarkerSize(0.8);
  //auto gr5 = new TGraph(1024); gr5->SetMarkerColor(8); gr5 -> SetLineColor(8); gr5->SetMarkerStyle(24); gr5->SetMarkerSize(0.8);


  ifstream in1;
  TMultiGraph *mg = new TMultiGraph();

  in1.open(file);
  float volt, volt2, volt3, volt4, rpc[10000], tr1[10000],tr2[10000], tr0[10000],time[10000], fast[10000];

  Int_t lines=0,c=1, pmin;

  for(lines=0; lines <= 1024; lines++)
  {
    in1 >> volt >> volt2 >> volt3 >> volt4;
    //in1 >> volt >> volt2 >> volt3;
    rpc[lines]=(float)volt; tr1[lines]=(float)volt2; tr2[lines]=(float)volt3; tr0[lines]=(float)volt4;
    //sipm[lines]=(float)volt;/4096 tr1[lines]=(float)volt2/4096; tr2[lines]=(float)volt3/4096; tr0[lines]=(float)volt4/4096;
    time[lines]=(float)lines; //GHz
    gr1->SetPoint(lines,time[lines],tr1[lines]);
    gr2->SetPoint(lines,time[lines],tr2[lines]);
    gr3->SetPoint(lines,time[lines],rpc[lines]);
    gr4->SetPoint(lines,time[lines],tr0[lines]);
  //  gr5->SetPoint(lines,time[lines],tr0[lines]);

  }

  mg->Add(gr1);
  mg->Add(gr2);
  mg->Add(gr3);
  mg->Add(gr4);
  //mg->Add(gr5);
  mg->Draw("ALP+");

  //mg->SetMaximum(1);
  mg->SetMaximum(4096);
  mg->SetMinimum(0);

  auto legend = new TLegend(0.6,0.3,0.9,0.1);
  legend->SetHeader("Cosmic Rays Test","C"); // option "C" allows to center the header

  legend->AddEntry(gr1,"PMT Down","l");
  legend->AddEntry(gr2,"PMT Up","l");
  legend->AddEntry(gr3,"RPC","l");
  legend->AddEntry(gr4,"Trigger","l");
  //legend->AddEntry(gr5,"Trigger","l");
  legend->Draw();
}
