
all: gda_lib
cf := -Werror -Wall $(opt)
lf := $(opt)

header := gda_time.hpp gda_string.hpp gda_math.hpp gda_server.hpp gda_client.hpp
source := $(header:.hpp=.cpp)
object := $(header:.hpp=.o)

gda_lib: $(object)
	ar q gda.a *.o

%o: %cpp
	g++ -c -o $@ $< $(cf)

clean:
	find . -name '*.o' -delete -o -name 'gda.a' -delete
