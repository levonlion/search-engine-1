CXX = g++
CXXFLAGS = -std=c++17

# Libraries
CURL_LINKER_FLAG				= -lcurl

GUMBO_COMPILER_FLAG 			= -I/usr/local/opt/gumbo-parser/include
GUMBO_LINKER_FLAGS 				= -L/usr/local/opt/gumbo-parser/lib -lgumbo

BOOST_COMPILER_FLAG 			= -I/usr/local/opt/boost/include
BOOST_LINKER_FLAGS 				= -L/usr/local/opt/boost/lib

CPPRESTSDK_COMPILER_FLAG		= -I/usr/local/opt/cpprestsdk/include
CPPRESTSDK_LINKER_FLAG			= -L/usr/local/opt/cpprestsdk/lib -lcpprest

MYSQL_CONNECTOR_COMPILER_FLAG	= -I/usr/local/opt/mysql-connector-c++/include
MYSQL_CONNECTOR_LINKER_FLAGS	= -L/usr/local/opt/mysql-connector-c++/lib -lmysqlcppconn8


ALL_LINKER_FLAGS = ${CURL_LINKER_FLAG} ${GUMBO_LINKER_FLAGS} ${BOOST_LINKER_FLAGS} ${MYSQL_CONNECTOR_LINKER_FLAGS} ${CPPRESTSDK_LINKER_FLAG}

# Names
main = main

all: $(main)

$(main): $(main).o DocumentStore.o Document.o LinkStore.o Link.o PageLoader.o Page.o Parser.o WebsiteStore.o Website.o
	$(CXX) $(CXXFLAGS) ${ALL_LINKER_FLAGS} $(main).o DocumentStore.o Document.o LinkStore.o Link.o PageLoader.o Page.o Parser.o WebsiteStore.o Website.o -o $(main)

$(main).o: $(main).cpp
	$(CXX) $(CXXFLAGS) -c $(main).cpp -o $(main).o

DocumentStore.o: ./DocumentStore/DocumentStore.cpp
	$(CXX) $(CXXFLAGS) ${MYSQL_CONNECTOR_COMPILER_FLAG} -c ./DocumentStore/DocumentStore.cpp -o DocumentStore.o

Document.o: ./DocumentStore/Document.cpp
	$(CXX) $(CXXFLAGS) -c ./DocumentStore/Document.cpp -o Document.o

WebsiteStore.o: ./WebsiteStore/WebsiteStore.cpp
	$(CXX) $(CXXFLAGS) ${MYSQL_CONNECTOR_COMPILER_FLAG} ${BOOST_COMPILER_FLAG} -c ./WebsiteStore/WebsiteStore.cpp -o WebsiteStore.o

Website.o: ./WebsiteStore/Website.cpp
	$(CXX) $(CXXFLAGS) -c ./WebsiteStore/Website.cpp -o Website.o

LinkStore.o: ./LinkStore/LinkStore.cpp
	$(CXX) $(CXXFLAGS) ${MYSQL_CONNECTOR_COMPILER_FLAG} -c ./LinkStore/LinkStore.cpp -o LinkStore.o

Link.o: ./LinkStore/Link.cpp
	$(CXX) $(CXXFLAGS) -c ./LinkStore/Link.cpp -o Link.o

PageLoader.o: ./PageLoader/PageLoader.cpp
	$(CXX) $(CXXFLAGS) -c ./PageLoader/PageLoader.cpp -o PageLoader.o

Page.o: ./PageLoader/Page.cpp
	$(CXX) $(CXXFLAGS) -c ./PageLoader/Page.cpp -o Page.o

Parser.o: ./Parser/Parser.cpp
	$(CXX) $(CXXFLAGS) ${GUMBO_COMPILER_FLAG} ${CPPRESTSDK_COMPILER_FLAG} -c ./Parser/Parser.cpp -o Parser.o

clean:
	rm *.o $(main)
