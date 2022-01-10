CFLAGS=-std=gnu99 -pedantic -Wall
breaker:breaker.o
	gcc -o breaker breaker.o
%.o:%.c
	gcc $(CFLAGS) -c $<
.PHONY:clean
clean:
	rm -f breaker *.o *.c~
