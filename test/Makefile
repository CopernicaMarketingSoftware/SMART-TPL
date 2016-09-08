COMPILER_FLAGS    = -Wall -g -O0 -pipe -std=c++11 -Wno-sign-compare
LINKER_FLAGS      =
INC               = -I../ -I. -Igoogletest-release-1.8.0/googletest/include
COMPILER          = c++
LINKER            = c++

VALGRIND          = valgrind
VALGRIND_OPTS     =

BINARY            = test.out
DEPS              = $(patsubst %.cpp, %.o, $(shell find . -name \*.cpp -type f))

all: ${BINARY}

%.o: %.cpp libgtest.a
	${COMPILER} ${COMPILER_FLAGS} ${INC} -c $< -o $@

${BINARY}: ${DEPS} main.cpp
	${LINKER} ${LINKER_FLAGS} ${INC} -o ${BINARY} ${DEPS} libgtest.a -pthread ../libsmarttpl.so

libgtest.a:
	wget -q https://github.com/google/googletest/archive/release-1.8.0.tar.gz
	tar -xf release-1.8.0.tar.gz
	${COMPILER} ${COMPILER_FLAGS} -I googletest-release-1.8.0/googletest/include -I googletest-release-1.8.0/googletest -c googletest-release-1.8.0/googletest/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o

.PHONY: test

test: ${BINARY}
	./${BINARY}

.PHONY: valgrind

valgrind: ${BINARY}
	${VALGRIND} ${VALGRIND_OPTS} ./${BINARY}

.PHONY: clean

clean:
	rm -rf ${BINARY} ${DEPS}
