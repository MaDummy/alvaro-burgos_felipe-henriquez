# Variables
CC = gcc
CFLAGS = -I./include -I/usr/local/include/cjson  # Incluye la ruta a los encabezados de cJSON
LDFLAGS = -L/usr/local/lib -lcjson           # Incluye la ruta a las bibliotecas de cJSON
SRCDIR = src
OBJDIR = obj
TARGET = main
SRCFILES = main.c menu.c opciones.c utils.c validaciones.c
OBJFILES = $(SRCFILES:.c=.o)
OBJS = $(addprefix $(OBJDIR)/, $(OBJFILES))


all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)


$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)
