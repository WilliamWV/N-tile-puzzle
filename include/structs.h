/**
	This file contains important structures and classes used by the search 
	algorithms
*/

#include <vector>
#include <cmath>
#include <climits>
#include <cstdlib>

#define ULL unsigned long long
#define PuzzleState ULL

struct Node{
    PuzzleState state;
    int h;
    int size;
    int cost;
    ULL order;
};


