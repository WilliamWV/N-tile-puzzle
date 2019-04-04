/**
TODO: Accepts command line arguments and respond accordingly 
*/

#include <iostream>
#include "../include/searchAlgorithms.h"

int main() {
    std::vector<std::vector<int>> puzzle {{7, 2, 4}, {5, 0, 6}, {8, 3, 1}};


    Solution bfs = BFS_Graph(new PuzzleState(puzzle));
    std::cout<<"BFS-Graph: "<<std::endl;
    bfs.print();
    std::cout<<std::endl;
    Solution gbfs = GreedyBestFirstSearch(new PuzzleState(puzzle));
    std::cout<<"Greedy Best-First Search: "<<std::endl;
    gbfs.print();
    std::cout<<std::endl;
    Solution astar = AStar(new PuzzleState(puzzle));
    std::cout<<"A*: "<<std::endl;
    astar.print();
    std::cout<<std::endl;

}
