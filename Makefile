all:	filter.c senial.h inputSig.h
	gcc -fopenmp -o filter filter.c

clean:	filter
	rm filter
	rm *~
