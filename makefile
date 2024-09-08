# Variables
CC = gcc
CFLAGS = -I./include
SRCDIR = src
OBJDIR = obj
TARGET = main
SRCFILES = main.c menu.c opciones.c utils.c validaciones.c
OBJFILES = $(SRCFILES:.c=.o)
OBJS = $(addprefix $(OBJDIR)/, $(OBJFILES))


all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)


$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)
