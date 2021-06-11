CC=g++
CFLAGS=-c
LDFLAGS=
SOURCES=main.cpp Logger.cpp LoggerCreator.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Logger

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o Logger