all:	filter.c filter_serial.c senial.h inputSig.h
	gcc -fopenmp -o filter filter.c
	gcc -o filter_serial filter_serial.c

clean:	filter filter_serial
	rm filter filter_serial
