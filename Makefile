
all: test

cf := -Werror -Wall $(opt)
lf := $(opt)

header := $(wildcard *.h)
source := $(wildcard *.cpp)
object := $(addprefix $(object),$(source:.cpp=.o))

test : $(object) $(header)
	g++ -o $@ $(lf) $(object)

%o: %cpp
	g++ -c -o $@ $< $(cf)

clean:
	find . -name '*.o' -delete
