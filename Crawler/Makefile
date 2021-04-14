CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Libraries
LDLIBS = -lcurl -I/usr/local/Cellar/gumbo-parser/0.10.1/include -L/usr/local/Cellar/gumbo-parser/0.10.1/lib -lgumbo

# Names
main = test

all: $(main)

$(main): $(main).o PageLoader.o Page.o Parser.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(main).o PageLoader.o Page.o Parser.o -o $(main)

$(main).o: $(main).cpp
	$(CXX) $(CXXFLAGS) -c $(main).cpp -o $(main).o

PageLoader.o: ./PageLoader/PageLoader.cpp
	$(CXX) $(CXXFLAGS) -c ./PageLoader/PageLoader.cpp -o PageLoader.o

Page.o: ./PageLoader/Page.cpp
	$(CXX) $(CXXFLAGS) -c ./PageLoader/Page.cpp -o Page.o

Parser.o: ./Parser/Parser.cpp
	$(CXX) $(CXXFLAGS) -c ./Parser/Parser.cpp -o Parser.o

clean:
	rm *.o $(main)
