//In this code 4 different files are read (trigger 1, trigger 2, FDD and Analogic FDD) in order to select only the lines belonging to an especific group.
//The output file contains the 1024 lines of each signal.
//It is neccesary to establish where the files are located.

void Group_Extractor_RPC(string file, string file2, string file3, string file4, string fileout, Int_t group) //string  file2,
{

  //cd Documents/NewCodes
  //root.exe Group_Extractor_RPC.C("/Users/marcosbautista/Desktop/Datos2023_2/acorde3_middle/pedestal/SIPM_ACORDE.txt", "/Users/marcosbautista/Desktop/Datos2023_2/acorde3_middle/pedestal/PMT_up_data.txt","/Users/marcosbautista/Desktop/Datos2023_2/acorde3_middle/pedestal/PMT_down_data.txt", "/Users/marcosbautista/Desktop/Datos2023_2/acorde3_middle/pedestal/TR_0_0_data.txt", "/Users/marcosbautista/Desktop/Datos2023_2/acorde3_middle/pedestal/GE_ACORDE.txt",5)

  //root.exe Group_Extractor_RPC.C'("/home/yael/shared-drives/E:/Pruebas_YAVB/Prueba_15_RPC_Puras_11.8KV/RPC.txt", "/home/yael/shared-drives/E:/Pruebas_YAVB/Prueba_15_RPC_Puras_11.8KV/Up.txt","/home/yael/shared-drives/E:/Pruebas_YAVB/Prueba_15_RPC_Puras_11.8KV/Down.txt", "/home/yael/shared-drives/E:/Pruebas_YAVB/Prueba_15_RPC_Puras_11.8KV/TR_0_0.txt", "/home/yael/shared-drives/E:/Pruebas_YAVB/Group.txt",5)'
  //root.exe Group_Extractor_RPC.C'("/home/yael/shared-drives/E:/Pruebas_YAVB/Prueba_16_RPC_Puras_11.8KV/RPC.txt", "/home/yael/shared-drives/E:/Pruebas_YAVB/Prueba_16_RPC_Puras_11.8KV/Up.txt","/home/yael/shared-drives/E:/Pruebas_YAVB/Prueba_16_RPC_Puras_11.8KV/Down.txt", "/home/yael/shared-drives/E:/Pruebas_YAVB/Prueba_16_RPC_Puras_11.8KV/TR_0_0.txt", "/home/yael/shared-drives/E:/Pruebas_YAVB/Group.txt",5)'

   ifstream in1;
   ifstream in2;
   ifstream in3;
   ifstream in4;
   //ifstream in5;

  in1.open(file);
  in2.open(file2);
  in3.open(file3);
  in4.open(file4);
  //in5.open(file5);

  std::ofstream out1 (fileout, std::ofstream::out);

  float volt, volt2, volt3;
  float volt4, volt5;

  for(Int_t i=0; i <= 1024*(group-1); i++)
  {
    in1>>volt;
    in2>>volt2;
    in3>>volt3;
    in4>>volt4;
  //  in5>>volt5;
  }
  for(Int_t j=0; j <= 1024; j++)
  {
    in1>>volt;
    in2>>volt2;
    in3>>volt3;
    in4>>volt4;
  //  in5>>volt5;
  out1 << volt << " " <<volt2 << " " << volt3 <<  " " << volt4 <<  endl; //volt2 << endl;
  //out1 << volt << " " <<volt2 << " " << volt3 <<  " " << volt4 <<  " " << volt5 <<  endl; //volt2 << endl;
  //  out1 << volt << " " <<volt2 << " " << volt3 << endl; //volt2 << endl;

  }
  out1.close();
}
