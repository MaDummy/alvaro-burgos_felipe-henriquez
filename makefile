.PHONY: all clean menu_principal menu_secundario conteo_paralelo indice_invertido

# Compilar ambos proyectos
all: menu_principal menu_secundario conteo_paralelo indice_invertido

# Compilar menu_principal y mover el ejecutable al nivel superior sin renombrarlo
menu_principal:
	$(MAKE) -C menu_principal
	mv menu_principal/main ./main

# Compilar menu_secundario y dejar el ejecutable dentro de menu_secundario
menu_secundario:
	$(MAKE) -C menu_secundario

conteo_paralelo:
	$(MAKE) -C conteo_paralelo

indice_invertido:
	$(MAKE) -C indice_invertido

# Limpiar ambos proyectos
clean:
	$(MAKE) -C menu_principal clean
	$(MAKE) -C menu_secundario clean
	$(MAKE) -C conteo_paralelo clean
	$(MAKE) -C indice_invertido clean
	rm -f main