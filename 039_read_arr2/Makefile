CFLAGS=-std=gnu99 -pedantic -Wall
test:test.o
	gcc -o test test.o
%.o:%.c
	gcc $(CFLAG) -c $<
.PHONY:clean
clean:
	rm -f myProgram *.o *.c~ 
