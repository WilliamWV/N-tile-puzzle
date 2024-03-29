/**
	This file contains headers of the algorithms and comparision classes used
	on priority queues
*/
#ifndef SEARCHALGORITHMS_H
#define SEARCHALGORITHMS_H


#include <deque>
#include <set>
#include <unordered_set>
#include <queue>
#include <stack>
#include "Solution.h"


//Node comparision to Greedy Best first search
class GBFSComp{
public:
    bool operator() (Node a, Node b){
        int hDiff = a.h - b.h;
        if (hDiff < 0) return false;
        else if (hDiff > 0) return true;
        else return a.order < b.order;
    }
};



Solution BFS_Graph(Node init);
Solution GreedyBestFirstSearch(Node init);
Solution AStar(Node init);
Solution IDAStar(Node init); 
Solution IterativeDeepeningDFS(Node init);

#endif //SEARCHALGORITHMS_H
