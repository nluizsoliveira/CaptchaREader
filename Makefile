all: clean main.o compile clean

compile:
	@gcc main.o -o trab3 -g -lm

main.o:
	@gcc -c main.c -g

clean:
	@find -name '*~' | xargs rm -rf {}
	@find -name '*.o' | xargs rm -rf {}

run:
	@./trab3

zip:
	zip -r trab3.zip *.c *.h Makefile
