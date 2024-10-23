CC = gcc
CFLAGS = -I./include
SRCDIR = src
OBJDIR = obj
TARGET = main

# Definir las rutas para los archivos que están en otras carpetas
OTHER_SRC_DIR = ../conteo_paralelo/src

# Añadir aquí todos los archivos .c, incluyendo los de otras carpetas
SRCFILES = main.c
OTHER_SRCFILES = menu.c cuenta_pal.c utils.c stopwords.c # El archivo `menu.c` está en una carpeta diferente

# Convertir los archivos .c a archivos .o
OBJFILES = $(SRCFILES:.c=.o)
OTHER_OBJFILES = $(OTHER_SRCFILES:.c=.o)

OBJS = $(addprefix $(OBJDIR)/, $(OBJFILES)) $(addprefix $(OBJDIR)/, $(OTHER_OBJFILES))

all: $(TARGET)

# Regla para compilar el ejecutable final
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Regla para compilar los archivos .c a .o de la carpeta principal
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para compilar los archivos .c a .o de la carpeta distinta
$(OBJDIR)/%.o: $(OTHER_SRC_DIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Crear el directorio obj si no existe
$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)
