CC = g++
LIBS = -lGL -lglut -lGLU -lm 

SRC = cuboid.cpp
BIN = cuboid

all	:	$(BIN)

$(BIN)	:	$(SRC)
	$(CC) $(SRC) -g -o $(BIN) $(LIBS) 

clean	:
	rm -f $(BIN) *~ *.aux *.log
