
CC=g++
CFLAGS=-Wall -Wextra -Werror -std\=c++11 -I ./assl/
LFLAGS=-pthread -ldl

tests := $(wildcard tests/*.cpp)
testsout = $(tests:.cpp=.out)

.SECONDARY:

all: $(testsout)

clean:
	rm -f tests/*.out tests/*.o

tests/%.out: tests/%.o
	$(CC) $(CFLAGS) $^ -o $@

tests/%.o: tests/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^
