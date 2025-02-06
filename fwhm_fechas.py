import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

file_path = '/Users/marcosbautista/Desktop/cop_FWHM_fech.csv'
data = pd.read_csv(file_path)


data['FWHM1'] = pd.to_numeric(data['FWHM1'], errors='coerce')
data['FWHM2'] = pd.to_numeric(data['FWHM2'], errors='coerce')
data['FWHM3'] = pd.to_numeric(data['FWHM3'], errors='coerce')


fwhm1_min, fwhm1_max = 0.01, 3
fwhm2_min, fwhm2_max = 0.01, 3
fwhm3_min, fwhm3_max = 0.01, 3


data_fwhm1 = data[(data['FWHM1'] >= fwhm1_min) & (data['FWHM1'] <= fwhm1_max)]
data_fwhm2 = data[(data['FWHM2'] >= fwhm2_min) & (data['FWHM2'] <= fwhm2_max)]
data_fwhm3 = data[(data['FWHM3'] >= fwhm3_min) & (data['FWHM3'] <= fwhm3_max)]



def graficar_puntos_con_promedio(data, columna, nombre, color):

    promedio = data[columna].mean()
    

    plt.figure(figsize=(9, 7))
    plt.scatter(data.index, data[columna], color=color, alpha=0.8, label=nombre)
    plt.axhline(y=promedio, color='red', linestyle='--', label=f'Promedio (ns) = {promedio:.2f}' )
    plt.title(f'{nombre}')
    plt.xlabel('Índice')
    plt.ylabel(f'{columna} (ns)')
    plt.legend()
    plt.grid(alpha=0.5, linestyle='--')
    
    intervalos = [-0.5, 42.5, 62.5, 90.5]
    for x in intervalos:
        plt.axvline(x=x, color='gray', linestyle='--', linewidth=1)

    x_ticks = [20, 50 , 75]
    x_labels = ['Abril-Mayo 2023', 'Octubre-Diciembre 2023', 'Enero-Julio 2024']

    plt.xticks(ticks=x_ticks, labels=x_labels, rotation=5)
    
    plt.show()

graficar_puntos_con_promedio(data_fwhm1, 'FWHM1', 'Voltaje vs FWHM1 (PMT up - PMT down)', 'red')
graficar_puntos_con_promedio(data_fwhm2, 'FWHM2', 'Voltaje vs FWHM2 (PMT up - RPC)', 'blue')
graficar_puntos_con_promedio(data_fwhm3, 'FWHM3', 'Voltaje vs FWHM3 (PMT down - RPC)', 'green')
