CC=g++
CFLAGS=-c -DLINUX -I. -LSDL/lib -std=c++11
LDFLAGS=-lSDL -lSDL_gfx
SOURCES=Main.cpp Game.cpp Board.cpp IO.cpp Pieces.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tetris

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS) $(EXECUTABLE)
