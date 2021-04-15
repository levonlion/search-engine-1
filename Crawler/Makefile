CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Libraries
LDLIBS = -lcurl -I/usr/local/Cellar/gumbo-parser/0.10.1/include -L/usr/local/Cellar/gumbo-parser/0.10.1/lib -lgumbo

# Names
main = main

all: $(main)

$(main): $(main).o DocumentStore.o Document.o LinkStore.o Link.o PageLoader.o Page.o Parser.o WebsiteStore.o Website.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) $(main).o DocumentStore.o Document.o LinkStore.o Link.o PageLoader.o Page.o Parser.o WebsiteStore.o Website.o -o $(main)

$(main).o: $(main).cpp
	$(CXX) $(CXXFLAGS) -c $(main).cpp -o $(main).o

DocumentStore.o: ./DocumentStore/DocumentStore.cpp
	$(CXX) $(CXXFLAGS) -c ./DocumentStore/DocumentStore.cpp -o DocumentStore.o

Document.o: ./DocumentStore/Document.cpp
	$(CXX) $(CXXFLAGS) -c ./DocumentStore/Document.cpp -o Document.o

LinkStore.o: ./LinkStore/LinkStore.cpp
	$(CXX) $(CXXFLAGS) -c ./LinkStore/LinkStore.cpp -o LinkStore.o

Link.o: ./LinkStore/Link.cpp
	$(CXX) $(CXXFLAGS) -c ./LinkStore/Link.cpp -o Link.o

PageLoader.o: ./PageLoader/PageLoader.cpp
	$(CXX) $(CXXFLAGS) -c ./PageLoader/PageLoader.cpp -o PageLoader.o

Page.o: ./PageLoader/Page.cpp
	$(CXX) $(CXXFLAGS) -c ./PageLoader/Page.cpp -o Page.o

Parser.o: ./Parser/Parser.cpp
	$(CXX) $(CXXFLAGS) -c ./Parser/Parser.cpp -o Parser.o

WebsiteStore.o: ./WebsiteStore/WebsiteStore.cpp
	$(CXX) $(CXXFLAGS) -c ./WebsiteStore/WebsiteStore.cpp -o WebsiteStore.o

Website.o: ./WebsiteStore/Website.cpp
	$(CXX) $(CXXFLAGS) -c ./WebsiteStore/Website.cpp -o Website.o

clean:
	rm *.o $(main)
