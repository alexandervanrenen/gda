
all: gda_lib

cf := -Werror -Wall -funroll-loops -O2 -Iinclude/gda
lf := -funroll-loop -O2

source := src/time.cpp src/string.cpp src/math.cpp src/server.cpp src/client.cpp
object := $(source:.cpp=.o)

gda_lib: $(object)
	mv src/*.o .
	ar -rv libgda.a *.o
	rm *.o

%o: %cpp
	g++ -c -o $@ $< $(cf)

clean:
	find . -name '*.o' -delete -o -name 'gda.a' -delete
