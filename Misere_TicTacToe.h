//
// Created by User on 12/16/2024.
//

#ifndef A3_MISERE_TICTACTOE_H
#define A3_MISERE_TICTACTOE_H

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"

using namespace std;
template <typename T>
class Misere_Board: public Board<T>{
private:
    const char EMPTY = '.';
    const char PLAYER_X = 'X';
    const char PLAYER_O = 'O';

public:
    Misere_Board() {
        this->rows = this->columns = 3;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = EMPTY;
            }
        }
        this->n_moves = 0;
    }

    ~Misere_Board() { // Proper cleanup
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
    bool is_win() {
        char player  = ( this->n_moves%2==0)? 'O':'X';
        // Check rows and columns
        for (int i = 0; i < 3; ++i) {
            // Horizontal
            if (this->board[i][0] == player && this->board[i][1] == player && this->board[i][2] == player){
                return true;
            }
            // Vertical
            if (this->board[0][i] == player && this->board[1][i] == player && this->board[2][i] == player)
                return true;
        }

        // Check diagonal
        if (this->board[0][0] == player && this->board[1][1] == player && this->board[2][2] == player)
            return true;

        return false;
    }



    bool is_draw() {
        return (this->n_moves == 9 && !is_win());
    }


    bool game_is_over() {
        return is_win() || is_draw();
    }


};


template <typename T>
bool Misere_Board<T>::update_board (int x , int y , T symbol){
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
class Misere_Player : public Player<T> {
public:
    Misere_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Misere_Random_Player : public RandomPlayer<T>{
public:
    Misere_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};
template <typename T>
Misere_Player<T>::Misere_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Misere_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
Misere_Random_Player<T>::Misere_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Misere_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 5
    y = rand() % this->dimension;
}


#endif //A3_MISERE_TICTACTOE_H
