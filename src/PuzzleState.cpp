
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

////////////////////////////////////////////////////////////////////////////////
/// PuzzleState::PuzzleState(std::vector<std::vector<int>> puzzle)           ///
///  - Initialization of a PuzzleState based matrix, where the puzzle cells  ///
///    are represented                                                       ///
///  - In fact, this will be used only when the user inputs the initial      ///
///    matrix                                                                ///
////////////////////////////////////////////////////////////////////////////////
PuzzleState::PuzzleState(std::vector<std::vector<int>> puzzle) {
    
    this->size = static_cast<int>(puzzle.size());
    this->id = 0;
    int shift = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            ULL s = ((ULL) puzzle[i][j] << shift);
            this->id = this->id | s;
            shift += 4;
        }
    }
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (puzzle[i][j] == 0){
                this->zeroY = i;
                this->zeroX = j;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
/// std::vector<State*> PuzzleState::succ()                                  ///
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
std::vector<State*> PuzzleState::succ() {

    std::vector<State*> ans;
    //UP
    if (zeroY - 1 >= 0){
        PuzzleState* suc = new PuzzleState(this->id, this->size);
        suc->setPuzzleCell(zeroY, zeroX, this->getPuzzleCell(zeroY - 1, zeroX));
        suc->setPuzzleCell(zeroY - 1, zeroX, this->getPuzzleCell(zeroY, zeroX));
        ans.push_back(suc);
    }
    //LEFT
    if (zeroX - 1 >= 0){
        PuzzleState* suc = new PuzzleState(this->id, this->size);
        suc->setPuzzleCell(zeroY, zeroX, this->getPuzzleCell(zeroY, zeroX - 1));
        suc->setPuzzleCell(zeroY, zeroX - 1, this->getPuzzleCell(zeroY, zeroX));
        ans.push_back(suc);
    }
    //RIGHT
    if (zeroX + 1 < this->size){
        PuzzleState* suc = new PuzzleState(this->id, this->size);
        suc->setPuzzleCell(zeroY, zeroX, this->getPuzzleCell(zeroY, zeroX + 1));
        suc->setPuzzleCell(zeroY, zeroX + 1, this->getPuzzleCell(zeroY, zeroX));
        ans.push_back(suc);
    }
    //DOWN
    if (zeroY + 1 < this->size){
        PuzzleState* suc = new PuzzleState(this->id, this->size);
        suc->setPuzzleCell(zeroY, zeroX, this->getPuzzleCell(zeroY + 1, zeroX));
        suc->setPuzzleCell(zeroY + 1, zeroX, this->getPuzzleCell(zeroY, zeroX));
        ans.push_back(suc);
    }
    return ans;
}

////////////////////////////////////////////////////////////////////////////////
/// bool PuzzleState::isGoal()                                               ///
///  - Determines if the state is the goal state:                            ///
///                    | 0 1 2 |        | 0  1  2  3 |                       ///
///                    | 3 4 5 |   or   | 4  5  6  7 |                       ///
///                    | 6 7 8 |        | 8  9 10 11 |                       ///
///                                     |12 13 14 15 |                       ///
////////////////////////////////////////////////////////////////////////////////
bool PuzzleState::isGoal() {
    for (int i = 0; i < this->size; i++){
        for (int j = 0; j <this->size; j++){
            if (getPuzzleCell(i, j) != j + i * this->size) return false;
        }
    }
    return true;
}
////////////////////////////////////////////////////////////////////////////////
/// int PuzzleState::heuristic()                                             ///
///  - Calculates the heuristic funtion of the state, based on the manhattan ///
///    distance from each value's current position to the final position of  ///
///    this value, this must not counts 0 because it is the representation   ///
///    of the blank cell                                                     ///
////////////////////////////////////////////////////////////////////////////////
int PuzzleState::heuristic() {

    int h = 0;
    for (int i = 0; i < this->size; i++){
        for(int j = 0; j < this->size; j++){
            int puzzleCell = getPuzzleCell(i, j);
            if (puzzleCell != 0){
                h += abs(puzzleCell % this->size - j); // horizontal manhattan distance
                h += abs(puzzleCell / this->size - i); // vertical manhattan distance
            }
        }
    }
    return h;

}

ULL PuzzleState::getId() {
    return this->id;
}

////////////////////////////////////////////////////////////////////////////////
/// int PuzzleState::getPuzzleCell(int row, int col)                         ///
///  - Obtains a specific value from the puzzle, this uses bitwise           ///
///    operations to extract only the cell value from the state              ///
///    representation                                                        ///
////////////////////////////////////////////////////////////////////////////////
int PuzzleState::getPuzzleCell(int row, int col) {
    int desloc = 4 * (row * 3 + col);
    ULL mask = (ULL)15 << desloc;
    return (int)((this->id & mask) >> desloc);
}

////////////////////////////////////////////////////////////////////////////////
/// void PuzzleState::setPuzzleCell(int row, int col, int val)               ///
///  - Sets a specific cell of the puzzle to a value, this will bitwise      ///
///    operations to put 0000 where the value must be stored to clear the    ///
///    previous state, and then uses bitwise or to fill this space with the  ///
///    desired value.                                                        ///
////////////////////////////////////////////////////////////////////////////////
void PuzzleState::setPuzzleCell(int row, int col, int val) {
    int desloc = 4 * (row * 3 + col);
    ULL mask = (ULL)15 << desloc;
    ULL invMask = ~mask;
    this->id = this->id & invMask;
    this->id = this->id | (mask & ((ULL)val << desloc));

    if (val == 0){
        this->zeroX = col;
        this->zeroY = row;
    }
}

////////////////////////////////////////////////////////////////////////////////
/// PuzzleState::PuzzleState(ULL id, int size)                               ///
///  - Initialization of a PuzzleState based on its unsigned long long       ///
///    representation                                                        ///
///  - this is used by the succ().                                           ///
////////////////////////////////////////////////////////////////////////////////
PuzzleState::PuzzleState(ULL id, int size) {
    this->id = id;
    this->size = size;

    for (int i = 0; i<this->size; i++){
        for (int j = 0; j<this->size; j++){
            if(this->getPuzzleCell(i, j) == 0){
                this->zeroX = j;
                this->zeroY = i;
            }
        }
    }
}

#endif //PUZZLESTATE_CPP