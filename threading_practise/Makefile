CC=g++
CFLAGS=-pthread -lboost_thread -g -o0 2>&1
LDFLAGS=-std=c++0x
SOURCES=$(wildcard ./*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=threading_practise

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

clean:
	rm *.o

