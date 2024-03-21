PROJ=ascii-image-viewer

CFLAGS=-Wall -Wextra -Werror -pedantic -g -O0 -fsanitize=address
LINKS=-lm
CC=clang

SRCDIR=src
SRCS=$(wildcard $(SRCDIR)/*.c)
OBJDIR=obj
OBJS=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(PROJ)

run: all
	./$(PROJ)

$(PROJ): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LINKS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@ mkdir $@

clean:
	$(RM) $(OBJDIR)/* $(PROJ)
	@ rmdir $(OBJDIR)
