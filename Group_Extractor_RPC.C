void Group_Extractor_RPC(string file, string file2, string file3, string file4, string fileout, Int_t group) //string  file2,
{

  //cd Documents/NewCodes
  //root.exe Group_Extractor_RPC.C("/Volumes/LaCie/Tesis/Datos Tratados/Datos2024_2tratados/19062024/RPC.txt", "/Volumes/LaCie/Tesis/Datos Tratados/Datos2024_2tratados/19062024/PMT_up_data.txt","/Volumes/LaCie/Tesis/Datos Tratados/Datos2024_2tratados/19062024/PMT_down_data.txt", "/Volumes/LaCie/Tesis/Datos Tratados/Datos2024_2tratados/19062024/TR_0_0_data.txt", "/Users/marcosbautista/Desktop/pruebas/GE_g6.txt",5)


   ifstream in1;
   ifstream in2;
   ifstream in3;
   ifstream in4;


  in1.open(file);
  in2.open(file2);
  in3.open(file3);
  in4.open(file4);


  std::ofstream out1 (fileout, std::ofstream::out);

  float volt, volt2, volt3;
  float volt4, volt5;

  for(Int_t i=0; i <= 1024*(group-1); i++)
  {
    in1>>volt;
    in2>>volt2;
    in3>>volt3;
    in4>>volt4;

  }
  for(Int_t j=0; j <= 1024; j++)
  {
    in1>>volt;
    in2>>volt2;
    in3>>volt3;
    in4>>volt4;

  out1 << volt << " " <<volt2 << " " << volt3 <<  " " << volt4 <<  endl; //volt2 << endl;
  //out1 << volt << " " <<volt2 << " " << volt3 <<  " " << volt4 <<  " " << volt5 <<  endl; //volt2 << endl;
  //  out1 << volt << " " <<volt2 << " " << volt3 << endl; //volt2 << endl;

  }
  out1.close();
}
