//
//  main.cpp
//  CS205_project1
//
//  Created by Pei-Yun Jan on 2025/4/19.
//

#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include "eight_puzzle.hpp"
using namespace std;

//default a 8 puzzle
array<int, 9> defaultPuzzle(){
    return{1, 2, 3, 4, 5, 6, 7, 8, 0};
}

//user input a 8 puzzle
array<int, 9> inputPuzzle(){
    array<int,9> board;
    cout<<"Enter your puzzle, using a zero to represent the blank.\n"
          "Enter the puzzle delimiting the numbers with a space.\n"
          "RET only when finished.\n\n";
    cout<<"Enter the first row: ";
    for(int i=0; i<3; i++){
        cin>>board[i];
    }
    cout<<"Enter the second row: ";
    for(int i=3; i<6; i++){
        cin>>board[i];
    }
    cout<<"Enter the third row: ";
    for(int i=6; i<9; i++){
        cin>>board[i];
    }
    return board;
}

void printBoard(array<int,9>& b){
    for(int i=0; i<9; i++){
        if(i%3==0){
            cout<<"["<<b[i]<<", ";
        }
        else if(i%3==2){
            cout<<b[i]<<"]\n";
        }
        else{
            cout<<b[i]<<", ";
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int welcome_choose, algorithm_choose;
    
    cout<<"Welcome to my 8‑Puzzle Solver. Type '1' to use a default puzzle, or '2' to create your own.\n";
    cin>>welcome_choose;
    array<int, 9> start_puzzle=(welcome_choose==1 ? defaultPuzzle(): inputPuzzle());
    
    cout<<"Select algorithm. (1) for Uniform Cost Search, (2) for the Misplaced Tile Heuristic, or (3) the Manhattan Distance Heuristic.\n";
    cin>>algorithm_choose;
    
    searchResult result=search(puzzleState(start_puzzle), algorithm_choose);
        
    
    for(size_t i=0; i<result.trace_puzzle.size(); i++){
        cout<<"The best state to expand with a g(n) = "<<result.g[i]<<" and h(n) = "<<result.h[i]<<" is…\n";
        printBoard(result.trace_puzzle[i]);
    }
    if(result.solved){
        cout<<"\nGoal state!\n\n"
            <<"Solution depth was "<<result.depth<<"\n"
            <<"Number of nodes expanded: "<<result.nodesExpand<<"\n"
            <<"Max queue size: "<<result.maxQueue<<"\n\n";
    }
    else{
        cout<<"Failure no solution found.\n";
    }
    
    return 0;
}
