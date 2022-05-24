all:output

output:file.o
	gcc -o output file.o
file.o:file.c
	gcc -c -g -Wall file.c

clean:
	rm -f *.o output

