#include <bits/stdc++.h>
#pragma once
#include <array>
#include <vector>
#include <memory>
#include <queue>
#include <unordered_set>
#include <cmath>
#include <algorithm>
using namespace std;

class puzzleState{
public:
    array<int, 9> puzzle;
    int zero;
    int g;
    
    //find 0
    puzzleState(array<int, 9>& s, int cur_g=0):puzzle(s), g(cur_g){
        for(int i=0; i<9; i++){
            if(puzzle[i] == 0){
                zero=i;
                break;
            }
        }
    }

    //set goal
    bool puzzleGoal() const{
        array<int, 9> goal{1, 2, 3, 4, 5, 6, 7, 8, 0};
        return puzzle==goal;
    }
    
    //expened puzzle tree
    vector<puzzleState> expand(){
        int dx[4]={-1, 1 ,0 ,0};//up, down
        int dy[4]={0, 0, -1, 1};//left, right
        
        vector<puzzleState> children;
        int x=zero/3;
        int y=zero%3;
        
        for(int i=0; i<4; i++){
            int nx = x+dx[i];
            int ny = y+dy[i];
            if(nx<0 || nx>=3 || ny<0 || ny>=3) continue;
            int next_zero = nx*3+ny;
            array<int, 9> next_state = puzzle;
            swap(next_state[next_zero], next_state[zero]);
            children.emplace_back(next_state, g+1);
        }
        return children;
    }

    //hash
    struct hasher{
        size_t operator()(const puzzleState& s)const noexcept{
            size_t h = 0;
            for(int v:s.puzzle){
                h = h*10+v;
            }
            return h;
        }
    };
    bool operator==(const puzzleState& other)const noexcept{
        return puzzle==other.puzzle;
    }
};

//heuristic
int misplaced(const puzzleState& s){
    int m=0;
    for (int i=0; i<9; i++){
        if(s.puzzle[i]!=0 && s.puzzle[i]!=i+1){
            m++;
        }
    }
    return m;
}
int manhattan(const puzzleState& s){
    int d=0;
    for(int i=0; i<9; i++){
        int val=s.puzzle[i];
        if(val!=0){
            val--;
            d += abs(i/3-val/3)+abs(i%3-val%3);
        }
    }
    return d;
}
int heuristic(const puzzleState& s, int a){
    switch(a){
        case 1: return 0;//Uniform Cost Search
        case 2: return misplaced(s);//A* Misplaced Tile heuristic
        case 3: return manhattan(s);//A* Manhattan Distance heuristic
        default:return 0;
    }
}

//tree node
struct node{
    puzzleState state;
    int h;
    int order;
    shared_ptr<node> parent;
    node(const puzzleState& s, int cur_h, int cur_o, shared_ptr<node> p=nullptr): state(s), h(cur_h), order(cur_o), parent(std::move(p)){}
    int f(){
        return state.g+h;//f=g+h
    }
};

struct nodeCompare{
    bool operator()(const shared_ptr<node>& a, const shared_ptr<node>& b)const{
        if (a->f() != b->f()){
            return a->f()>b->f();
        }
        return a->order > b->order;
    }
};

struct searchResult{
    bool solved=false;
    int depth = 0;
    int nodesExpand = 0;
    int maxQueue = 0;
    vector<array<int, 9>> trace_puzzle;
    vector<int>   g;
    vector<int>   h;
};

//search
searchResult search(const puzzleState& start, int a){
    using nodePtr = shared_ptr<node>;
    priority_queue<nodePtr, vector<nodePtr>, nodeCompare> open;
    unordered_set<puzzleState, puzzleState::hasher> closed;
    
    int next_oder=0;
    nodePtr startN = make_shared<node>(start, heuristic(start, a), next_oder++);
    open.push(startN);

    searchResult result;
    result.maxQueue=1;

    while(!open.empty()){
        nodePtr current = open.top();
        open.pop();

        result.trace_puzzle.push_back(current->state.puzzle);
        result.g.push_back(current->state.g);
        result.h.push_back(current->h);

        if(current->state.puzzleGoal()){
            result.solved=true;
            result.depth =current->state.g;
            return result;
        }
        result.nodesExpand++;
        closed.insert(current->state);

        for(puzzleState& childState:current->state.expand()){
            if(closed.find(childState) != closed.end()) continue;
            nodePtr child = make_shared<node>(childState, heuristic(childState, a), next_oder++, current);
            open.push(child);
        }
        if(static_cast<int>(open.size()) > result.maxQueue){
            result.maxQueue = static_cast<int>(open.size());
        }
    }
    return result;
}
