CPPFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3
code:code.o
	g++ -o code code.o
%.o:%.cpp
	g++ $(CPPFLAGS) -c $<
.PHONY:clean
clean:
	rm -f code *.o *.cpp~
