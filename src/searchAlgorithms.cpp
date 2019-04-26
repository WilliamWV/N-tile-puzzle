/**
	This file contains the implementation of the required search algorithms
*/
#include <iostream>
#include "../include/OpenList.h"

////////////////////////////////////////////////////////////////////////////////
/// Solution BFS_Graph(Node* init)                                           ///
///  - Search through the state space using BFS-Graph algorithm, this        ///
///    algorithm does not use the heuristic value and expand the nodes in    ///
///    their generation order.                                               ///
///  - The algorithm is optimal for the Puzzle problem once every actions    ///
///    have the same cost.                                                   ///
////////////////////////////////////////////////////////////////////////////////
Solution BFS_Graph(Node init){
    Solution ans = Solution(init);
    if (isGoal(init)){
        ans.finish(0);
        return ans;
    }
    std::deque <Node> open;
    open.push_front(init);
    std::set <PuzzleState> closed;
    closed.insert(init.state);
    while (! open.empty()){
        Node current = open.front();
        open.pop_front();
        ans.incExpanded();
        for (Node n : succ(current)){
            if (isGoal(n)){
                ans.finish(n.cost);
                return ans;
            }

            if (closed.find(n.state) == closed.end()){ // not in closed
                closed.insert(n.state);
                open.push_back(n);
            }
        }
    }
    ans.finish(INT_MAX); // infinite
    return  ans;//
}


////////////////////////////////////////////////////////////////////////////////
/// Solution GreedyBestFirstSearch(Node * init)                              ///
///  - Search through the state space using Greedy Best-First Search         ///
///    algorithm, that consider the heuristic value only to define the       ///
///    expansion order of the nodes.                                         ///
///  - The algorithm is not optimal.                                         ///
////////////////////////////////////////////////////////////////////////////////
Solution GreedyBestFirstSearch(Node init){
    Solution ans = Solution(init);
    std::priority_queue <Node, std::vector<Node>, GBFSComp> open;
    open.push(init);
    std::unordered_set <PuzzleState> closed;
    while (! open.empty()){
        Node current = open.top();
        open.pop();
        if (closed.find(current.state) == closed.end()){ // not in closed
            closed.insert(current.state);
            if (isGoal(current)){
                ans.finish(current.cost);
                return ans;
            }
            ans.incExpanded();
            for (Node n : succ(current)) {

                ans.updateAvg(n.h);
                open.push(n);
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

Solution AStar(Node init){
    Solution ans = Solution(init);
    //std::priority_queue <Node, std::vector<Node>, AstarComp> open;
    //open.push(init);
    OpenList open = OpenList();
    open.insert(init);
    std::unordered_set <PuzzleState> closed;
    while (! open.empty()){
        Node current = open.pop_min();
        //open.pop();
        if (closed.find(current.state) == closed.end()){ // not in closed
            closed.insert(current.state);
            if (isGoal(current)){
                ans.finish(current.cost);
                return ans;
            }
            ans.incExpanded();
            for (Node n : succ(current)) {

                ans.updateAvg(n.h);
                open.insert(n);
            }
        }

    }
    ans.finish(INT_MAX); // infinite
    return  ans;//
}

int f (Node n){
	return n.cost + n.h;
}

#define PAIR_INT_SOL std::pair <int, Solution*>

PAIR_INT_SOL IDARecSearch (Node n, int f_limit, Solution* ans){
    if (f(n) > f_limit){
        return std::make_pair(f(n), nullptr);
    }
    if (isGoal(n)){
        return std::make_pair(-1, ans);
    }
    int next_limit = INT_MAX;
    ans->incExpanded();
    for (Node ns : succ(n)) {
        if (ns.h < INT_MAX){
            ans->updateAvg(ns.h);
            PAIR_INT_SOL sol = IDARecSearch(ns, f_limit, ans);
            if (sol.second != nullptr){
                return std::make_pair(-1, sol.second);
            }
            next_limit = std::min (next_limit, sol.first);
        }
    }
	return std::make_pair(next_limit, nullptr);
}

////////////////////////////////////////////////////////////////////////////////
/// Solution IDAStar(Node* init)                                             ///
///  - Use Iterative Deepening and heuristic value to reduce Iterative       ///
///    deepening overhead while using less memory than other methods         ///
///  - Once this algorithm does not use a priority_queue, the order fiels    ///
///    of nodes is not used so it will always contains 0                     ///
////////////////////////////////////////////////////////////////////////////////
Solution IDAStar(Node init){
	Solution ans = Solution(init);
	int f_limit = init.h;
	while (f_limit < INT_MAX){
		PAIR_INT_SOL s = IDARecSearch(init, f_limit, &ans);
		if (s.second != nullptr){
			// It is possible to use f_limit here because the heuristic is 
			// goal-aware
			ans.finish(f_limit); 			
			return ans;		
		}
		f_limit = s.first;	
	}
	return ans;
}


Solution* DepthLimitedSearch(Node n, int depth_limit, Solution* ans){
    if (isGoal(n)) {
        return ans;
    }
    if (depth_limit > 0){
        //std::cout<<"4"<<std::endl;
        ans->incExpanded();
        //std::cout<<"5"<<std::endl;
        for (Node ns : succ(n)) {
            Solution* sol = DepthLimitedSearch(ns, depth_limit - 1, ans);
            if (sol != nullptr) return sol;
        }
        //std::cout<<"6"<<std::endl;
        
    }
    return nullptr;
    
}

Solution IterativeDeepeningDFS(Node init)
{
    Solution ans = Solution(init);
    //std::cout<<"1"<<std::endl;
    int depth_limit = 0;
    while (depth_limit < INT_MAX){
        //std::cout<<"2"<<std::endl;
        Solution* sol = DepthLimitedSearch(init, depth_limit, &ans);
        //std::cout<<"3"<<std::endl;
        if (sol != nullptr) {
            ans.finish(depth_limit);
            return ans;
        }
        depth_limit++;
    }
    return ans;

}

