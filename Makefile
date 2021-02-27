CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Librarys
LDLIBS = -lcurl

all: main

main: main.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) main.o -o main

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

clean:
	rm *.o main
