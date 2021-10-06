CC := g++
FLAGS := -std=c++17 -Wall -Werror -O2 -pedantic -fsanitize=address -g
SRC := ./src
BIN := ./bin

all: deps
	$(CC) $(FLAGS) -c $(SRC)/main.cpp -o $(BIN)/main.o
	$(CC) $(FLAGS) -o $(BIN)/app.out $(BIN)/main.o $(BIN)/sort.o $(BIN)/io.o $(BIN)/encoded_string.o 

deps:
	$(CC) $(FLAGS) -c $(SRC)/encoded_string.cpp -o $(BIN)/encoded_string.o
	$(CC) $(FLAGS) -c $(SRC)/io.cpp -o $(BIN)/io.o
	$(CC) $(FLAGS) -c $(SRC)/sort.cpp -o $(BIN)/sort.o

clean:
	cd ./bin && $(RM) *.o *.out

