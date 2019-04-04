/**
	This file contains implementation of methods from class Solution that
	stores data that may be displayed about the entry.
*/
#include <iostream>
#include <iomanip>
#include "../include/Solution.h"

////////////////////////////////////////////////////////////////////////////////
/// Solution::Solution(PuzzleState *state)                                   ///
///  - initializes a solution with data from the initial state               ///
////////////////////////////////////////////////////////////////////////////////
Solution::Solution(PuzzleState *state) {
    this->initTime = clock();
    this->initHeuristic = state->heuristic();
    this->heuristicNodes = 1;
    this->avgHeuristic = this->initHeuristic;
    this->optimalSolLenght = 0;
    this->expandedNodes = 0;
}

void Solution::updateAvg(int newH) {
    this->avgHeuristic = ((this->avgHeuristic * this->heuristicNodes) + newH) / (this->heuristicNodes + 1);
    this->heuristicNodes = this->heuristicNodes + 1;
}

void Solution::incExpanded(){
    this->expandedNodes = this->expandedNodes + 1;
}
////////////////////////////////////////////////////////////////////////////////
/// void Solution::finish(int optCost)                                       ///
///  - called when the search was finished to save the solution cost and the ///
///    execution time.
////////////////////////////////////////////////////////////////////////////////
void Solution::finish(int optCost) {
    this->optimalSolLenght = optCost;
    this->execTime = clock() - this->initTime;
}

void Solution::clear() {
    this->heuristicNodes = 1;
    this->avgHeuristic = this->initHeuristic;
    this->optimalSolLenght = 0;
    this->expandedNodes = 0;
    this->execTime = 0;
}

void Solution::print() {
    std::cout<<"Solution: "<<std::endl;
    std::cout<<"Execution time = "<<((float)(this->execTime)) / CLOCKS_PER_SEC<<std::endl;
    std::cout<<"Expanded nodes = "<<this->expandedNodes<<std::endl;
    std::cout<<"Solution length = "<<this->optimalSolLenght<<std::endl;
    std::cout<<"Initial state heuristic value = "<<this->initHeuristic<<std::endl;
    std::cout<<"Average heuristic value = "<<this->avgHeuristic<<std::endl;
    std::cout<<"Heuristic nodes evaluated = "<<this->heuristicNodes<<std::endl;

}
