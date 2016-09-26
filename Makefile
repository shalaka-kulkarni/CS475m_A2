CC = g++
LIBS = -lGL -lglut -lGLU -lm 

SRC = frame_revised.cpp
BIN = frame

all	:	$(BIN)

$(BIN)	:	$(SRC)
	$(CC) $(SRC) -o $(BIN) $(LIBS)

clean	:
	rm -f $(BIN) *~
