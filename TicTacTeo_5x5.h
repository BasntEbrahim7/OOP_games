//
// Created by User on 12/16/2024.
//

#ifndef A3_TICTACTEO_5X5_H
#define A3_TICTACTEO_5X5_H


#include <bits/stdc++.h>
#include "BoardGame_Classes.h"

int t_p1=0;int t_p2=0;
using namespace std;
template <typename T>
class Board_5x5: public Board<T>{
private:
    const char EMPTY = '.';
    const char PLAYER_X = 'X';
    const char PLAYER_O = 'O';

public:
    int score_p1=0,score_p2=0;
    Board_5x5() {
        this->rows = this->columns = 5;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = EMPTY;
            }
        }
        this->n_moves = 0;
    }

    ~Board_5x5() { // Proper cleanup
        for (int i = 0; i < this->rows; i++) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }
    bool update_board (int x , int y , T symbol);
    void display_board (){
        for (int i = 0; i < this->rows; i++) {
            cout << "\n| ";
            for (int j = 0; j < this->columns; j++) {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " |";
            }
            cout << "\n----------------------------------------------------------";
        }
        cout << endl;
    }
    int check_round(){
        int count = 0;
        char player  = ( this->n_moves%2==0)? 'O':'X';
        // Check rows and columns
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j <= 5 - 3; ++j) {
                // Horizontal
                if (this->board[i][j] == player && this->board[i][j + 1] == player && this->board[i][j + 2] == player)
                    ++count;
                // Vertical
                if (this->board[j][i] == player && this->board[j + 1][i] == player && this->board[j + 2][i] == player)
                    ++count;
            }
        }

        // Check diagonals
        for (int i = 0; i <= 5 - 3; ++i) {
            for (int j = 0; j <= 5 - 3; ++j) {
                // Top-left to bottom-right
                if (this->board[i][j] == player && this->board[i + 1][j + 1] == player && this->board[i + 2][j + 2] == player)
                    ++count;
                // Bottom-left to top-right
                if (this->board[i + 2][j] == player && this->board[i + 1][j + 1] == player && this->board[i][j + 2] == player)
                    ++count;
            }
        }

        return count;
    }
    void update_score(){
        int n=check_round();
        if (this->n_moves!=0){
            this->score_p1+=(n-t_p1);
            t_p1=n;
        }
        else{
            this->score_p2+=(n-t_p2);
            t_p2=n;
        }
    }

    bool is_win(){

        update_score();
        if (this->n_moves==24) {
            if (this->score_p2 != this->score_p1)
                return true;
            return false;
        }
        return false;

    }
    bool is_draw() {
        return (this->n_moves == 24 && !is_win());
    }


    bool game_is_over() {
        return is_win() || is_draw();
    }


};


template <typename T>
bool Board_5x5<T>::update_board (int x , int y , T symbol){
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == EMPTY|| symbol == EMPTY)) {
        if (symbol == EMPTY){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(symbol);
        }

        return true;
    }
    return false;
}
//________________________________________________________________________________
template <typename T>
class Player_5x5 : public Player<T> {
public:
    Player_5x5 (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Random_Player_5x5 : public RandomPlayer<T>{
public:
    Random_Player_5x5 (T symbol);
    void getmove(int &x, int &y) ;
};
template <typename T>
Player_5x5<T>::Player_5x5(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Player_5x5<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
Random_Player_5x5<T>::Random_Player_5x5(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Random_Player_5x5<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 5
    y = rand() % this->dimension;
}


#endif //A3_TICTACTEO_5X5_H
