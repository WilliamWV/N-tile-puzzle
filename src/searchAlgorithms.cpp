/**
	This file contains the implementation of the required search algorithms
*/
#include <iostream>
#include "../include/searchAlgorithms.h"

////////////////////////////////////////////////////////////////////////////////
/// Solution BFS_Graph(PuzzleState* init)                                    ///
///  - Search through the state space using BFS-Graph algorithm, this        ///
///    algorithm does not use the heuristic value and expand the nodes in    ///
///    their generation order.                                               ///
///  - The algorithm is optimal for the Puzzle problem once every actions    ///
///    have the same cost.                                                   ///
////////////////////////////////////////////////////////////////////////////////
Solution BFS_Graph(PuzzleState* init){
	ULL insertionOrder = 0;
    Solution ans = Solution(init);
    if (init->isGoal()){
        ans.finish(0);
        return ans;
    }
    std::deque <Node> open;
    open.push_front(Node(init, 0, insertionOrder++));
    std::set <ULL> closed;
    closed.insert(init->getId());
    while (! open.empty()){
        Node current = open.front();
        open.pop_front();
        ans.incExpanded();
        for (State * s : current.state->succ()){
            Node suc = Node(s, current.cost + 1, insertionOrder++);
            if (s->isGoal()){
                ans.updateAvg(s->heuristic());
                ans.finish(suc.cost);
                return ans;
            }

            if (closed.find(s->getId()) == closed.end()){ // not in closed
                ans.updateAvg(s->heuristic());
                closed.insert(s->getId());
                open.push_back(suc);
            }
        }
    }
    ans.finish(INT_MAX); // infinite
    return  ans;//
}


////////////////////////////////////////////////////////////////////////////////
/// Solution GreedyBestFirstSearch(PuzzleState * init)                       ///
///  - Search through the state space using Greedy Best-First Search         ///
///    algorithm, that consider the heuristic value only to define the       ///
///    expansion order of the nodes.                                         ///
///  - The algorithm is not optimal.                                         ///
////////////////////////////////////////////////////////////////////////////////
Solution GreedyBestFirstSearch(PuzzleState * init){
    Solution ans = Solution(init);
    ULL insertionOrder = 0;
    std::priority_queue <Node, std::vector<Node>, GBFSComp> open;
    open.push(Node(init, 0, insertionOrder++));
    std::set <ULL> closed;
    while (! open.empty()){
        Node current = open.top();
        open.pop();
        if (closed.find(current.state->getId()) == closed.end()){ // not in closed
            closed.insert(current.state->getId());
            if (current.state->isGoal()){

                ans.finish(current.cost);
                return ans;
            }
            ans.incExpanded();
            for (State* s : current.state->succ()) {
                ans.updateAvg(s->heuristic());
                Node suc = Node(s, current.cost + 1, insertionOrder++);
                open.push(suc);
            }
        }

    }
    ans.finish(INT_MAX); // infinite
    return  ans;//
}


////////////////////////////////////////////////////////////////////////////////
/// Solution AStar(PuzzleState* init)                                        ///
///  - Consider the heuristic value of the node and the real cost, to        ///
///    determine the expansion order.                                        ///
///  - This implementation does not uses reopening, once the heuristic is    ///
///    consistent, so the algorithm is optimal and would not use reopening   ///
////////////////////////////////////////////////////////////////////////////////

Solution AStar(PuzzleState* init){
    Solution ans = Solution(init);
    ULL insertionOrder = 0;
    std::priority_queue <Node, std::vector<Node>, AstarComp> open;
    open.push(Node(init, 0, insertionOrder++));
    std::set <ULL> closed;
    while (! open.empty()){
        Node current = open.top();
        open.pop();
        if (closed.find(current.state->getId()) == closed.end()){ // not in closed
            closed.insert(current.state->getId());
            if (current.state->isGoal()){
                ans.finish(current.cost);
                //ans.updateAvg(current.state->heuristic());
                return ans;
            }
            ans.incExpanded();
            //ans.updateAvg(current.state->heuristic());
            for (State* s : current.state->succ()) {

                Node suc = Node(s, current.cost + 1, insertionOrder++);
                ans.updateAvg(s->heuristic());
                open.push(suc);
            }
        }

    }
    ans.finish(INT_MAX); // infinite
    return  ans;//
}




