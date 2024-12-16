//
// Created by User on 12/16/2024.
//

#ifndef A3_SUS_H
#define A3_SUS_H

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
using namespace std;


int t_p = 0;


template <typename T>
class SUS_Board: public Board<T>{
public:
    int score_p1 = 0, score_p2 = 0;

    SUS_Board() {
        this->rows = this->columns = 3;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = '.';
            }
        }
        this->n_moves = 0;
    }

    ~SUS_Board() {
        for (int i = 0; i < this->rows; i++) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

    bool update_board(int x, int y, T symbol) {
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != '.') {
            return false;
        }

        if (symbol == '.') {
            this->n_moves--;
            this->board[x][y] = '.';
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(symbol);
        }

        return true;
    }

    void display_board();
    int check_round();
    void update_score();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class SUS_Player : public Player<T> {
public:
    SUS_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class SUS_Random_Player : public RandomPlayer<T> {
public:
    SUS_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Display the board and the pieces on it
template <typename T>
void SUS_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(2) << this->board[i][j] << " | ";
        }
        cout << "\n-------------------";
    }
    cout << "\nplayer 1 score: "<< this->score_p1<<endl;
    cout <<"plyeer 2 score: "<<this->score_p2<<endl;

    cout << endl;
}

template <typename T>
int SUS_Board<T>::check_round() {
    int count = 0;
    string s1,s2;

    for (int i = 0; i < this->rows; i++) {
        s1={this->board[i][0],this->board[i][1],this->board[i][2]};
        if (s1=="SUS") {
            ++count;
        }
    }
    for (int i = 0; i < this->columns; i++) {
        s2={this->board[0][i],this->board[1][i],this->board[2][i]};
        if (s2=="SUS") {
            ++count;
        }
    }
    s1={this->board[0][0]  ,this->board[1][1] , this->board[2][2]};
    s2={this->board[0][2] , this->board[1][1] ,this->board[2][0]};
    if ( s1== "SUS"){
        ++count;
    }
    if(s2=="SUS"){
        count++;
    }


    return count;
}

template <typename T>
void SUS_Board<T>::update_score() {
    int n = check_round();
    if (this->n_moves % 2 == 1) {  // Player 1's turn (odd moves)
        this->score_p1 += (n - t_p);
        t_p = n;

    } else {  // Player 2's turn (even moves)
        this->score_p2 += (n - t_p);
        t_p = n;

    }
}


template <typename T>
bool SUS_Board<T>::is_win() {
    update_score();
    return this->n_moves == 9 && this->score_p1 != this->score_p2;
}

template <typename T>
bool SUS_Board<T>::is_draw() {
    return this->n_moves == 9 && !is_win();
}

template <typename T>
bool SUS_Board<T>::game_is_over() {
    return is_win() || is_draw();
}
//--------------------------------------

// Constructor for SUS_Player
template <typename T>
SUS_Player<T>::SUS_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void SUS_Player<T>::getmove(int& x, int& y) {

    cout << this->getname()<<"\nPlease enter your move (x y) between 0 and 2: ";
    cin >> x >> y;
}

// Constructor for SUS_Random_Player
template <typename T>
SUS_Random_Player<T>::SUS_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void SUS_Random_Player<T>::getmove(int& x, int& y) {

    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;

}

#endif //A3_SUS_H
