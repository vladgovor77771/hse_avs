CC := g++
FLAGS := -std=c++17 -Wall -Werror -O2 -pedantic -pthread
DEBUG_FLAGS :=  -fsanitize=address -g
SRC := ./src
BIN := ./bin

all: createbindir
	$(CC) $(FLAGS) -c $(SRC)/client.cpp -o $(BIN)/client.o
	$(CC) $(FLAGS) -c $(SRC)/seller.cpp -o $(BIN)/seller.o
	$(CC) $(FLAGS) -c $(SRC)/market.cpp -o $(BIN)/market.o
	$(CC) $(FLAGS) -c $(SRC)/main.cpp -o $(BIN)/main.o
	$(CC) $(FLAGS) -c $(SRC)/log.cpp -o $(BIN)/log.o
	$(CC) $(FLAGS) -o $(BIN)/app.out $(BIN)/log.o $(BIN)/market.o $(BIN)/main.o $(BIN)/seller.o $(BIN)/client.o

debug: createbindir
	$(CC) $(FLAGS) $(DEBUG_FLAGS) -c $(SRC)/client.cpp -o $(BIN)/client.o
	$(CC) $(FLAGS) $(DEBUG_FLAGS) -c $(SRC)/seller.cpp -o $(BIN)/seller.o
	$(CC) $(FLAGS) $(DEBUG_FLAGS) -c $(SRC)/market.cpp -o $(BIN)/market.o
	$(CC) $(FLAGS) $(DEBUG_FLAGS) -c $(SRC)/main.cpp -o $(BIN)/main.o
	$(CC) $(FLAGS) $(DEBUG_FLAGS) -c $(SRC)/log.cpp -o $(BIN)/log.o
	$(CC) $(FLAGS) $(DEBUG_FLAGS) -o $(BIN)/app.out $(BIN)/log.o $(BIN)/market.o $(BIN)/main.o $(BIN)/seller.o $(BIN)/client.o

createbindir:
	mkdir -p $(BIN)

clean:
	$(RM) $(BIN)/*.o $(BIN)/*.out

test:
	/bin/sh ./run_tests.sh

