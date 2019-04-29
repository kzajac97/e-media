CXXFLAGS = -pedantic -Wall -std=c++1z
BOOSTFLAGS = -I C:/MinGw/include -L C:/MinGw/lib

__START__: emedia.exe
	./emedia.exe

emedia.exe: main.o rsa.o reader.o
	g++ -o emedia.exe main.o rsa.o reader.o

main.o: main.cpp 	
	g++ -c ${CXXFLAGS} ${BOOSTFLAGS} main.cpp

rsa.o: rsa.cpp rsa.hpp
	g++ -c ${CXXFLAGS} ${BOOSTFLAGS} rsa.cpp -lpthread

reader.o: reader.cpp reader.hpp
	g++ -c ${CXXFLAGS} ${BOOSTFLAGS} reader.cpp

clean:
	rm -f *.o *.exe