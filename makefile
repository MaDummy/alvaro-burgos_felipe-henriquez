.PHONY: all clean menu_principal menu_secundario conteo_paralelo indice_invertido planificador distribuidor core

all: menu_principal menu_secundario conteo_paralelo indice_invertido

menu_principal:
	$(MAKE) -C menu_principal
	mv menu_principal/main ./main

menu_secundario:
	$(MAKE) -C menu_secundario

conteo_paralelo:
	$(MAKE) -C conteo_paralelo

indice_invertido:
	$(MAKE) -C indice_invertido

planificador:
	$(MAKE) -C planificador

distribuidor:
	$(MAKE) -C distribuidor

core:
	$(MAKE) -C core

clean:
	$(MAKE) -C menu_principal clean
	$(MAKE) -C menu_secundario clean
	$(MAKE) -C conteo_paralelo clean
	$(MAKE) -C indice_invertido clean
	$(MAKE) -C planificador clean
	$(MAKE) -C distribuidor clean
	$(MAKE) -C core clean
	rm -f main