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
class PuzzleState : public State{
public:
    explicit PuzzleState(std::vector<std::vector<int>> puzzle);
    explicit PuzzleState(ULL id, int size, int h);
    std::vector<State*> succ() override;
    bool isGoal() override ;
    int heuristic() override ;
    ULL int getId() override;
    int getPuzzleCell(int row, int col);
    void setPuzzleCell(int row, int col, int val);
	void swapCells(int r1, int c1, int r2, int c2);
    void calculateHeuristic();

private:
    int size;
    ULL id;
    int h;
};
#endif //PUZZLESTATE_H
