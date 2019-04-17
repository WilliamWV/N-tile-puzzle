
/**

This file contains the implementation of methods from class PuzzleState, 
so here is the implementation for:
	* initializing state	
	* obtaining successors of a state
	* checking if a state is goal
	* calculation of heuristic function	

OBS: To docs about the PuzzleState structure read the comments of file 
	 PuzzleState.h 

*/

#ifndef PUZZLESTATE_CPP
#define PUZZLESTATE_CPP
#include "../include/PuzzleState.h"
#include <iostream>

ULL nodeOrder = 0;

////////////////////////////////////////////////////////////////////////////////
/// Node* make_root_state(std::vector<std::vector<int>> puzzle)              ///
///  - Initialization of a Node from a matrix, where the puzzle cells are    ///
///    represented                                                           ///
////////////////////////////////////////////////////////////////////////////////
Node make_root_node(std::vector<std::vector<int>> puzzle) {
    Node ans;

    ans.size = static_cast<int>(puzzle.size());
    ans.state = 0;
    int shift = 0;
    for (int i = 0; i < ans.size; i++) {
        for (int j = 0; j < ans.size; j++) {
            ULL s = ((ULL) puzzle[i][j] << shift);
            ans.state = ans.state | s;
            shift += 4;
        }
    }
    ans.h = calculateHeuristic(ans);
    ans.cost = 0;
    nodeOrder = 0;
    ans.order = nodeOrder++;
    return ans;
}


Node copy_node(Node other){
    Node ans;
    ans.size = other.size;
    ans.state = other.state;
    ans.h = other.h;
    ans.cost = other.cost + 1;
    ans.order = nodeOrder++;
    return ans;
}

////////////////////////////////////////////////////////////////////////////////
///  std::vector<Node*> succ(Node* n)                                        ///
///  - Used to obtain all the successor states of this state, these, will be ///
///    generated following the order of the four actions of moving the blank ///
///    space, that is:                                                       ///
///      1) UP:                                                              ///
///              | 1 2 3 |      | 1 0 3 |                                    ///
///              | 4 0 5 |  ->  | 4 2 5 |                                    ///
///              | 6 7 8 |      | 6 7 8 |                                    ///
///      2) LEFT:                                                            ///
///              | 1 2 3 |      | 1 2 3 |                                    ///
///              | 4 0 5 |  ->  | 0 4 5 |                                    ///
///              | 6 7 8 |      | 6 7 8 |                                    ///
///      3) RIGHT:                                                           ///
///              | 1 2 3 |      | 1 2 3 |                                    ///
///              | 4 0 5 |  ->  | 4 5 0 |                                    ///
///              | 6 7 8 |      | 6 7 8 |                                    ///
///      4) DOWN:                                                            ///
///              | 1 2 3 |      | 1 2 3 |                                    ///
///              | 4 0 5 |  ->  | 4 7 5 |                                    ///
///              | 6 7 8 |      | 6 0 8 |                                    ///
////////////////////////////////////////////////////////////////////////////////

std::vector<Node> succ(Node n) {

    std::vector<Node> ans;
    int zeroX;
    int zeroY;
    for (int i = 0; i<n.size; i++){
        for (int j = 0; j<n.size; j++){
            if(getPuzzleCell(n, i, j) == 0){
                zeroX = j;
                zeroY = i;
            }
        }
    }
    //UP
    if (zeroY - 1 >= 0){
        Node suc = copy_node(n);
        suc = swapCells(suc, zeroY - 1, zeroX, zeroY, zeroX);        
        ans.push_back(suc);
    }
    //LEFT
    if (zeroX - 1 >= 0){
        Node suc = copy_node(n);
        suc = swapCells(suc, zeroY, zeroX - 1, zeroY, zeroX);             
        ans.push_back(suc);
    }
    //RIGHT
    if (zeroX + 1 < n.size){
        Node suc = copy_node(n);
        suc = swapCells(suc, zeroY, zeroX + 1, zeroY, zeroX);                
        ans.push_back(suc);
    }
    //DOWN
    if (zeroY + 1 < n.size){
        Node suc = copy_node(n);        
        suc = swapCells(suc, zeroY + 1, zeroX, zeroY, zeroX);        
        ans.push_back(suc);
    }
    return ans;
}

