CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Librarys
LDLIBS = -lcurl

all: main

main: main.o PageLoader.o Page.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) main.o PageLoader.o Page.o -o main

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

PageLoader.o: ./Crawler/PageLoader/PageLoader.cpp 
	$(CXX) $(CXXFLAGS) -c ./Crawler/PageLoader/PageLoader.cpp -o PageLoader.o

Page.o:
	$(CXX) $(CXXFLAGS) -c ./Crawler/PageLoader/Page.cpp -o Page.o

clean:
	rm *.o main
