#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <array>
#include <vector>
#include "TCanvas.h"
#include "TGraph.h"
#include "TMath.h"
#include "TAxis.h"
#include "TH2.h"

std::ifstream::pos_type filesize(const char* filename) {
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

void Binary_Analyzer() {
    Int_t nEvents = -1;
    int numFiles;
    std::cout << "Ingrese el número de archivos a procesar (1-6): ";
    std::cin >> numFiles;

    std::vector<std::string> files(numFiles);
    std::vector<std::string> fileouts(numFiles);
    std::vector<std::ifstream> inputFiles(numFiles);
    std::vector<std::ofstream> outputFiles(numFiles);
    std::vector<TH2*> histograms(numFiles);

    for (int i = 0; i < numFiles; ++i) {
        std::cout << "Ingrese la ruta del archivo " << i + 1 << ": ";
        std::cin >> files[i];
        std::cout << "Ingrese la ruta del archivo de salida " << i + 1 << ": ";
        std::cin >> fileouts[i];
        inputFiles[i].open(files[i], std::ios::binary);
        outputFiles[i].open(fileouts[i], std::ofstream::out);
    }

    const UInt_t eventSz = 1024;
    std::array<float, eventSz> buffer;
    float samplingrate = 1; // sampling rate = 1GS/s
    Int_t dataPointSz = sizeof(buffer[0]);
    Double_t dt[eventSz];
    Double_t ampRes;
    std::cout << "Ingrese la resolución de amplitud (ampRes): ";
    std::cin >> ampRes;

    for (int i = 0; i < eventSz; ++i) {
        dt[i] = i * samplingrate;
    }

    for (int i = 0; i < numFiles; ++i) {
        int fSize = filesize(files[i].c_str());
        histograms[i] = new TH2D(("h2Signal" + std::to_string(i + 1)).c_str(), "Signal Average; time (ns);Amplitude (mV);", 1024, 0, samplingrate * 1023, 4096 * 2, -4096 * ampRes, 4095 * ampRes);
        Int_t nTotalEvents = fSize / (eventSz * dataPointSz);
        if (nEvents < 0) nEvents = nTotalEvents;

        std::stringstream bufferStream;
        for (Int_t event = 0; event < nEvents; ++event) {
            readAndFill(inputFiles[i], buffer, histograms[i], bufferStream, dt, ampRes);
        }
        outputFiles[i] << bufferStream.str();
    }

    gStyle->SetOptTitle(kFALSE);
    gStyle->SetPalette(kSolar);
    for (int i = 0; i < numFiles; ++i) {
        TCanvas* canvas = new TCanvas(("can" + std::to_string(i + 1)).c_str(), ("Signal " + std::to_string(i + 1)).c_str(), 1400, 800);
        histograms[i]->Draw("COLZ");
    }
} 