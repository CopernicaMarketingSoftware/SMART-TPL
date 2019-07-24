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
#   SONAME and version
#
#   When ABI changes, soname and minor version of the library should be raised.
#   Otherwise only release verions changes. (version is MAJOR.MINOR.RELEASE)
#

SONAME					=	1.4
VERSION					=	1.4.0

#
#   Name of the target library and target program
#
#   The SMART-TPL library will be installed on your system as libsmarttpl.so.
#   This is a brilliant name. If you want to use a different name for it,
#   you can change that here. The SMART-TPL command line compiler will be
#   named 'smarttpl'
#

SHARED_LIBRARY  =   libsmarttpl.so
STATIC_LIBRARY  =   libsmarttpl.a
PROGRAM         =   smarttpl

#
#   Compiler and other programs
#
#   By default, c++ is used. Meaning your default C++ compiler is used.
#
#   For generating the tokenizer and the parser, the external programs "flex"
#   and "lemon" are being used. You may override them here
#

COMPILER        =   g++
LINKER          =   g++
FLEX            =   flex
LEMON           =   lemon
ARCHIVER        =   ar rcs

#
#   Additions flags
#
#   This variable holds the flags that are passed to the compiler/linker and
#   other programs. By default, we include the -O2 flag. This flag tells the
#   compiler to optimize the code, but it makes debugging more difficult. So if
#   you're debugging your application, you probably want to remove this -O2
#   flag. At the same time, you can then add the -g flag to instruct the
#   compiler to include debug information in the library (but this will make the
#   final libsmarttpl.so file much bigger, so you want to leave that flag out on
#   production servers).
#

COMPILER_FLAGS        = -Wall -c -I. -O2 -MD -pipe -std=c++11 -Wno-sign-compare -Wno-psabi
SHARED_COMPILER_FLAGS = -fPIC
STATIC_COMPILER_FLAGS =
LINKER_FLAGS          = -L.
LIBRARIES             = -ljitplus -ljit -ldl -lboost_regex -ltimelib
FLEX_FLAGS            =
LEMON_FLAGS           =

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
LN              =   ln -fs

#
#   The tokenizer output file
#

TOKENIZERS      =    src/tokenizer_v1.cpp src/tokenizer_v2.cpp

#
#    The lemon output file
#

PARSER          =    src/parser.cpp

#
#   The source files
#
#   For this we use a special Makefile function that automatically scans the
#   src/ directory for all *.cpp files. No changes are probably necessary here
#

LIBRARY_SOURCES =   $(wildcard src/*.cpp) ${TOKENIZERS} ${PARSER}
PROGRAM_SOURCES =   $(wildcard program/*.cpp)

#
#   The object files
#
#   The intermediate object files are generated by the compiler right before
#   the linker turns all these object files into the libsmarttpl.so shared library.
#   We also use a Makefile function here that takes all source files.
#

SHARED_LIBRARY_OBJECTS = $(sort $(LIBRARY_SOURCES:%.cpp=%.o))
STATIC_LIBRARY_OBJECTS = $(sort $(LIBRARY_SOURCES:%.cpp=%.s.o))
PROGRAM_OBJECTS        = $(sort $(PROGRAM_SOURCES:%.cpp=%.o))

#
#	Dependency (*.d) files
#

DEPENDENCIES = $(LIBRARY_SOURCES:%.cpp=%.d) $(PROGRAM_SOURCES:%.cpp=%.d)

#
#   Auto-generated files
#
#   Some of the source files are not part of the project, but are generated
#   on fly by programs like 'flex' and 'lemon'. For 'make clean' we need an
#   explicit list of the generated files.
#

GENERATED       =   ${TOKENIZERS} ${PARSER} ${PARSER:%.cpp=%.h} ${PARSER:%.cpp=%.out}

#
#   End of the variables section. Here starts the list of instructions and
#   dependencies that are used by the compiler.
#

all: ${SHARED_LIBRARY} ${STATIC_LIBRARY} ${PROGRAM}

-include ${DEPENDENCIES}

${SHARED_LIBRARY}: ${PARSER} ${TOKENIZERS} ${SHARED_LIBRARY_OBJECTS}
	${LINKER} ${LINKER_FLAGS} -Wl,-soname,libsmarttpl.so.${SONAME} -shared -o $@ ${SHARED_LIBRARY_OBJECTS} ${LIBRARIES}

${STATIC_LIBRARY}: ${PARSER} ${TOKENIZERS} ${STATIC_LIBRARY_OBJECTS}
	${ARCHIVER} ${STATIC_LIBRARY} ${STATIC_LIBRARY_OBJECTS}

${PROGRAM}: ${PROGRAM_OBJECTS} ${SHARED_LIBRARY} 
	${LINKER} ${LINKER_FLAGS} -o $@ ${PROGRAM_OBJECTS} -lsmarttpl -ltimelib

clean:
	${RM} ${GENERATED} ${SHARED_LIBRARY_OBJECTS} ${STATIC_LIBRARY_OBJECTS} ${PROGRAM_OBJECTS} ${LIBRARY} ${PROGRAM}

${TOKENIZERS}: ${TOKENIZERS:%.cpp=%.flex}
	${FLEX} ${FLEX_FLAGS} ${@:%.cpp=%.flex}

${PARSER}: ${PARSER:%.cpp=%.lemon}
	${LEMON} ${LEMON_FLAGS} ${@:%.cpp=%.lemon}
	${MV} ${@:%.cpp=%.c} $@

${SHARED_LIBRARY_OBJECTS}: ${@:%.o=%.cpp}
	${COMPILER} ${COMPILER_FLAGS} ${SHARED_COMPILER_FLAGS} -o $@ ${@:%.o=%.cpp}

${PROGRAM_OBJECTS}: ${@:%.o=%.cpp}
	${COMPILER} ${COMPILER_FLAGS} -o $@ ${@:%.o=%.cpp}

${STATIC_LIBRARY_OBJECTS}: ${@:%.s.o=%.cpp}
	${COMPILER} ${COMPILER_FLAGS} ${STATIC_COMPILER_FLAGS} -o $@ ${@:%.s.o=%.cpp}

install:
	${MKDIR} ${INSTALL_HEADERS}/smarttpl
	${CP} smarttpl.h ${INSTALL_HEADERS}
	${CP} include/*.h ${INSTALL_HEADERS}/smarttpl
	${CP} ${SHARED_LIBRARY} ${INSTALL_LIB}/${SHARED_LIBRARY}.${VERSION}
	${LN} ${INSTALL_LIB}/${SHARED_LIBRARY}.${VERSION} ${INSTALL_LIB}/${SHARED_LIBRARY}.${SONAME}
	${LN} ${INSTALL_LIB}/${SHARED_LIBRARY}.${VERSION} ${INSTALL_LIB}/${SHARED_LIBRARY}
	${CP} ${STATIC_LIBRARY} ${INSTALL_LIB}/${STATIC_LIBRARY}.${VERSION}
	${LN} ${INSTALL_LIB}/${STATIC_LIBRARY}.${VERSION} ${INSTALL_LIB}/${STATIC_LIBRARY}.${SONAME}
	${LN} ${INSTALL_LIB}/${STATIC_LIBRARY}.${VERSION} ${INSTALL_LIB}/${STATIC_LIBRARY}
	${CP} ${PROGRAM} ${INSTALL_BIN}
	if `which ldconfig`; then \
		ldconfig; \
	fi
