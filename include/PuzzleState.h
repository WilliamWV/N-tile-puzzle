/**
	This file contains definitions to the class PuzzleState used to represent
	a search state.
*/
#ifndef PUZZLESTATE_H
#define PUZZLESTATE_H
#include "structs.h"

/**
     * Each cell on the puzzle represent a 4-bit group inside the 64-bit number
     * ex:
     *
     *      | 1  2  3 |
     *      | 4  5  6 |  =>  0000 1000 0111 0110 0101 0100 0011 0010 0001
     *      | 7  8  0 |
     *
     *      | 5  3  2 |
     *      | 1  7  4 |  =>  0110 1000 0000 0100 0111 0001 0010 0011 0101
     *      | 0  8  6 |
     *
     *      | 10  7  1 13 |
     *      |  5 11  6  9 |  => 1111 1110 1000 1100 0100 0000 0011 0010 1001 0110 1011 0101 1101 0001 0111 1010
     *      |  2  3  0  4 |
     *      | 12  8 14 15 |
     *
     * 
*/

Node make_root_node(std::vector<std::vector<int>> puzzle);
Node copy_node(Node other);
std::vector<Node> succ(Node n);
bool isGoal(Node n);
int heuristic(Node n);
int getPuzzleCell(Node n, int row, int col);
Node swapCells(Node n, int r1, int c1, int r2, int c2);
int calculateHeuristic(Node n);

#endif //PUZZLESTATE_H
