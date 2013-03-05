CXX = g++
CXXFLAGS = -Wall -ansi -pedantic
LDFLAGS = -lncurses -lSDL -lSDL_ttf
EXE = blocksfall
EXEWIN = blocksfall.exe
OBJS = main.o pieza.o matriztetris.o contador.o controlTetris.o juegotetris.o piezas_src.o

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(EXE)

clean:
	$(RM) *.o *~ $(EXE)

run:
	./$(EXE)
	
windows: $(EXEWIN)

$(EXEWIN): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(EXEWIN)
