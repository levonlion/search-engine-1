CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Libraries
LDLIBS = -I/usr/local/Cellar/gumbo-parser/0.10.1/include -L/usr/local/Cellar/gumbo-parser/0.10.1/lib -lgumbo

#names
main = test
# firstFile = Parser
# secondFile = Page

all: $(main)
# $(firstFile).o $(secondFile).o
$(main): $(main).o 
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(main).o -o $(main)

$(main).o: $(main).cpp
	$(CXX) $(CXXFLAGS) -c $(main).cpp -o $(main).o

# $(firstFile).o: $(firstFile).cpp
# 	$(CXX) $(CXXFLAGS) -c $(firstFile).cpp -o $(firstFile).o

# $(secondFile).o: $(secondFile).cpp
# 	$(CXX) $(CXXFLAGS) -c $(secondFile).cpp -o $(secondFile).o

clean:
	rm *.o $(main)
