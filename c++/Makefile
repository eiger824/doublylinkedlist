CC 			= g++
CXXFLAGS 	= -c -Wall -Wextra -Wpedantic -fPIC --std=c++1z -g
LDFLAGS 	= -Wall -Wextra -Wpedantic -fPIC --std=c++1z -g
LIBFLAGS 	= -shared

LIBNAME 	= libdll-c++
LIBVERSION  = 0.2

all: test lib

test: main.o dll.o
	@echo "Linking objects $^"
	${CC} ${LDFLAGS} $^ -o $@

%.o: %.cpp
	${CC} ${CXXFLAGS} $^ -o $@

lib: ${LIBNAME}.so.${LIBVERSION}

${LIBNAME}.so.${LIBVERSION}: dll.cpp dll.h
	@echo "Building shared lib $@"
	${CC} ${CXXFLAGS} ${LIBFLAGS} $< -o $@
	@rm -f ${LIBNAME}.so
	@echo "Creating simlink to version ${LIBVERSION}"
	@ln -s ${LIBNAME}.so.${LIBVERSION} ${LIBNAME}.so
	@ chmod +x ${LIBNAME}.so.${LIBVERSION}

clean:
	rm -f test *~ *.so*
