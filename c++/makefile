all: test lib

test: main.o dll.o
	@echo "Linking objects $^"
	g++ -Wall -Wextra -Wpedantic -fPIC --std=c++1z $^ -o $@

main.o: main.cpp
	g++ -c -Wall -Wextra -Wpedantic -g -fPIC --std=c++1z $^ -o $@

dll.o: dll.cpp dll.h
	g++ -c -Wall -Wextra -Wpedantic -g -fPIC --std=c++1z $< -o $@

lib: libdll.so.0.1

libdll.so.0.1: dll.cpp dll.h
	@echo "Building shared lib $@"
	g++ -c -shared -Wextra -Wpedantic -g --std=c++1z $< -o $@
	@rm -f libdll.so
	@echo "Creating simlink to version 0.1"
	@ln -s libdll.so.0.1 libdll.so
	@ chmod +x libdll.so.0.1

clean:
	rm -f test *.o *~ libdll*
