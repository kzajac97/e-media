CXXFLAGS = -pedantic -Wall -std=c++17
BOOSTFLAGS = -I C:/MinGw/include -L C:/MinGw/lib

__START__: Bin/emedia.exe
	./Bin/emedia.exe

Bin/emedia.exe: Bin/main.o Bin/rsa.o Bin/reader.o Bin/menu.o
	g++ -o Bin/emedia.exe Bin/main.o Bin/rsa.o Bin/reader.o Bin/menu.o

Bin/main.o: Src/main.cpp 	
	g++ -c -o Bin/main.o ${CXXFLAGS} ${BOOSTFLAGS} Src/main.cpp

Bin/rsa.o: Src/rsa.cpp Src/rsa.hpp
	g++ -c -o Bin/rsa.o ${CXXFLAGS} ${BOOSTFLAGS} Src/rsa.cpp -lpthread

Bin/reader.o: Src/reader.cpp Src/reader.hpp
	g++ -c -o Bin/reader.o ${CXXFLAGS} ${BOOSTFLAGS} Src/reader.cpp

Bin/menu.o: Src/menu.cpp Src/menu.hpp
	g++ -c -o Bin/menu.o ${CXXFLAGS} ${BOOSTFLAGS} Src/menu.cpp

clean:
	rm Bin/*