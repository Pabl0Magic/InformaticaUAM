CC = gcc
BISON = bison
FLEX = flex

BIN = pruebaSintactico
CFLAGS = -Wall -ansi -pedantic
CYYFLAGS = -ansi -pedantic
BISONFLAGS = -d -y -v

all: ${BIN}

${BIN}:%: y.tab.o lex.yy.o %.o
	$(CC) -o $@ $^

lex.yy.o: lex.yy.c
	$(CC) ${CYYFLAGS} -c -o $@ $<

y.tab.o: y.tab.c
	$(CC) ${CYYFLAGS} -c -o $@ $<

%.o: %.c
	$(CC) ${CFLAGS} -c -o $@ $<

y.tab.c: alfa.y
	$(BISON) $(BISONFLAGS) alfa.y

y.tab.h: alfa.y
	$(BISON) $(BISONFLAGS) alfa.y

lex.yy.c: alfa.l y.tab.h
	$(FLEX) alfa.l

clean:
	rm -rvf $(BIN) *.o lex.yy.c y.tab.h y.tab.c y.output

