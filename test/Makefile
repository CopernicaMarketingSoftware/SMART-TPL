COMPILER_FLAGS    = -Wall -g -O0 -pipe -std=c++11 -Wno-sign-compare
LINKER_FLAGS      =
INC               = -I../ -I. -Igtest-1.7.0/include
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
	wget -q https://googletest.googlecode.com/files/gtest-1.7.0.zip
	unzip -qq gtest-1.7.0.zip
	${COMPILER} ${COMPILER_FLAGS} -I gtest-1.7.0/include -I gtest-1.7.0 -c gtest-1.7.0/src/gtest-all.cc
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
