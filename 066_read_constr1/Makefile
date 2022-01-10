CPPFLAGS=-std=gnu99 -pedantic -Werror -Wall -ggdb3
code:code.o
	g++ -o code code.o
%.o:%.cpp
	g++ $(CFLAGS) -c $<
.PHONY:clean
clean:
	rm -f code *.o *.cpp~ 
