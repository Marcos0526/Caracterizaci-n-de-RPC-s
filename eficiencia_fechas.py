import pandas as pd
import matplotlib.pyplot as plt


data = pd.read_csv('/Users/marcosbautista/Desktop/2_eficiencia_fechas.csv')


data = data[data['Eficiencia'] > 0]


data_red = data.tail(27)


data_blue = data.iloc[:-27]


data_blue = data_blue[data_blue['Eficiencia'] > 0]


plt.figure(figsize=(22, 13))


plt.scatter(range(len(data_blue)), data_blue['Eficiencia'], color='blue', label='Datos recolectados en 2023')


plt.scatter(range(len(data_blue), len(data_blue) + len(data_red)), data_red['Eficiencia'], color='red', label='Datos recolectados en 2024')


plt.title('Eficiencia de los Datos')
plt.xlabel('Fechas')
plt.ylabel('Eficiencia (%)')
plt.ylim(-7, 100)
plt.legend()
plt.grid(True, axis='y')
 
intervalos = [-0.5, 28.5, 47.5, 74.5]
for x in intervalos:
    plt.axvline(x=x, color='gray', linestyle='--', linewidth=1)

x_ticks = [14, 39, 62]
x_labels = ['Abril-Mayo 2023', 'Octubre-Diciembre 2023', 'Enero-Julio 2024']

plt.xticks(ticks=x_ticks, labels=x_labels, rotation=0)
y_ticks = range(0, 101, 10)
plt.yticks(ticks=y_ticks)

plt.show()
