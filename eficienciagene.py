import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns


data = pd.read_csv('/Users/marcosbautista/Desktop/2ef.csv')


data.columns = ['voltaje', 'eficiencia']


data = data[data['eficiencia'] > 0]


print(data.head())
print("Nombres de columnas:", data.columns)


plt.figure(figsize=(22, 13))
plt.scatter(data['voltaje'], data['eficiencia'])
plt.xlabel('Voltaje (V)')
plt.ylabel('Porcentaje de Éxito (%)')
plt.title('Relación entre Voltaje y Eficiencia')
plt.show()


correlation = data.corr()
print("Correlación entre voltaje y eficiencia:\n", correlation)


bins = list(range(9200, 10401, 200))
data['rango'] = pd.cut(data['voltaje'], bins=bins)


promedio_por_rango = data.groupby('rango')['eficiencia'].mean()


print("Promedio de éxito por rango de voltaje:")
for rango, promedio in promedio_por_rango.items():
    print(f"{rango}: {promedio:.2f}%")
