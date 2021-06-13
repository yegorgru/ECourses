CC=g++
CFLAGS=-c
LDFLAGS=
SOURCES=main.cpp FileWrapper.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=FileWrapper

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o FileWrapper