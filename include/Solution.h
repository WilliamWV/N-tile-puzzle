/**
	This file contains the definitions of class Solution used to store data
	about the search.
*/
#ifndef SOLUTION_H
#define SOLUTION_H

#include <time.h>
#include "PuzzleState.h"
class Solution {
public:
    Solution (Node *n);

    void updateAvg(int newH);
    void incExpanded();
    void finish (int optCost);
    void clear ();
    void printDebug();
    void print ();

public:
    int expandedNodes;
    int optimalSolLenght;
    int heuristicNodes;
    double avgHeuristic;
    int initHeuristic;
    clock_t execTime;
    clock_t initTime;

};


#endif //SOLUTION_H
