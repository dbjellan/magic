CC=g++
CFLAGS=-Wall

all: regenerate main

regenerate:
	yacc -d grammar.y
	lex tokens.l

main: data.o grammar.o tokens.o magic.o
	$(CC) $(CFLAGS) data.o tokens.o magic.o grammar.o -o magic

magic.o:
	$(CC) $(CFLAGS) -c magic.c -o magic.o

tokens.o:
	$(CC) $(CFLAGS) -c lex.yy.c -o tokens.o

grammar.o:
	$(CC) $(CFLAGS) -c y.tab.c -o grammar.o

data.o:
	$(CC) $(CFLAGS) -c data.c

clean:
	rm *.o magic
