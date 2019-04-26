CXX=g++
EXEC=main
FLAG =-std=c++11 -O3

MAIN_SRC=src/main.cpp
PUZZLE_STATE_SRC=src/PuzzleState.cpp
SEARCH_SRC=src/searchAlgorithms.cpp
SOLUTION_SRC=src/Solution.cpp
TEST_SRC=src/test.cpp
OPEN_SRC=src/OpenList.cpp

MAIN_O =obj/main.o
PUZZLE_STATE_O=obj/PuzzleState.o 
SEARCH_O=obj/searchAlgorithms.o
SOLUTION_O=obj/Solution.o
TEST_O=obj/test.o
OPEN_O=obj/OpenList.o

all: gen_bin

gen_obj:
	$(CXX) $(FLAG) -c $(MAIN_SRC) $(PUZZLE_STATE_SRC) $(SEARCH_SRC) $(SOLUTION_SRC) $(TEST_SRC) $(OPEN_SRC)
	mv *.o obj

gen_bin: gen_obj
	$(CXX) $(FLAG) -o $(EXEC) $(MAIN_O) $(PUZZLE_STATE_O) $(SEARCH_O) $(SOLUTION_O) $(TEST_O) $(OPEN_O)

clean:
	rm -rf obj/*
	rm -rf $(EXEC)
