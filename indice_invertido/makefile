CC = gcc
CFLAGS = -I./include 
LDFLAGS = -L/usr/local/lib 
SRCDIR = src
OBJDIR = obj
TARGET = main
SRCFILES = main.c menu.c utils.c file_utils.c
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
