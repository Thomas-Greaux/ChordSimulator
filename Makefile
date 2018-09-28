COMPIL=g++
FLAGS=--std=c++11 -Wall
OBJ=main.o ChordNode.o
PROG=Chord

all: $(PROG)

$(PROG): $(OBJ)
	$(COMPIL) $(FLAGS) -o $@ $^

%.o: %.cpp
	$(COMPIL) $(FLAGS) -c -o $@ $^

clean:
	rm -f $(OBJ)
	rm -f $(PROG)
