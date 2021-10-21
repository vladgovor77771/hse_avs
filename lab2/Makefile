CC := g++
FLAGS := -std=c++17 -Wall -Werror -O2 -pedantic
DEBUG_FLAGS :=  -fsanitize=address -g
SRC := ./src
BIN := ./bin

all: deps
	$(CC) $(FLAGS) -c $(SRC)/main.cpp -o $(BIN)/main.o
	$(CC) $(FLAGS) -o $(BIN)/app.out $(BIN)/main.o $(BIN)/sort.o $(BIN)/io.o $(BIN)/base.o $(BIN)/cc_string.o $(BIN)/ci_string.o $(BIN)/cs_string.o

benchmark: deps
	$(CC) $(FLAGS) -c $(SRC)/benchmark.cpp -o $(BIN)/benchmark.o
	$(CC) $(FLAGS) -o $(BIN)/app_benchmark.out $(BIN)/benchmark.o $(BIN)/sort.o $(BIN)/io.o $(BIN)/base.o $(BIN)/cc_string.o $(BIN)/ci_string.o $(BIN)/cs_string.o

deps: createbindir
	$(CC) $(FLAGS) -c $(SRC)/encoded_string/base.cpp -o $(BIN)/base.o
	$(CC) $(FLAGS) -c $(SRC)/encoded_string/cc_string.cpp -o $(BIN)/cc_string.o
	$(CC) $(FLAGS) -c $(SRC)/encoded_string/ci_string.cpp -o $(BIN)/ci_string.o
	$(CC) $(FLAGS) -c $(SRC)/encoded_string/cs_string.cpp -o $(BIN)/cs_string.o
	$(CC) $(FLAGS) -c $(SRC)/io.cpp -o $(BIN)/io.o
	$(CC) $(FLAGS) -c $(SRC)/sort.cpp -o $(BIN)/sort.o

debug: createbindir debugdeps
	$(CC) $(FLAGS) $(DEBUG_FLAGS) -c $(SRC)/main.cpp -o $(BIN)/main.o
	$(CC) $(FLAGS) $(DEBUG_FLAGS) -o $(BIN)/app.out $(BIN)/main.o $(BIN)/sort.o $(BIN)/io.o $(BIN)/base.o $(BIN)/cc_string.o $(BIN)/ci_string.o $(BIN)/cs_string.o

debugdeps: createbindir
	$(CC) $(FLAGS) $(DEBUG_FLAGS) -c $(SRC)/encoded_string/base.cpp -o $(BIN)/base.o
	$(CC) $(FLAGS) $(DEBUG_FLAGS) -c $(SRC)/encoded_string/cc_string.cpp -o $(BIN)/cc_string.o
	$(CC) $(FLAGS) $(DEBUG_FLAGS) -c $(SRC)/encoded_string/ci_string.cpp -o $(BIN)/ci_string.o
	$(CC) $(FLAGS) $(DEBUG_FLAGS) -c $(SRC)/encoded_string/cs_string.cpp -o $(BIN)/cs_string.o
	$(CC) $(FLAGS) $(DEBUG_FLAGS) -c $(SRC)/io.cpp -o $(BIN)/io.o
	$(CC) $(FLAGS) $(DEBUG_FLAGS) -c $(SRC)/sort.cpp -o $(BIN)/sort.o

createbindir:
	mkdir -p $(BIN)

clean:
	$(RM) $(BIN)/*.o $(BIN)/*.out

test:
	/bin/sh ./run_tests.sh

