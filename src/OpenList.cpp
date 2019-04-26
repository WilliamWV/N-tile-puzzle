#include "../include/OpenList.h"
#include <iostream>
OpenList::OpenList(){
    this->smaller_f = -1;
    this->greater_f = 0;
}
void OpenList::insert(Node n){
    int nh = n.h;
    int nf = n.cost + nh;
    if (nf > this->greater_f){
        this->greater_f = nf;
        while (this->open.size() <= nf){
            std::vector<std::vector<Node>> newFList;
            open.push_back(newFList);
            this->smaller_h.push_back(-1);
            this->greater_h.push_back(0);
        }
    }

    if (this->smaller_f > nf || this->smaller_f < 0){
        this->smaller_f = nf;
    }
    if (this->smaller_h[nf] > nh || this->smaller_h[nf] < 0){
        this->smaller_h[nf] = nh;
    }

    if (n.h > this->greater_h[nf]){
        this->greater_h[nf] = nh;
        while (this->open[nf].size() <= nh){
            std::vector<Node> newHList;
            open[nf].push_back(newHList);
        }
    }
    this->open[nf][nh].push_back(n);
}
Node OpenList::pop_min(){
    int sf = this->smaller_f;
    int sh = this->smaller_h[sf];
    Node ans = this->open[sf][sh].back();
    this->open[sf][sh].pop_back();
    while (this->smaller_h[sf] <= this->greater_h[sf] && this->open[sf][this->smaller_h[sf]].empty()){
        this->smaller_h[sf]++;
    }
    if (this->smaller_h[sf] > this->greater_h[sf]){
        this->smaller_h[sf] = -1;
        this->greater_h[sf] = 0;
        this->smaller_f++;
        while (this->smaller_f <= this->greater_f && this->open[this->smaller_f].empty()){
            this->smaller_f++;
        }
        if (this->smaller_f > this->greater_f){
            this->smaller_f = -1;
            this->greater_f = 0;
        }
    }
    return ans;
}

bool OpenList::empty(){
    return smaller_f == -1;
}