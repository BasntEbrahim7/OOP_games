//
// Created by User on 12/16/2024.
//

#ifndef A3_ULTIMATE_TICTACTOE_H
#define A3_ULTIMATE_TICTACTOE_H


#include "BoardGame_Classes.h"
#include<vector>

template <typename T>
class X9_O9_Board:public Board<T> {

public:
    X9_O9_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool check_small_board(int X_startFrom, int Y_startFrom) ;
    bool check_big_board();
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

    ~X9_O9_Board(){
        // Proper cleanup
        for (int i = 0; i < this->rows; i++) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }
private:
    vector<vector<pair<bool, char>>> B;
    bool is_vaild(int x , int y );
};

template <typename T>
class X9_O9_Player : public Player<T> {
public:
    X9_O9_Player (string name, T symbol);
    void getmove(int& x, int& y) ;
};

template <typename T>
class X9_O9_Random_Player : public RandomPlayer<T>{
public:
    X9_O9_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};
//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;
template <typename T>
X9_O9_Board<T>::X9_O9_Board() {
    this->rows = this->columns = 9;


    // Initialize 3x3 big board
    for (int i = 0; i < 3; i++) {
        vector<pair<bool, char>> row;
        for (int j = 0; j < 3; ++j) {
            row.emplace_back(false, '-');
        }
        B.push_back(row);
    }

    // Initialize 9x9 board
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = '-';
        }
    }

    this->n_moves = 0;
}
template<typename T>
bool X9_O9_Board<T>::is_vaild(int x , int y ){
    int board_x = x / 3, board_y = y / 3;
    return !B[board_x][board_y].first;
}
template <typename T>
bool X9_O9_Board<T>::update_board(int x, int y, T mark) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || (this->board[x][y] != '-')) {
        return false;
    }

    int board_x = x / 3, board_y = y / 3;
    if(!is_vaild(x, y)){
        return false;
    }

    this->board[x][y] = toupper(mark);
    this->n_moves++;

    // Update the small board if there is a winner
    if(check_small_board(board_x * 3, board_y * 3)){
        B[board_x][board_y] = {true, mark};
    }


    return true;
}

template <typename T>
void X9_O9_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n ||";
        for (int j = 0; j < this->columns; j++) {
            if ((j+1)%3==0&&j!=0){
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " ||";
            }
            else
            {cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " |";
            }
        }
        if ((i+1)%3==0&&i!=0){
            cout << "\n   -------------------------  ---------------------------  -------------------------";
            //cout<<"\n   ------------   ------------  -------------";
        }
        else cout<<endl;

    }
    cout << endl;
}

template <typename T>
bool X9_O9_Board<T>:: check_small_board(int X_startFrom, int Y_startFrom) {
    for(int i = X_startFrom; i < X_startFrom + 3; i++){
        if(this->board[i][Y_startFrom] == this->board[i][Y_startFrom+1] &&
           this->board[i][Y_startFrom+1] == this->board[i][Y_startFrom+2] &&
           this->board[i][Y_startFrom] != '-'){
            return true;
        }
    }
    for (int j = Y_startFrom; j < Y_startFrom + 3; ++j) {
        if (this->board[X_startFrom][j] == this->board[X_startFrom + 1][j] &&
            this->board[X_startFrom + 1][j] == this->board[X_startFrom + 2][j] &&
            this->board[X_startFrom][j] != '-') {
            return true;
        }
    }

    if (this->board[X_startFrom][Y_startFrom] == this->board[X_startFrom + 1][Y_startFrom + 1] &&
        this->board[X_startFrom + 1][Y_startFrom + 1] == this->board[X_startFrom + 2][Y_startFrom + 2] &&
        this->board[X_startFrom][Y_startFrom] != '-') {
        return true;
    }

    if (this->board[X_startFrom][Y_startFrom + 2] == this->board[X_startFrom + 1][Y_startFrom + 1] &&
        this->board[X_startFrom + 1][Y_startFrom + 1] == this->board[X_startFrom + 2][Y_startFrom] &&
        this->board[X_startFrom][Y_startFrom + 2] != '-') {
        return true;
    }

    return false;
}

template <typename T>
bool X9_O9_Board<T>:: check_big_board(){
    for (int i = 0; i < 3; i++) {
        if ((B[i][0].first && B[i][1].first && B[i][2].first && B[i][0].second == B[i][1].second &&
             B[i][1].second == B[i][2].second) ||
            (B[0][i].first && B[1][i].first && B[2][i].first && B[0][i].second == B[1][i].second &&
             B[1][i].second == B[2][i].second)) {
            return true;
        }
    }

    if ((B[0][0].first && B[1][1].first && B[2][2].first && B[0][0].second == B[1][1].second &&
         B[1][1].second == B[2][2].second) ||
        (B[0][2].first && B[1][1].first && B[2][0].first && B[0][2].second == B[1][1].second &&
         B[1][1].second == B[2][0].second)) {
        return true;
    }

    return false;
}

// Returns true if there is any winner
template <typename T>
bool X9_O9_Board<T>::is_win() {
    return check_big_board();
}

// Return true if 9 moves are done and no winner
template <typename T>
bool X9_O9_Board<T>::is_draw() {
    return (this->n_moves == 9*9 && !is_win());
}

template <typename T>
bool X9_O9_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X9_O9_Player
template <typename T>
X9_O9_Player<T>::X9_O9_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X9_O9_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 8) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X9_O9_Random_Player
template <typename T>
X9_O9_Random_Player<T>::X9_O9_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void X9_O9_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}



#endif //A3_ULTIMATE_TICTACTOE_H
