myProgram: power.o test-power.o
	gcc -o myProgram power.o test-power.o
test-power.o: test-power.c
	gcc -c test-power.c
power.o: power.c
	gcc -c power.c

.PHONY: clean
clean:
	rm -f myProgram *.o *.c~ 
