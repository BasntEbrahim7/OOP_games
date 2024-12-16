#ifndef _FOUR_IN_A_ROW_H_
#define _FOUR_IN_A_ROW_H_

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class FourInRowBoard : public Board<T> {
public:
    FourInRowBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class FourInRowPlayer : public Player<T> {
public:
    FourInRowPlayer(string name, T symbol);
    void getmove(int& x, int&y);
};

template <typename T>
class FourInRow_Random_Player : public RandomPlayer<T> {
public:
    FourInRow_Random_Player(T symbol);
    void getmove(int& x,int& y);
};

//--------------------------------------- IMPLEMENTATION

// Constructor for FourInRowBoard
template <typename T>
FourInRowBoard<T>::FourInRowBoard() {
    this->rows = 6;
    this->columns = 7;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool FourInRowBoard<T>::update_board(int x, int y, T symbol) {
    if (y < 0 || y >= this->columns) {
        return false;
    }

    for (int row = this->rows - 1; row >= 0; row--) {
        if (this->board[row][y] == ' ') {
            this->board[row][y] = toupper(symbol);
            this->n_moves++;
            return true;
        }
    }
    return false; // Column is full
}

template <typename T>
void FourInRowBoard<T>::display_board() {
    // Print column numbers
    for (int i = 0; i < this->columns; i++) {
        cout << "  " << i + 1 << " ";
    }
    cout << endl;

    // Print the board with grid lines
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            cout << "| " << this->board[i][j] << " ";
        }
        cout << "|" << endl;

    }
}

template <typename T>
bool FourInRowBoard<T>::is_win() {
    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->columns; col++) {
            if (this->board[row][col] != ' ' &&
                this->board[row][col] == this->board[row][col -1] &&
                this->board[row][col] == this->board[row][col - 2] &&
                this->board[row][col] == this->board[row][col - 3]) {
                return true;
            }
            if (this->board[row][col] != ' ' &&
                this->board[row][col] == this->board[row - 1][col] &&
                this->board[row][col] == this->board[row - 2][col] &&
                this->board[row][col] == this->board[row - 3][col]) {
                return true;
            }
            if (this->board[row][col] != ' ' &&
                this->board[row][col] == this->board[row - 1][col - 1] &&
                this->board[row][col] == this->board[row - 2][col - 2] &&
                this->board[row][col] == this->board[row - 3][col - 3]) {
                return true;
            }
            if (this->board[row][col] != ' ' &&
                this->board[row][col] == this->board[row - 1][col + 1] &&
                this->board[row][col] == this->board[row - 2][col + 2] &&
                this->board[row][col] == this->board[row - 3][col + 3]) {
                return true;
            }

        }
    }



    return false;
}

template <typename T>
bool FourInRowBoard<T>::is_draw() {
    return this->n_moves ==42 && !is_win();
}

template <typename T>
bool FourInRowBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for FourInRowPlayer
template <typename T>
FourInRowPlayer<T>::FourInRowPlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void FourInRowPlayer<T>::getmove(int& x, int& y) {
    cout <<this->getname()<< ",Please enter your column number: ";
    cin >> y;
    y--; // Convert to zero-based index
}

// Constructor for FourInRow_Random_Player
template <typename T>
FourInRow_Random_Player<T>::FourInRow_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); // Seed RNG
}

template <typename T>
void FourInRow_Random_Player<T>::getmove(int& x, int&y) {
    y = rand() % this->dimension; // Random number between 0 and 6
}

#endif // _FOUR_IN_A_ROW_H_