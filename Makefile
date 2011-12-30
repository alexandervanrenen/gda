
all: libgda

gtest_include := ../gtest/include
gtest_dir := ../gtest

cf := -Werror -Wall -O2 -funroll-all-loops -ffast-math -g0 -Iinclude $(addprefix -I,$(gtest_include)) $(addprefix -I,$(gtest_dir)) $(opt)
lf := -funroll-loop -O2 -ffast-math -g0 $(addprefix -I,$(gtest_include)) $(addprefix -I,$(gtest_dir)) -pthread $(opt)

source := src/time.cpp src/string.cpp src/math.cpp src/server.cpp src/client.cpp
object := $(source:.cpp=.o)

libgda: $(object)
	mv src/*.o .
	ar -rv libgda.a *.o
	rm *.o

test_source := $(source) test/main.cpp test/test_string.cpp test/test_fasthash.cpp
test_object := $(test_source:.cpp=.o)

tester: $(test_object)
	g++ -o tester $(test_object) $(addprefix $(gtest_dir),/gtest_lib.o) $(lf)

%o: %cpp
	g++ -c -o $@ $< $(cf)


clean:
	find . -name '*.o' -delete -o -name 'libgda.a' -delete -o -name 'tester' -delete
