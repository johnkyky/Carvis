CC = g++
CFLAGS = -Wall -g
SFFLAGS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio
EXE = Carvis

SRCDIR = src/
OBJDIR = obj/
BINDIR = bin/

OBJ = $(OBJDIR)main.o $(OBJDIR)Car.o $(OBJDIR)Circuit.o $(OBJDIR)Ray.o $(OBJDIR)Wall.o \
	  $(OBJDIR)NeuralNetwork.o $(OBJDIR)Fonction.o $(OBJDIR)Matrix.o


all: $(OBJ)
	$(CC) -o $(BINDIR)$(EXE) $(CFLAGS) $(SFFLAGS) $^
	./bin/$(EXE)


$(OBJDIR)main.o: $(SRCDIR)main.cpp $(OBJDIR)Car.o $(OBJDIR)Circuit.o $(OBJDIR)NeuralNetwork.o $(OBJDIR)Matrix.o
	$(CC) -c -o $@ $(CFLAGS) $(SFFLAGS) $<

$(OBJDIR)Car.o: $(SRCDIR)Car.cpp $(SRCDIR)Car.hpp $(OBJDIR)Circuit.o $(OBJDIR)Ray.o $(OBJDIR)NeuralNetwork.o $(OBJDIR)Matrix.o
	$(CC) -c -o $@ $(CFLAGS) $(SFFLAGS) $<

$(OBJDIR)Circuit.o: $(SRCDIR)Circuit.cpp $(SRCDIR)Circuit.hpp $(OBJDIR)Wall.o $(OBJDIR)Fonction.o
	$(CC) -c -o $@ $(CFLAGS) $(SFFLAGS) $<

$(OBJDIR)Ray.o: $(SRCDIR)Ray.cpp $(SRCDIR)Ray.hpp $(OBJDIR)Circuit.o $(OBJDIR)Fonction.o
	$(CC) -c -o $@ $(CFLAGS) $(SFFLAGS) $<

$(OBJDIR)Wall.o: $(SRCDIR)Wall.cpp $(SRCDIR)Wall.hpp
	$(CC) -c -o $@ $(CFLAGS) $(SFFLAGS) $<

$(OBJDIR)Fonction.o: $(SRCDIR)Fonction.cpp $(SRCDIR)Fonction.hpp
	$(CC) -c -o $@ $(CFLAGS) $(SFFLAGS) $<

$(OBJDIR)NeuralNetwork.o: $(SRCDIR)NeuralNetwork.cpp $(SRCDIR)NeuralNetwork.hpp
	$(CC) -c -o $@ $(CFLAGS) $(SFFLAGS) $<

$(OBJDIR)Matrix.o: $(SRCDIR)Matrix.cpp $(SRCDIR)Matrix.hpp
	$(CC) -c -o $@ $(CFLAGS) $(SFFLAGS) $<


clean:
	rm $(OBJDIR)*.o
	rm $(BINDIR)Carvis