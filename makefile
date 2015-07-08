CC=g++
CFLAGS=-Wall

all: regenerate main

regenerate:
	yacc -d grammar.y
	lex tokens.l

main: data.o grammar.o tokens.o magic.o ast.o util.o
	$(CC) $(CFLAGS) data.o tokens.o magic.o grammar.o ast.o util.o -o magic

util.o:
	$(CC) $(CFLAGS) -c util.c -o util.o	

ast.o:
	$(CC) $(CFLAGS) -c ast.c -o ast.o	

magic.o:
	$(CC) $(CFLAGS) -c magic.c -o magic.o

tokens.o:
	$(CC) $(CFLAGS) -c lex.yy.c -o tokens.o

grammar.o:
	$(CC) $(CFLAGS) -c y.tab.c -o grammar.o

data.o:
	$(CC) $(CFLAGS) -c data.c

clean:
	rm *.o magic lex.yy.c y.tab.h y.tab.c