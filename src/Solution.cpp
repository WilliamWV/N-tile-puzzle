/**
	This file contains implementation of methods from class Solution that
	stores data that may be displayed about the entry.
*/
#include <iostream>
#include <iomanip>
#include "../include/Solution.h"

////////////////////////////////////////////////////////////////////////////////
/// Solution::Solution(Node* n)                                              ///
///  - initializes a solution with data from the initial state               ///
////////////////////////////////////////////////////////////////////////////////
Solution::Solution(Node n) {
    this->initTime = clock();
    this->initHeuristic = n.h;
    this->heuristicNodes = 1;
    this->avgHeuristic = this->initHeuristic;
    this->optimalSolLenght = 0;
    this->expandedNodes = 0;
}

void Solution::updateAvg(int newH) {
    this->avgHeuristic += newH;
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
    if (this->heuristicNodes > 1){ // nodos usam heurística
        this->avgHeuristic /= this->heuristicNodes;
    }
    else
        this->avgHeuristic = 0;
}

void Solution::clear() {
    this->heuristicNodes = 1;
    this->avgHeuristic = this->initHeuristic;
    this->optimalSolLenght = 0;
    this->expandedNodes = 0;
    this->execTime = 0;
}

void Solution::printDebug() {
    std::cout<<"Solution: "<<std::endl;
    std::cout<<"Execution time = "<<((float)(this->execTime)) / CLOCKS_PER_SEC<<std::endl;
    std::cout<<"Expanded nodes = "<<this->expandedNodes<<std::endl;
    std::cout<<"Solution length = "<<this->optimalSolLenght<<std::endl;
    std::cout<<"Initial state heuristic value = "<<this->initHeuristic<<std::endl;
    std::cout<<"Average heuristic value = "<<this->avgHeuristic<<std::endl;
    std::cout<<"Heuristic nodes evaluated = "<<this->heuristicNodes<<std::endl;

}

void Solution::print() {
	std::cout<<this->expandedNodes<<","<<this->optimalSolLenght<<","
             << (double) this->execTime / CLOCKS_PER_SEC << "," 
             << this->avgHeuristic<< ","<<this->initHeuristic<<std::endl;
}
