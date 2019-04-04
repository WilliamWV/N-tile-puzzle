/**
	This file contains headers of the algorithms and comparision classes used
	on priority queues
*/
#ifndef SEARCHALGORITHMS_H
#define SEARCHALGORITHMS_H


#include <deque>
#include <set>
#include <queue>
#include <stack>
#include "Solution.h"


//Node comparision to Greedy Best first search
class GBFSComp{
public:
    bool operator() (Node a, Node b){

        return a.state->heuristic() >= b.state->heuristic();
    }
};


//Node comparision to A*
class AstarComp{
public:
    bool operator() (Node a, Node b){
        int sub = (a.state->heuristic() + a.cost) - (b.state->heuristic() + b.cost);
        if (sub < 0)
            return false;
        else if (sub > 0)
            return true;
        else return a.state->heuristic() >= b.state->heuristic(); // heuristic is used as tie breaker
    }
};
Solution BFS_Graph(PuzzleState* init);
Solution GreedyBestFirstSearch(PuzzleState* init);
Solution AStar(PuzzleState* init);
Solution IterativeDeepeningDFS(PuzzleState* init);

#endif //SEARCHALGORITHMS_H
