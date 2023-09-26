CC=gcc
CFLAGS=-Wall -g
EXAMPLES = aritmeticas1 aritmeticas2 comparaciones funciones1 funciones2 funciones3 funciones4 if1 if2 if3 logicas1 logicas2 vectores1 vectores2 vectores3 vectores4 while
ERR = error_ej1 error_ej2 error_se2 error_se3 error_se4 error_se5 error_se6 error_se7 error_se8 error_se9 error_se10 error_se11 error_se12 error_se13 error_se14 error_se15
EXE = alfa $(EXAMPLES) $(ERR)
all: $(EXE)

alfa: alfa.c lex.yy.o y.tab.o generacion.o hash_table.o
	$(CC) $(CFLAGS) $^ -o $@

generacion.o: generacion.c generacion.h
	$(CC) $(CFLAGS) -c $<

hash_table.o: hash_table.c hash_table.h
	$(CC) $(CFLAGS) -c $<

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c $^

y.tab.o: y.tab.c
	$(CC) $(CFLAGS) -c $<

lex.yy.c: alfa.l y.tab.h
	flex $<

y.tab.c: alfa.y
	bison -d -y -v $^

y.tab.h: alfa.y
	bison -d -y -v $^

${EXAMPLES}: %: alfa examples/%.alf
	./alfa examples/$@.alf examples/$@.asm
	nasm -g -o examples/$@.o -f elf32 examples/$@.asm
	gcc -m32 -o examples/$@ examples/$@.o ./alfalib.o

${ERR}: %: alfa errors/%.alf
	./alfa errors/$@*.alf errors/$@.asm

alfa.c:
	@echo "Empty" > /dev/null

.PHONY: clean
clean:
	rm -rf *.o alfa lex.yy.* y.tab.* y.output *.asm
	cd errors && $(MAKE) clean
	cd examples && $(MAKE) clean
