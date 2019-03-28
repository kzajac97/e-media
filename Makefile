CXXFLAGS = -pedantic -Wall -std=c++17
BOOSTFLAGS = -I C:/MinGw/include -L C:/MinGw/lib

__START__: emedia.exe
	./emedia.exe

emedia.exe: main.o 
	g++ -o emedia.exe main.o

main.o: main.cpp 	
	g++ -c ${CXXFLAGS} main.cpp

clean:
	rm -f *.o *.exe