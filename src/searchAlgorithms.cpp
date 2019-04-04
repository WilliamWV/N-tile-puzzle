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

    Solution ans = Solution(init);
    if (init->isGoal()){
        ans.finish(0);
        return ans;
    }
    std::deque <Node> open;
    open.push_front(Node(init, 0));
    std::set <ULL> closed;
    closed.insert(init->getId());
    while (! open.empty()){
        Node current = open.front();
        open.pop_front();
        ans.incExpanded();
        for (State * s : current.state->succ()){
            Node suc = Node(s, current.cost + 1);
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
//TODO: verificar se precisa usar reopening 
Solution GreedyBestFirstSearch(PuzzleState * init){
    Solution ans = Solution(init);
    if (init->isGoal()){
        ans.finish(0);
        return ans;
    }
    std::priority_queue <Node, std::vector<Node>, GBFSComp> open;
    open.push(Node(init, 0));
    std::set <ULL> closed;
    closed.insert(init->getId());

    while (! open.empty()){
        Node current = open.top();
        open.pop();
        ans.incExpanded();
        for (State* s : current.state->succ()){
            Node suc = Node(s, current.cost + 1);

            if (s->heuristic() == 0){
                bool a = s->isGoal();
            }
            if (s->isGoal()){
                ans.updateAvg(s->heuristic());
                ans.finish(suc.cost);
                return ans;
            }

            if (closed.find(s->getId()) == closed.end()){ // not in closed
                ans.updateAvg(s->heuristic());
                closed.insert(s->getId());
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
    if (init->isGoal()){
        ans.finish(0);
        return ans;
    }
    std::priority_queue <Node, std::vector<Node>, AstarComp> open;
    open.push(Node(init, 0));
    std::set <ULL> closed;
    closed.insert(init->getId());
    while (! open.empty()){
        Node current = open.top();
        open.pop();
        ans.incExpanded();
        for (State* s : current.state->succ()){
            Node suc = Node(s, current.cost + 1);
            if (s->isGoal()){
                ans.updateAvg(s->heuristic());
                ans.finish(suc.cost);
                return ans;
            }

            if (closed.find(s->getId()) == closed.end()){ // not in closed
                ans.updateAvg(s->heuristic());
                closed.insert(s->getId());
                open.push(suc);
            }
        }
    }
    ans.finish(INT_MAX); // infinite
    return ans;
}

