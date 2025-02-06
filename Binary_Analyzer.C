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


const Char_t * file =     "/Volumes/LaCie/Tesis/Datos Tratados/Datos2024_2bin/PAD2/19062024/TR_0_0.dat";
const Char_t * file2 =    "/Volumes/LaCie/Tesis/Datos Tratados/Datos2024_2bin/PAD2/19062024/wave_0.dat";
const Char_t * file3 =    "/Volumes/LaCie/Tesis/Datos Tratados/Datos2024_2bin/PAD2/19062024/wave_1.dat";
const Char_t * file4 =    "/Volumes/LaCie/Tesis/Datos Tratados/Datos2024_2bin/PAD2/19062024/wave_2.dat";

    
    
const Char_t * fileout =  "/Users/marcosbautista/Desktop/pruebas/TR_0_0_data.txt";
const Char_t * fileout2 = "/Users/marcosbautista/Desktop/pruebas/PMT_up_data.txt";
const Char_t * fileout3 = "/Users/marcosbautista/Desktop/pruebas/RPC.txt";
const Char_t * fileout4 = "/Users/marcosbautista/Desktop/pruebas/PMT_down_data.txt";


  std::ofstream out1 (fileout, std::ofstream::out);
  std::ofstream out2 (fileout2, std::ofstream::out);
  std::ofstream out3 (fileout3, std::ofstream::out);
  std::ofstream out4 (fileout4, std::ofstream::out);

  const UInt_t eventSz=1024;
  float  sipm1[eventSz];
  float  sipm2[eventSz];
  float  fast1[eventSz];
  float  fast2[eventSz];

  FILE *ptr;
  FILE *ptr2;
  FILE *ptr3;
  FILE *ptr4;

	float samplingrate=1; //sampling rate = 1GS/s

  // Get the size of the file
  // TODO set option for full or par of the file to be analized
  Int_t dataPointSz=sizeof sipm1[0];
  //cout <<  "Size of data point: " << sizeof sipm1[0] << endl;
  int fSize = filesize(file);
  int fSize2 = filesize(file2);
  int fSize3 = filesize(file3);
  int fSize4 = filesize(file4);

  
  //printf("File size %i Bytes\tEvent size (%i)\tTotal Events(%i)\n", fSize, eventSz*dataPointSz, fSize/eventSz);

  ptr = fopen(file,"rb");  
  ptr2 = fopen(file2,"rb");  
  ptr3 = fopen(file3,"rb");  
  ptr4 = fopen(file4,"rb");  
  // r for read, b for binary
 
    
  Double_t dt[eventSz];
  Double_t amplitude;
    Double_t ampRes =0.24414;// 1/4096 = 0.24414;// amplitude resolution = 0.2 mV per bit (LSB)  ampx20= 0.012207;

  TH2 * h2Signal = new TH2D("h2Signal", "Signal Average; time (ns);Amplitude (mV);", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
  TH2 * h2Signal2 = new TH2D("h2Signal2", "Signal Average; time (ns);Amplitude (mV);", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
  TH2 * h2Signal3 = new TH2D("h2Signal3", "Signal Average; time (ns);Amplitude (mV);", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
  TH2 * h2Signal4 = new TH2D("h2Signal4", "Signal Average; time (ns);Amplitude (mV);", 1024,0,samplingrate*1023 ,4096*2,-4096*0.24414,4095*0.24414);
  
  for (Int_t i = 0; i < eventSz; i++){
    dt[i]=i*samplingrate;
  }

  Int_t nTotalEvents = fSize/(eventSz*dataPointSz);
   if (nEvents<0) nEvents = nTotalEvents;

  for(Int_t event=0; event < nEvents; event++){
    fread(sipm1,sizeof(sipm1),1,ptr); 
    fread(sipm2,sizeof(sipm2),1,ptr2); 
    fread(fast1,sizeof(fast1),1,ptr3); 
    fread(fast2,sizeof(fast2),1,ptr4); // Put one signal (1024*UInt32) in the buffer

    for (Int_t i = 0; i < eventSz; i++){
      h2Signal -> Fill(dt[i],sipm1[i]*ampRes);
      out1 << sipm1[i]<< "\n" ;
      h2Signal2 -> Fill(dt[i],sipm2[i]*ampRes);
      out2 << sipm2[i]<< "\n" ;
      h2Signal3 -> Fill(dt[i],fast1[i]*ampRes);
      out3 << fast1[i]<< "\n" ;
      h2Signal4 -> Fill(dt[i],fast2[i]*ampRes);
      out4 << fast2[i]<< "\n" ;

  //  printf("Event number %i\r",event);
      
  }

  //printf("\n");


  cout << "\n\n";
  gStyle->SetOptTitle(kFALSE);
  gStyle->SetPalette(kSolar);

  TCanvas * can1 = new TCanvas("can1","TR_0_0",1400,800);
  h2Signal -> Draw("COLZ");

  TCanvas * can2 = new TCanvas("can2","PMT_up",1400,800);
  h2Signal2 -> Draw("COLZ");

  TCanvas * can3 = new TCanvas("can3","RPC",1400,800);
  h2Signal3 -> Draw("COLZ");

  TCanvas * can4 = new TCanvas("can4","PMT_down",1400,800);
  h2Signal4 -> Draw("COLZ");

}