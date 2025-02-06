import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

data = pd.read_csv('/Users/marcosbautista/Desktop/2restemp.csv')

data = data.apply(pd.to_numeric, errors='coerce').replace(0, np.nan).dropna()


if data.shape[1] < 4:
    raise ValueError("El archivo debe tener al menos 4 columnas, incluyendo eficiencia y FWHM.")


data = data[data['ef'] > 1]


data = data[
    (data['FWHM1'] >= -1) & (data['FWHM1'] <= 4) &
    (data['FWHM2'] >= -1) & (data['FWHM2'] <= 4) &
    (data['FWHM3'] >= -1) & (data['FWHM3'] <= 4)
]

def graficar_puntos(data, nombre_columna):

    eficiencia = data['ef']
    valores = data[nombre_columna]
    
 
    promedio = np.mean(valores)
    print(f'Estadísticas para {nombre_columna}:')
    print(f'  Promedio: {promedio:.2f}\n')

 
    plt.figure(figsize=(8, 5))
    plt.scatter(eficiencia, valores, color='blue', alpha=0.7, label=nombre_columna)
    plt.axhline(y=promedio, color='red', linestyle='--', linewidth=1.5, label=f'Promedio = {promedio:.2f}')
    plt.title(f'Eficiencia vs {nombre_columna}')
    plt.xlabel('Eficiencia')
    plt.ylabel(nombre_columna)
    plt.ylim(-1, 4)  # Limitar eje Y entre -1 y 4
    plt.legend()
    plt.grid(axis='both', linestyle='--', alpha=0.7)
    plt.show()

graficar_puntos(data, 'FWHM1')
graficar_puntos(data, 'FWHM2')
graficar_puntos(data, 'FWHM3')
