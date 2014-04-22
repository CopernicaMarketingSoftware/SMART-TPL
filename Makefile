#
#   SMART-TPL Makefile
#
#   This makefile has a user friendly order: the top part of this file contains 
#   all variable settings that you may alter to suit your own system, while at
#   the bottom you will find instructions for the compiler in which you will
#   probably not have to make any changes
#   

#
#   Installation directory
#
#   When you install the SMART-TPL library, it will place a number of C++ *.h 
#   header files in your system include directory, and a smarttpl.so shared
#   library file in your system libraries directory. Most users set this to
#   the regular /usr/include and /usr/lib directories, or /usr/local/include
#   and /usr/local/lib. You can of course change it to whatever suits you best
#   

INSTALL_PREFIX  =   /usr
INSTALL_HEADERS =   ${INSTALL_PREFIX}/include
INSTALL_LIB     =   ${INSTALL_PREFIX}/lib
INSTALL_BIN     =   ${INSTALL_PREFIX}/bin


#
#   Name of the target library and target program
#
#   The SMART-TPL library will be installed on your system as libsmarttpl.so.
#   This is a brilliant name. If you want to use a different name for it,
#   you can change that here. The SMART-TPL command line compiler will be 
#   named 'smarttpl'
#

LIBRARY         =   libsmarttpl.so
PROGRAM         =   smarttpl


#
#   Compiler and other programs
#
#   By default, the GNU C++ compiler is used. If you want to use a different
#   compiler, you can change that here. You can change this for both the 
#   compiler (the program that turns the c++ files into object files) and for
#   the linker (the program that links all object files into a single .so
#   library file. By default, g++ (the GNU C++ compiler) is used for both.
#
#   For generating the tokenizer and the parser, the external programs "flex"
#   and "lemon" are being used. You may override them here
#

COMPILER        =   clang
LINKER          =   g++
FLEX            =   flex
LEMON           =   lemon

#
#   Additions flags
#
#   This variable holds the flags that are passed to the compiler/linker and
#   other programs. By default, we include the -O2 flag. This flag tells the 
#   compiler to optimize the code, but it makes debugging more difficult. So if 
#   you're debugging your application, you probably want to remove this -O2 
#   flag. At the same time, you can then add the -g flag to instruct the 
#   compiler to include debug information in the library (but this will make the
#   final libphpcpp.so file much bigger, so you want to leave that flag out on 
#   production servers).
#
#   Are you compiling on OSX? You may have to append the option 
#   "-undefined dynamic_lookup" to the linker flags
#

COMPILER_FLAGS  =   -Wall -c -I. -O0 -g -fpic -std=c++11
LINKER_FLAGS    =   -L.
DEPENDENCIES    =   -ljitplus -ljit -ldl
FLEX_FLAGS      =   
LEMON_FLAGS     =   


#
#   Command to remove files, copy files and create directories.
#
#   I've never encountered a *nix environment in which these commands do not work. 
#   So you can probably leave this as it is
#

RM              =   rm -f
CP              =   cp -f
MKDIR           =   mkdir -p
MV              =   mv -f


#   
#   The tokenizer input file
#
#   The Tokenizer.yy file should be fed to the "flex" program
#

TOKENIZER       =    src/tokenizer.cpp


#
#    The lemon input file

#    The Parser.lemon file is processed by the "lemon" program
#

PARSER          =    src/parser.cpp


#
#   The source files
#
#   For this we use a special Makefile function that automatically scans the
#   src/ directory for all *.cpp files. No changes are probably necessary here
#

LIBRARY_SOURCES =   $(wildcard src/*.cpp) ${TOKENIZER} ${PARSER}
PROGRAM_SOURCES =   $(wildcard program/*.cpp)

#
#   The object files
#
#   The intermediate object files are generated by the compiler right before
#   the linker turns all these object files into the libphpcpp.so shared library.
#   We also use a Makefile function here that takes all source files.
#

LIBRARY_OBJECTS =   $(sort $(LIBRARY_SOURCES:%.cpp=%.o))
PROGRAM_OBJECTS =   $(sort $(PROGRAM_SOURCES:%.cpp=%.o))

#
#   Auto-generated files
#
#   Some of the source files are not part of the project, but are generated
#   on fly by programs like 'flex' and 'lemon'. For 'make clean' we need an
#   explicit list of the generated files.
#

GENERATED       =   ${TOKENIZER} ${PARSER} ${PARSER:%.cpp=%.h} ${PARSER:%.cpp=%.out}


#
#   End of the variables section. Here starts the list of instructions and
#   dependencies that are used by the compiler.
#

all: ${LIBRARY} ${PROGRAM}

${LIBRARY}: ${PARSER} ${TOKENIZER} ${LIBRARY_OBJECTS}
	${LINKER} ${LINKER_FLAGS} -shared -o $@ ${LIBRARY_OBJECTS} ${DEPENDENCIES}

${PROGRAM}: ${PROGRAM_OBJECTS}
	${LINKER} ${LINKER_FLAGS} -o $@ ${PROGRAM_OBJECTS} -lsmarttpl

clean:
	${RM} ${GENERATED} ${LIBRARY_OBJECTS} ${PROGRAM_OBJECTS} ${LIBRARY} ${PROGRAM}

${TOKENIZER}:
	${FLEX} ${FLEX_FLAGS} ${@:%.cpp=%.flex}

${PARSER}:
	${LEMON} ${LEMON_FLAGS} ${@:%.cpp=%.lemon}
	${MV} ${PARSER:%.cpp=%.c} $@

.cpp.o: 
	${COMPILER} ${COMPILER_FLAGS} -o $@ ${@:%.o=%.cpp}

.c.o: 
	${COMPILER} ${COMPILER_FLAGS} -o $@ ${@:%.o=%.c}

install:
	${MKDIR} ${INSTALL_HEADERS}/smarttpl
	${CP} smarttpl.h ${INSTALL_HEADERS}
	${CP} include/*.h ${INSTALL_HEADERS}/smarttpl
	${CP} ${LIBRARY} ${INSTALL_LIB}
	${CP} ${PROGRAM} ${INSTALL_BIN}

