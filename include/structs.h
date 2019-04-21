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

#define UP    0
#define LEFT  1
#define RIGHT 2
#define DOWN  3
#define NONE  4

#define BYTE char

struct Node{
    PuzzleState state;
    int h;
    int size;
    int cost;
    ULL order;
    BYTE action;
};


