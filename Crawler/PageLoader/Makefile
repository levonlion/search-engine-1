CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Libraries
LDLIBS = -lcurl

#names
main = test
firstFile = PageLoader
secondFile = Page

all: $(main)

$(main): $(main).o $(firstFile).o $(secondFile).o
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(main).o $(firstFile).o $(secondFile).o -o $(main)

$(main).o: $(main).cpp
	$(CXX) $(CXXFLAGS) -c $(main).cpp -o $(main).o

$(firstFile).o: $(firstFile).cpp
	$(CXX) $(CXXFLAGS) -c $(firstFile).cpp -o $(firstFile).o

$(secondFile).o: $(secondFile).cpp
	$(CXX) $(CXXFLAGS) -c $(secondFile).cpp -o $(secondFile).o

clean:
	rm *.o $(main)
