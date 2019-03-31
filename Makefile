CXXFLAGS = -pedantic -Wall -std=c++1z
BOOSTFLAGS = -I C:/MinGw/include -L C:/MinGw/lib

__START__: emedia.exe
	./emedia.exe

emedia.exe: main.o rsa.o
	g++ -o emedia.exe main.o rsa.o

main.o: main.cpp 	
	g++ -c ${CXXFLAGS} main.cpp

rsa.o: rsa.cpp rsa.hpp
	g++ -c ${CXXFLAGS} rsa.cpp

clean:
	rm -f *.o *.exe