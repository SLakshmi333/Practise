all:output

output:file1.o
	gcc -o output file1.o
file1.o:file1.c
	gcc -c -g -Wall file1.c

clean:
	rm -f *.o output

