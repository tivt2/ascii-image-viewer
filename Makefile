PROJ=ascii-renderer

CFLAGS=-Wall -Wextra -Werror -pedantic -g -O0
CC=clang

SRCDIR=src
SRCS=$(wildcard $(SRCDIR)/*.c)
OBJDIR=obj
OBJS=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(PROJ)

run: all
	./$(PROJ)

$(PROJ): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@ mkdir $@

clean:
	$(RM) $(OBJDIR)/* $(PROJ)
	@ rmdir $(OBJDIR)
