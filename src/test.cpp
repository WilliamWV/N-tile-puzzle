/**
	This file contains tests of the algorithms
*/

#include "../include/test.h"


std::vector<std::vector<int>> puzzle3x3_1 {
        {8, 3, 5},
        {7, 2, 6},
        {0, 4, 1}
};
std::vector<std::vector<int>> puzzle3x3_2 {
        {3, 0, 8},
        {7, 5, 2},
        {1, 6, 4}
};
std::vector<std::vector<int>> puzzle3x3_3 {
        {5, 4, 6},
        {3, 2, 7},
        {0, 1, 8}
};

std::vector<std::vector<int>> puzzle4x4_1 {
		{1, 2, 3, 7},
		{5, 6, 10, 11},
		{4, 0, 9, 15},
		{8, 12, 13, 14}
};

std::vector<std::vector<int>> puzzle4x4_2 {
		{4, 5, 7, 2},
		{9, 14, 12, 13},
		{0, 3, 6, 11},
		{8, 1, 15, 10}
};


void printPuzzle(std::vector<std::vector<int>> puzzle){
	for (int i = 0; i < puzzle.size(); i++){
		std::cout<<"| ";
		for (int j = 0; j < puzzle.size(); j++){
			std::cout<<puzzle[i][j];
			if (j < puzzle.size() - 1)
				std::cout<<", ";
		}
		std::cout<<" |\n";
	}
}

void testBFS(){
	std::cout << "******  Breadth-first Search  ******"<<std::endl;
	std::cout <<"Solving puzzle with BFS: "<<std::endl;
	printPuzzle(puzzle3x3_1);	
	Solution bfs = BFS_Graph(new PuzzleState(puzzle3x3_1));
    bfs.printDebug();
    std::cout<<std::endl;

	std::cout <<"Solving puzzle with BFS: "<<std::endl;
	printPuzzle(puzzle3x3_2);	
	bfs = BFS_Graph(new PuzzleState(puzzle3x3_2));
    bfs.printDebug();
    std::cout<<std::endl;

	std::cout <<"Solving puzzle with BFS: "<<std::endl;
	printPuzzle(puzzle3x3_3);	
	bfs = BFS_Graph(new PuzzleState(puzzle3x3_3));
    bfs.printDebug();
    std::cout<<std::endl;
	
}


void testAstar(){
    std::cout << "******  A*  ******"<<std::endl;
    std::cout <<"Solving puzzle with A*: "<<std::endl;
    printPuzzle(puzzle3x3_1);	
    Solution astar = AStar(new PuzzleState(puzzle3x3_1));
    astar.printDebug();
    std::cout<<std::endl;

    std::cout <<"Solving puzzle with A*: "<<std::endl;
    printPuzzle(puzzle3x3_2);	
    astar = AStar(new PuzzleState(puzzle3x3_2));
    astar.printDebug();
    std::cout<<std::endl;

    std::cout <<"Solving puzzle with A*: "<<std::endl;
    printPuzzle(puzzle3x3_3);	
    astar = AStar(new PuzzleState(puzzle3x3_3));
    astar.printDebug();
    std::cout<<std::endl;

    std::cout <<"Solving puzzle with A*: "<<std::endl;
    printPuzzle(puzzle4x4_1);	
    astar = AStar(new PuzzleState(puzzle4x4_1));
    astar.printDebug();
    std::cout<<std::endl;

    std::cout <<"Solving puzzle with A*: "<<std::endl;
    printPuzzle(puzzle4x4_2);	
    astar = AStar(new PuzzleState(puzzle4x4_2));
    astar.printDebug();
    std::cout<<std::endl;

	
}

void testGBFS(){
	std::cout << "******  Greedy Best-first Search  ******"<<std::endl;
	std::cout <<"Solving puzzle with GBFS: "<<std::endl;
	printPuzzle(puzzle3x3_1);	
	Solution gbfs = GreedyBestFirstSearch(new PuzzleState(puzzle3x3_1));
    gbfs.printDebug();
    std::cout<<std::endl;

	std::cout <<"Solving puzzle with GBFS: "<<std::endl;
	printPuzzle(puzzle3x3_2);	
	gbfs = GreedyBestFirstSearch(new PuzzleState(puzzle3x3_2));
    gbfs.printDebug();
    std::cout<<std::endl;

	std::cout <<"Solving puzzle with GBFS: "<<std::endl;
	printPuzzle(puzzle3x3_3);	
	gbfs = GreedyBestFirstSearch(new PuzzleState(puzzle3x3_3));
    gbfs.printDebug();
    std::cout<<std::endl;
}


void testIterDeepDFS(){

	std::cout << "******  Iterative Deepening DFS  ******"<<std::endl;
	std::cout << "Not implemented Yet" <<std::endl;
}

void testIDAstar(){
	std::cout << "******  IDA*  ******"<<std::endl;
	std::cout <<"Solving puzzle with IDA*: "<<std::endl;
	printPuzzle(puzzle3x3_1);	
	Solution idastar = IDAStar(new PuzzleState(puzzle3x3_1));
    idastar.printDebug();
    std::cout<<std::endl;

	std::cout <<"Solving puzzle with IDA*: "<<std::endl;
	printPuzzle(puzzle3x3_2);	
	idastar = IDAStar(new PuzzleState(puzzle3x3_2));
    idastar.printDebug();
    std::cout<<std::endl;

	std::cout <<"Solving puzzle with IDA*: "<<std::endl;
	printPuzzle(puzzle3x3_3);	
	idastar = IDAStar(new PuzzleState(puzzle3x3_3));
    idastar.printDebug();
    std::cout<<std::endl;
}

void testAll(){

	std::cout << "********************************************************************************" << std::endl <<
                 "****************************** Testing algorithms ******************************" << std::endl <<
                 "********************************************************************************" << std::endl;
	testBFS();
	testAstar();
	testGBFS();
	testIterDeepDFS();
	testIDAstar();
}
