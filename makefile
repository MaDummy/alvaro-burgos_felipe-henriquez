.PHONY: all clean menu_principal menu_secundario indice_invertido planificador distribuidor core ejecutador conteo_paralelo buscador cache motor_busqueda programa_principal

all: menu_principal menu_secundario indice_invertido planificador distribuidor core ejecutador conteo_paralelo buscador cache motor_busqueda programa_principal

programa_principal:
	$(MAKE) -C programa_principal
	mv programa_principal/main ./main

menu_principal:
	$(MAKE) -C menu_principal

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

ejecutador:
	$(MAKE) -C ejecutador

buscador:
	$(MAKE) -C buscador

cache:
	$(MAKE) -C cache

motor_busqueda:
	$(MAKE) -C motor_busqueda

clean:
	$(MAKE) -C programa_principal clean
	$(MAKE) -C menu_principal clean
	$(MAKE) -C menu_secundario clean
	$(MAKE) -C indice_invertido clean
	$(MAKE) -C planificador clean
	$(MAKE) -C distribuidor clean
	$(MAKE) -C core clean
	$(MAKE) -C ejecutador clean
	$(MAKE) -C conteo_paralelo clean
	$(MAKE) -C buscador clean
	$(MAKE) -C cache clean
	$(MAKE) -C motor_busqueda clean
	rm -f main