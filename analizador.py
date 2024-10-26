import matplotlib.pyplot as plt
import sys

#Ejecutar como "python <ruta_tiempos> <ruta_grafico>"
def leer_archivo(ruta_archivo):
    x_vals = []
    tiempos_por_linea = []

    with open(ruta_archivo, 'r') as file:
        for linea in file:
            thread, tiempos = linea.strip().split(';')
            x_vals.append(int(thread))
            tiempos_por_linea.append([float(t) for t in tiempos.split(',')])

    return x_vals, tiempos_por_linea


def graficar_lineas(x_vals, tiempos_por_linea, ruta_png):
    num_lineas = len(tiempos_por_linea[0])

    for i in range(num_lineas):
        tiempos_i = [tiempos[i] for tiempos in tiempos_por_linea]
        plt.plot(x_vals, tiempos_i, label=f"Repetición {i+1}", marker='o')

    plt.ylim(0, 60)
    plt.xlabel("Cant. Threads")
    plt.ylabel("Tiempo de ejecución (en seg)")
    plt.title("Gráfico de tiempo de ejecución por cantidad de threads")
    plt.legend()
    plt.grid(True)

    plt.savefig(ruta_png)


if __name__ == "__main__":
    ruta_tiempos = sys.argv[1]  
    ruta_png = sys.argv[2]
    x_vals, tiempos_por_linea = leer_archivo(ruta_tiempos)
    graficar_lineas(x_vals, tiempos_por_linea, ruta_png)
