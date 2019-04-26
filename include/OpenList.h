#ifndef OPEN_H
#define OPEN_H

#include "searchAlgorithms.h"

//Node comparision to A*
class AstarComp{
public:
    bool operator() (Node a, Node b){
        int hDiff = a.h - b.h;
        if (hDiff < 0) return false;
        else if (hDiff > 0) return true;
        else return a.order < b.order; // heuristic is used as tie breaker
    }
};

class OpenList{
    public:
        OpenList();
        void insert(Node n);
        Node pop_min();
        bool empty();
    private:
        int smaller_f;
        int greater_f;
        std::vector<int> smaller_h;
        std::vector<int> greater_h;
        std::vector<std::vector<std::vector<Node>>> open; 
};


#endif //OPEN_H