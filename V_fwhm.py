import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


file_path = '/Users/marcosbautista/Desktop/CSV/cop_V_FWHM.csv'
data = pd.read_csv(file_path)


data['Voltaje'] = pd.to_numeric(data['Voltaje'])
data['FWHM1'] = pd.to_numeric(data['FWHM1'])
data['FWHM2'] = pd.to_numeric(data['FWHM2'])
data['FWHM3'] = pd.to_numeric(data['FWHM3'])


voltaje_min, voltaje_max = 9200, 10400
fwhm1_min, fwhm1_max = 0.01, 3
fwhm2_min, fwhm2_max = 0.01, 3
fwhm3_min, fwhm3_max = 0.01, 3

data1 = data[(data['Voltaje'] >= voltaje_min) & (data['Voltaje'] <= voltaje_max) & 
            (data['FWHM1'] >= fwhm1_min) & (data['FWHM1'] <= fwhm1_max)]
data2 = data[(data['FWHM2'] >= fwhm2_min) & (data['FWHM2'] <= fwhm2_max) & 
            (data['Voltaje'] >= voltaje_min) & (data['Voltaje'] <= voltaje_max)]

data3 = data[(data['FWHM3'] >= fwhm3_min) & (data['FWHM3'] <= fwhm3_max) & 
            (data['Voltaje'] >= voltaje_min) & (data['Voltaje'] <= voltaje_max)]

def graficar_voltaje_vs_fwhm(data, columna, nombre, color):
    plt.figure(figsize=(8, 6))
    plt.scatter(data['Voltaje'], data[columna], color=color, alpha=0.8)
    plt.title(f'Voltaje vs {nombre}')
    plt.xlabel('Voltaje')
    plt.ylabel(f'{columna}(ns)' )
    plt.ylim(1, 2.5)
    plt.grid(alpha=0.5, linestyle='--')
    plt.show()


graficar_voltaje_vs_fwhm(data1, 'FWHM1', 'FWHM1 (PMT up - PMT down)', 'red')
graficar_voltaje_vs_fwhm(data2, 'FWHM2', 'FWHM2 (PMT up - RPC)', 'blue')
graficar_voltaje_vs_fwhm(data3, 'FWHM3', 'FWHM3 (PMT down - RPC)', 'green')
