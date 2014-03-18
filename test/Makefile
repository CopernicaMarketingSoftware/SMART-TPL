#
# Makefile template
#

#
# Compiler and linker
#

COMPILER = g++
LINKER = g++
COMPILER_FLAGS = -Wall -c -O2 -std=c++11 -fpic -o
LINKER_DEPENDENCIES = -lsmarttpl
LINKER_FLAGS = 

#
# Command to remove files, copy files and create directories.
#

RM = rm -f
CP = cp -f
MKDIR = mkdir -p

#
# All source files are simply all *.cpp files found in the current directory
#

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)

#
# Result file
#

RESULT = a.out

#
# From here the build instructions start
#

all: ${OBJECTS} ${RESULT}

${RESULT}: ${OBJECTS}
	${LINKER} ${LINKER_FLAGS} -o $@ ${OBJECTS} ${LINKER_DEPENDENCIES}

${OBJECTS}:
	${COMPILER} ${COMPILER_FLAGS} $@ ${@:%.o=%.cpp}

clean:
	${RM} ${RESULT} ${OBJECTS}

