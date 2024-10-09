.PHONY: all clean menu_principal menu_secundario

# Compilar ambos proyectos
all: menu_principal menu_secundario

# Compilar menu_principal y mover el ejecutable al nivel superior sin renombrarlo
menu_principal:
	$(MAKE) -C menu_principal
	mv menu_principal/main ./main

# Compilar menu_secundario y dejar el ejecutable dentro de menu_secundario
menu_secundario:
	$(MAKE) -C menu_secundario

# Limpiar ambos proyectos
clean:
	$(MAKE) -C menu_principal clean
	$(MAKE) -C menu_secundario clean
	rm -f main