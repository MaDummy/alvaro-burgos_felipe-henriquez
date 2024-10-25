import matplotlib.pyplot as plt
import sys

#Ejecutar como "python <ruta_analizador> <ruta_grafico>"
def leer_archivo(ruta_archivo):
    x_vals = []
    tiempos_por_linea = []

    with open(ruta_archivo, 'r') as file:
        for linea in file:
            # Separar la línea por el ';' para obtener el índice y los tiempos
            indice, tiempos = linea.strip().split(';')
            # Convertir el índice en número y añadirlo a x_vals
            x_vals.append(int(indice))
            # Separar los tiempos, convertir a float, y agregar a la lista de tiempos
            tiempos_por_linea.append([float(t) for t in tiempos.split(',')])

    return x_vals, tiempos_por_linea


def graficar_lineas(x_vals, tiempos_por_linea):
    # Asumimos que todas las líneas tienen el mismo número de tiempos
    num_lineas = len(tiempos_por_linea[0]) if tiempos_por_linea else 0

    for i in range(num_lineas):
        tiempos_i = [tiempos[i] for tiempos in tiempos_por_linea]
        plt.plot(x_vals, tiempos_i, label=f"Línea {i+1}", marker='o')  # Graficar cada línea

    plt.xlabel("Índice")
    plt.ylabel("Tiempos")
    plt.title("Gráfico de Líneas Escalable")
    plt.legend()  # Mostrar la leyenda de las líneas
    plt.grid(True)  # Añadir cuadrícula

    # Guardar el gráfico en un archivo PNG
    plt.savefig("grafico.png")  # Guardar el gráfico como 'grafico.png'
    plt.show()  # Mostrar el gráfico


if __name__ == "__main__":
    ruta_tiempos = sys.argv[1]  
    ruta_png = sys.argv[2]
    x_vals, tiempos_por_linea = leer_archivo(ruta_tiempos)
    graficar_lineas(x_vals, tiempos_por_linea)
