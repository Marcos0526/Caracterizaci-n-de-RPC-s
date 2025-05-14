

void RPC_CHARGE_TIME_TRIGGERS(string file, string  file2, string  file3, string fileout)
{
  //root.exe RPC_CHARGE_TIME_TRIGGERS.C("/Volumes/LaCie/Tesis/Datos Tratados/Datos2024_2tratados/03072024/RPC.txt", "/Volumes/LaCie/Tesis/Datos Tratados/Datos2024_2tratados/03072024/PMT_up_data.txt", "/Volumes/LaCie/Tesis/Datos Tratados/Datos2024_2tratados/03072024/PMT_down_data.txt", "/Volumes/LaCie/Tesis/Datos Tratados/Datos2024_2tratados/03072024/PPP3600RPC.txt")
    
    ifstream in1;
    ifstream in2;
    ifstream in3;

    TGraph* gr1 = new TGraph(1024);
    TGraph* gr2 = new TGraph(1024);
    TGraph* gr3 = new TGraph(1024);


   in1.open(file);
   in2.open(file2);
   in3.open(file3);

   std::ofstream out1 (fileout, std::ofstream::out);
   float volt, volt2, volt3, pmin, basement=0, basementUp=0, basementDown=0,rpc[10000], trigger1[10000], trigger2[10000], time[10000];
   Int_t lines=0, group=0, m,c1=0,c2=0,c3=0, two = 0, three = 0, c=1;
   long int total;
   float a,b,a2,b2,a3,b3,t1,t2,t3,t4, bm, minVal, maxVal, amp, th, level, downA, totalA, bmUp, bmDown, minValUp, minValDown, maxValUp, maxValDown, downAUp, downADown, totalAUp, totalADown;
   while (!in2.eof())
   {
     pmin=0;
     in1>>volt;
     in2>>volt2;
     in3>>volt3;

     if(lines<=1024)
     {
       rpc[lines]=volt;
       trigger1[lines]=volt2;
       trigger2[lines]=volt3;
       time[lines]=lines;
       gr1->SetPoint(lines,lines, trigger1[lines]);
       gr2->SetPoint(lines,lines, trigger2[lines]);
       lines=lines+1;
     }

     if(lines == 1024)
     {
       group++;
       minVal = rpc[0];
       maxVal = rpc[0];
       minValUp = trigger1[0];
       maxValUp = trigger1[0];
       minValDown = trigger2[0];
       maxValDown = trigger2[0];
       t1=0; t2=0; t3=0;
       c1 = 0; c2 =0; c3 = 0;

       for(Int_t j=0;j<=1024;j++)
       {
         if(trigger1[j]<3600 && trigger1[j]>1000) //negative slope
         {
           c1++;
           if (c1 == 1) {
             t1 = time[j];
               
             //cout<<" "<<trigger1[j]<<" ";
               
           }
         }
       }

       for(Int_t k=0;k<=1024;k++)
       {
         if(trigger2[k]<3600 && trigger2[k]>1000) //negative slope
         {
           c2++;
           if (c2 == 1) {
             t2 = time[k];
             //cout<<" "<<trigger2[k]<<" ";
           }
         }
       }

       for(Int_t l=0;l<=1024;l++)
       {
         if(rpc[l]<3600 && rpc[l]>1000) //negative slope
         {
           c3++;
           if (c3 == 1) {
             t3 = time[l];
            // cout<<" "<<rpc[l]<<" ";
           }
         }
       }

       

       //RPC

       minVal = rpc[0];
       maxVal = rpc[0];
       basement = 0;
       bm =0;
       for (Int_t i = 0; i <= lines; i++)
       {  
         if (i<20) {
           basement = basement + rpc[i];
         //if (i>993 && i < 1014) {
         //  basement = basement + sipm[i];
         }
         if (rpc[i] < minVal && i < 1024) {
           minVal = rpc[i];
           pmin = i;
         }
         if (rpc[i] > maxVal)
           maxVal = rpc[i];
       }

       bm = basement/20;

       for(Int_t g=0;g<1014;g++)
       {
         downA=(((time[g+1]-time[g])*(rpc[g+1]))+((time[g+1]-time[g])*(rpc[g]-(rpc[g+1])))/2)+downA;
       }
       totalA=(bm*1014)-downA; //=200/1024 * 1014


       //PMT UP

       minValUp = trigger1[0];
       maxValUp = trigger1[0];
       basementUp = 0;
       bmUp =0;
       for (Int_t i = 0; i <= lines; i++)
       {
         if (i<20) {
           basementUp = basementUp + trigger1[i];
         }
         if (trigger1[i] < minValUp && i < 1024) {
           minValUp = trigger1[i];
         }
         if (trigger1[i] > maxValUp)
           maxValUp = trigger1[i];
       }

       bmUp = basementUp/20;

       for(Int_t g=0;g<1014;g++)
       {
         downAUp=(((time[g+1]-time[g])*(trigger1[g+1]))+((time[g+1]-time[g])*(trigger1[g]-(trigger1[g+1])))/2)+downAUp;
       }
       totalAUp=(bmUp*1014)-downAUp; //=200/1024 * 1014

       //PMT DOWN

       minValDown = trigger2[0];
       maxValDown = trigger2[0];
       basementDown = 0;
       bmDown =0;
       for (Int_t i = 0; i <= lines; i++)
       {
         if (i<20) {
           basementDown = basementDown + trigger2[i];
         }
         if (trigger2[i] < minValDown && i < 1024) {
           minValDown = trigger2[i];
         }
         if (trigger2[i] > maxValDown)
           maxValDown = trigger2[i];
       }

       bmDown = basementDown/20;

       for(Int_t g=0;g<1014;g++)
       {
         downADown=(((time[g+1]-time[g])*(trigger2[g+1]))+((time[g+1]-time[g])*(trigger2[g]-(trigger2[g+1])))/2)+downADown;
       }
       totalADown=(bmDown*1014)-downADown; //=200/1024 * 1014


       if(t1!=0 && t2!=0 && t3!=0)
       {
         two++;
         three++;
         out1<<t1<<" "<<t2<<" "<<t3<<" "<< totalA << " " << totalAUp << " " << totalADown << " " << group << " " << two << " " << three << endl;
         cout<<t1<<" "<<t2<<" "<<t3<<" "<< totalA << " " << totalAUp << " " << totalADown << " " << group << " " << two << " " << three << endl;
       }

       else if (t1!=0 && t2!=0)
       {
         two++;
         out1<<t1<<" "<<t2<<" "<<t3<<" "<< totalA << " " << totalAUp << " " << totalADown << " " << group << " " << two << " " << three << endl;
         cout<<t1<<" "<<t2<<" "<<t3<<" "<< totalA << " " << totalAUp << " " << totalADown << " " << group << " " << two << " " << three << endl;
       }
       downA=0;
       downAUp=0;
       downADown=0;
       lines=0;

     }
   }
   out1.close();
 }
