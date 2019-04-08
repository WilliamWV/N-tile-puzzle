
#include "../include/test.h"
#include <string.h>
#include <cstdlib>

#define DEBUG 0

void printInstance(std::vector<int> inst){
	for (int i = 0; i<inst.size(); i++){
		std::cout<<inst[i]<<' ';
	}
	std::cout<<std::endl;
}

int main(int argc, char *argv[]) {
   	if (DEBUG == 1){
		testAll();
	}
	else{

		std::vector<std::vector<int>> instances;
		std::vector<int> instance;
		for (int i = 2; i < argc; i++){
			int argLen = strlen(argv[i]);
			if (argv[i][argLen-1] == ','){
				argv[i][argLen-1] = '\0';
				instance.push_back(atoi(argv[i]));
				instances.push_back(instance);
				instance.clear();			
			}
			else{
				instance.push_back(atoi(argv[i]));
			}
		}
		instances.push_back(instance);
		std::vector<std::vector<std::vector<int>>> puzzles;
		for (int i = 0; i < instances.size(); i++){
			std::vector<std::vector<int>> puzzle;
			int instSize = instances[i].size();	
			if (instSize == 9){
				for (int j = 0; j < 3; j++){
					std::vector<int> line;
					for(int k = 0; k < 3; k++){
						line.push_back(instances[i][j * 3 + k]);
					}
					puzzle.push_back(line);
					
				}
				
				puzzles.push_back(puzzle);
			}
			else if (instSize == 16){
				for (int j = 0; j < 4; j++){
					std::vector<int> line;
					for(int k = 0; k < 4; k++){
						line.push_back(instances[i][j * 4 + k]);
					}
					puzzle.push_back(line);
					
				}
				
				puzzles.push_back(puzzle);
			}		
			else{
				std::cout<<"The fololowing instance is not valid:";
				printInstance(instances[i]);			
			}
			
		}
		if (argc > 1){
			if (strncmp(argv[1], "-bfs", 16) == 0){
				
				for (int i = 0; i < puzzles.size(); i++){
					std::cout <<"Solving puzzle with BFS: "<<std::endl;
					printPuzzle(puzzles[i]);	
					Solution bfs = BFS_Graph(new PuzzleState(puzzles[i]));
					bfs.print();
				}
			}
			else if (strncmp(argv[1], "-idfs", 16) == 0){
				std::cout<<"Not yet implemented"<<std::endl;
			}
			else if (strncmp(argv[1], "-astar", 16) == 0){
				for (int i = 0; i < puzzles.size(); i++){
					std::cout <<"Solving puzzle with A*: "<<std::endl;
					printPuzzle(puzzles[i]);	
					Solution astar = AStar(new PuzzleState(puzzles[i]));
					astar.print();
				}
			}
			else if (strncmp(argv[1], "-idastar", 16) == 0){
				std::cout<<"Not yet implemented"<<std::endl;
			}
			else if (strncmp(argv[1], "-gbfs", 16) == 0){
				for (int i = 0; i < puzzles.size(); i++){
					std::cout <<"Solving puzzle with GBFS*: "<<std::endl;
					printPuzzle(puzzles[i]);	
					Solution gbfs = GreedyBestFirstSearch(new PuzzleState(puzzles[i]));
					gbfs.print();
				}
			}
		}

	}	
	return 0;
}
