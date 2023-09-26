CC = gcc
CFLAGS = -Wall -Wextra -pedantic 
LDLIBS = -lodbc

EXE = odbc-connection-test odbc-connection-test-2 odbc-example1 odbc-example2 odbc-example3 odbc-example4 dvdreq dvdrent dvdfilm

all : $(EXE)

clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o odbc.o
