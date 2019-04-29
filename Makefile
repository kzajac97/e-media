CXXFLAGS = -pedantic -Wall -std=c++17
BOOSTFLAGS = -I C:/MinGw/include -L C:/MinGw/lib

__START__: emedia.exe
	./emedia.exe

emedia.exe: main.o rsa.o reader.o menu.o
	g++ -o emedia.exe main.o rsa.o reader.o menu.o

main.o: main.cpp 	
	g++ -c ${CXXFLAGS} ${BOOSTFLAGS} main.cpp

rsa.o: rsa.cpp rsa.hpp
	g++ -c ${CXXFLAGS} ${BOOSTFLAGS} rsa.cpp -lpthread

reader.o: reader.cpp reader.hpp
	g++ -c ${CXXFLAGS} ${BOOSTFLAGS} reader.cpp

menu.o: menu.cpp menu.hpp
	g++ -c ${CXXFLAGS} ${BOOSTFLAGS} menu.cpp

clean:
	rm -f *.o *.exe