TARGET   = bin/bpp

CC       = gcc
# compiling flags here
CFLAGS   = -c -std=c99 -I inc

LINKER   = gcc
# linking flags here
LFLAGS   = -Wall -I. -lm

OBJECTS += src/main.o
OBJECTS += src/token.o

OBJECTS += src/lexer/lexer.o

OBJECTS += src/parser/ast_node.o
OBJECTS += src/parser/parser.o

OBJECTS += src/util/string.o
OBJECTS += src/util/vector.o

rm       = rm -f

$(TARGET): $(OBJECTS)
	$(LINKER) -o $@ $(LFLAGS) $^ -lgcc
%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"

.PHONY: run
run:
	@bin/bpp
