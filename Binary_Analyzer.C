// The program extract the signal form binary file and average them
#include <fstream>
#include <string>
#include <iostream>

#include "TCanvas.h"
#include "TGraph.h"
#include "TMath.h"
#include "TAxis.h"
#include "TH2.h"

std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

void Binary_Analyzer(){
  Int_t nEvents = -1;

// Horizontal Scan 6 GeV
const Char_t * file =     "/Users/marcosbautista/Desktop/Datos2023_2/2023/ACORDE_2_CERN_NUEVATOMA/POSITION1/wave_2.dat";
const Char_t * file2 =    "/Users/marcosbautista/Desktop/Datos2023_2/2023/ACORDE_2_CERN_NUEVATOMA/POSITION1/wave_3.dat";
const Char_t * file3 =    "/Users/marcosbautista/Desktop/Datos2023_2/2023/ACORDE_2_CERN_NUEVATOMA/POSITION1/TR_0_0.dat";
const Char_t * file4 =    "/Users/marcosbautista/Desktop/Datos2023_2/2023/ACORDE_2_CERN_NUEVATOMA/POSITION1/wave_0.dat";
const Char_t * file5 =    "/Users/marcosbautista/Desktop/Datos2023_2/2023/ACORDE_2_CERN_NUEVATOMA/POSITION1/wave_1.dat";
const Char_t * file6 =    "/Users/marcosbautista/Desktop/Datos2023_2/2023/ACORDE_2_CERN_NUEVATOMA/POSITION1/wave_5.dat";
    
    
const Char_t * fileout =  "/Users/marcosbautista/Desktop/Datos2023_2/acorde2_cern/position1/PMT_up_data.txt";
const Char_t * fileout2 = "/Users/marcosbautista/Desktop/Datos2023_2/acorde2_cern/position1/PMT_down_data.txt";
const Char_t * fileout3 = "/Users/marcosbautista/Desktop/Datos2023_2/acorde2_cern/position1/TR_0_0_data.txt";
const Char_t * fileout4 = "/Users/marcosbautista/Desktop/Datos2023_2/acorde2_cern/position1/SIPM1.txt";
const Char_t * fileout5 = "/Users/marcosbautista/Desktop/Datos2023_2/acorde2_cern/position1/SIPM2.txt";
const Char_t * fileout6 = "/Users/marcosbautista/Desktop/Datos2023_2/acorde2_cern/position1/RPC.txt";

  std::ofstream out1 (fileout, std::ofstream::out);
  std::ofstream out2 (fileout2, std::ofstream::out);
  std::ofstream out3 (fileout3, std::ofstream::out);
  std::ofstream out4 (fileout4, std::ofstream::out);
  std::ofstream out5 (fileout5, std::ofstream::out);
  std::ofstream out6 (fileout6, std::ofstream::out);
  const UInt_t eventSz=1024;
  float  sipm1[eventSz];
  float  sipm2[eventSz];
  float  fast1[eventSz];
  float  fast2[eventSz];
  float  trigger1[eventSz];
  float  trigger2[eventSz];
  FILE *ptr;
  FILE *ptr2;
  FILE *ptr3;
  FILE *ptr4;
  FILE *ptr5;
  FILE *ptr6;

	float samplingrate=1; //sampling rate = 1GS/s

  // Get the size of the file
  // TODO set option for full or par of the file to be analized
  Int_t dataPointSz=sizeof sipm1[0];
  //cout <<  "Size of data point: " << sizeof sipm1[0] << endl;
  int fSize = filesize(file);
  int fSize2 = filesize(file2);
  int fSize3 = filesize(file3);
  int fSize4 = filesize(file4);
  int fSize5 = filesize(file5);
  int fSize6 = filesize(file6);
  
  //printf("File size %i Bytes\tEvent size (%i)\tTotal Events(%i)\n", fSize, eventSz*dataPointSz, fSize/eventSz);

  ptr = fopen(file,"rb");  // r for read, b for binary
  ptr2 = fopen(file2,"rb");  // r for read, b for binary
  ptr3 = fopen(file3,"rb");  // r for read, b for binary
  ptr4 = fopen(file4,"rb");  // r for read, b for binary
  ptr5 = fopen(file5,"rb");  // r for read, b for binary
  ptr6 = fopen(file6,"rb");  // r for read, b for binary
 
    
  Double_t dt[eventSz];
  Double_t amplitude;
    Double_t ampRes =0.24414;// 1/4096;// amplitude resolution = 0.2 mV per bit (LSB) ;

  TH2 * h2Signal = new TH2D("h2Signal", "Signal Average; time (ns);Amplitude (mV);", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
  TH2 * h2Signal2 = new TH2D("h2Signal2", "Signal Average; time (ns);Amplitude (mV);", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
  TH2 * h2Signal3 = new TH2D("h2Signal3", "Signal Average; time (ns);Amplitude (mV);", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
  TH2 * h2Signal4 = new TH2D("h2Signal4", "Signal Average; time (ns);Amplitude (mV);", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
  TH2 * h2Signal5 = new TH2D("h2Signal5", "Signal Average; time (ns);Amplitude (mV);", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
  TH2 * h2Signal6 = new TH2D("h2Signal6", "Signal Average; time (ns);Amplitude (mV);", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);

  for (Int_t i = 0; i < eventSz; i++){
    dt[i]=i*samplingrate;
  }

  Int_t nTotalEvents = fSize/(eventSz*dataPointSz);
   if (nEvents<0) nEvents = nTotalEvents;

  for(Int_t event=0; event < nEvents; event++){
    fread(sipm1,sizeof(sipm1),1,ptr); // Put one signal (1024*UInt32) in the buffer
    fread(sipm2,sizeof(sipm2),1,ptr2); // Put one signal (1024*UInt32) in the buffer
    fread(fast1,sizeof(fast1),1,ptr3); // Put one signal (1024*UInt32) in the buffer
    fread(fast2,sizeof(fast2),1,ptr4); // Put one signal (1024*UInt32) in the buffer
    fread(trigger1,sizeof(trigger1),1,ptr5); // Put one signal (1024*UInt32) in the buffer
    fread(trigger2,sizeof(trigger2),1,ptr6); // Put one signal (1024*UInt32) in the buffer

    for (Int_t i = 0; i < eventSz; i++){
      h2Signal -> Fill(dt[i],sipm1[i]*ampRes);
      out1 << sipm1[i]<< "\n" ;
      h2Signal2 -> Fill(dt[i],sipm2[i]*ampRes);
      out2 << sipm2[i]<< "\n" ;
      h2Signal3 -> Fill(dt[i],fast1[i]*ampRes);
      out3 << fast1[i]<< "\n" ;
      h2Signal4 -> Fill(dt[i],fast2[i]*ampRes);
      out4 << fast2[i]<< "\n" ;
      h2Signal5 -> Fill(dt[i],trigger1[i]*ampRes);
      out5 << trigger1[i]<< "\n" ;
      h2Signal6 -> Fill(dt[i],trigger2[i]*ampRes);
      out6 << trigger2[i]<< "\n" ;    //sipm, fast y trigger se tomaran por igual (solo cambia el nombre)
       // cout << sipm1[i] << " " << sipm2[i] << " " <<fast1[i] << " " << fast2[i] << " " << trigger1[i] << " " << trigger2[i] << endl; //habilitar para ver el proceso
     }

  //  printf("Event number %i\r",event);
      
  }

  //printf("\n");


  cout << "\n\n";
  gStyle->SetOptTitle(kFALSE);
  gStyle->SetPalette(kSolar);

  TCanvas * can1 = new TCanvas("can1","PMT_up",1400,800);
  h2Signal -> Draw("COLZ");

  TCanvas * can2 = new TCanvas("can2","PMT_down",1400,800);
  h2Signal2 -> Draw("COLZ");

  TCanvas * can3 = new TCanvas("can3","TR_0_0",1400,800);
  h2Signal3 -> Draw("COLZ");

  TCanvas * can4 = new TCanvas("can4","RPC_1",1400,800);
  h2Signal4 -> Draw("COLZ");

  TCanvas * can5 = new TCanvas("can5","RPC_2",1400,800);
  h2Signal5 -> Draw("COLZ");

  TCanvas * can6 = new TCanvas("can6","RPC_3",1400,800);
  h2Signal6 -> Draw("COLZ");

  
}
    