////////////////////////////////////////////////////////////////////////////////
/// bool isGoal(Node* n)                                                     ///
///  - Determines if the state is the goal state:                            ///
///                    | 0 1 2 |        | 0  1  2  3 |                       ///
///                    | 3 4 5 |   or   | 4  5  6  7 |                       ///
///                    | 6 7 8 |        | 8  9 10 11 |                       ///
///                                     |12 13 14 15 |                       ///
////////////////////////////////////////////////////////////////////////////////
#define GOAL_3X3 0x876543210
#define GOAL_4X4 0xFEDCBA9876543210
bool isGoal(Node n) {
    if (n.size == 3) return n.state == GOAL_3X3;
    else return n.state == GOAL_4X4;
}

int heuristic(Node n) {
    return n.h;

}

////////////////////////////////////////////////////////////////////////////////
/// int getPuzzleCell(Node* n, int row, int col)                             ///
///  - Obtains a specific value from the puzzle, this uses bitwise           ///
///    operations to extract only the cell value from the state              ///
///    representation                                                        ///
////////////////////////////////////////////////////////////////////////////////
int getPuzzleCell(Node n, int row, int col) {
    int desloc = 4 * (row * n.size + col);
    ULL mask = (ULL)15 << desloc;
    return (int)((n.state & mask) >> desloc);
}

////////////////////////////////////////////////////////////////////////////////
/// void calculateHeuristic(Node* n)                                         ///
///  - Calculates the heuristic funtion of the state, based on the manhattan ///
///    distance from each value's current position to the final position of  ///
///    this value, this must not counts 0 because it is the representation   ///
///    of the blank cell                                                     ///
////////////////////////////////////////////////////////////////////////////////

int calculateHeuristic(Node n){
	int h = 0;
    for (int i = 0; i < n.size; i++){
        for(int j = 0; j < n.size; j++){
            int puzzleCell = getPuzzleCell(n, i, j);
            if (puzzleCell != 0){
                h += abs(puzzleCell % n.size - j); // horizontal manhattan distance
                h += abs(puzzleCell / n.size - i); // vertical manhattan distance
            }
        }
    }
	return h;
}

////////////////////////////////////////////////////////////////////////////////
/// void swapCells(Node* n, int r, int c, int rb, int cb)                    ///
///  - This function substitute the previous use of setPuzzleCell(), being   ///
///    faster to execute the two value changes on a movement and also        ///
///    recalculating the heuristic value, this will use bitwise operations   ///
///    to be fast.                                                           ///
////////////////////////////////////////////////////////////////////////////////
Node swapCells(Node n, int r, int c, int rb, int cb){
	int desloc1 = 4 * (r * n.size + c);
	int desloc2 = 4 * (rb * n.size + cb);
	ULL mask1 = (ULL)15 << desloc1;
	ULL mask2 = (ULL)15 << desloc2;

	ULL invMask = ~(mask1 | mask2);

	int val = getPuzzleCell(n, r, c);

    n.state = n.state & invMask;
	n.state = n.state | (mask2 & ((ULL) val << desloc2));
	
	n.h -= abs(val % n.size - c); // horizontal manhattan distance of the previos position
    n.h -= abs(val / n.size - r); // vertical manhattan distance of the previos position
	
	n.h += abs(val % n.size - cb); // horizontal manhattan distance of the new position
    n.h += abs(val / n.size - rb); // vertical manhattan distance of the new position
	
	return n;
}
    

#endif //PUZZLESTATE_CPP
