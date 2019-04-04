/**
	This file contains important structures and classes used by the search 
	algorithms
*/

#include <vector>
#include <cmath>
#include <climits>

#define ULL unsigned long long

class State {
public:
    //Define pure virtual functions to describe the state
    virtual std::vector<State*> succ() = 0;
    virtual bool isGoal() = 0;
    virtual int heuristic() = 0;
    virtual ULL getId() = 0;

};

class Node{

public:
    Node(State * state, int cost){
        this->state = state;
        this->cost = cost;
    }
    State * state;
    int cost;
};


