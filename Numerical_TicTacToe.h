//
// Created by User on 12/16/2024.
//

#ifndef A3_NUMERICAL_TICTACTOE_H
#define A3_NUMERICAL_TICTACTOE_H


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm> // for std::find

using namespace std;

//--------------------------------------- CLASS DEFINITIONS

#include "BoardGame_Classes.h"

template <typename T>
class NumericalBoard : public Board<T> {
    vector<T> usedNumbers; // Track used numbers

public:
    NumericalBoard();
    ~NumericalBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    bool is_number_used(T number); // Check if a number is already used
};

template <typename T>
class NumericalPlayer : public Player<T> {
    vector<T> availableNumbers; // Track numbers a player can use

public:
    NumericalPlayer(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class TicTacToe_Random_Player : public RandomPlayer<T> {
    vector<T> availableNumbers;

public:
    TicTacToe_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

// Constructor for NumericalBoard
template <typename T>
NumericalBoard<T>::NumericalBoard() {
    this->rows = this->columns = 3;
    this->n_moves = 0;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[this->columns]();
        for (int j = 0; j < this->columns; ++j) {
            this->board[i][j] = 0;

        }
    }
}

// Destructor for NumericalBoard
template <typename T>
NumericalBoard<T>::~NumericalBoard() {
    for (int i = 0; i < this->rows; ++i) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

// Check if a number is already used
template <typename T>
bool NumericalBoard<T>::is_number_used(T number) {
    return find(usedNumbers.begin(), usedNumbers.end(), number) != usedNumbers.end();
}

// Update the board with a move
template <typename T>
bool NumericalBoard<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0 && !is_number_used(symbol)) {
        this->board[x][y] = symbol;
        usedNumbers.push_back(symbol); // Mark the number as used
        this->n_moves++;
        return true;
    }
    return false;
}

// Display the board
template <typename T>
void NumericalBoard<T>::display_board() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            cout << "| " << setw(2) << this->board[i][j] << " ";
        }
        cout << "|\n";
    }
    cout << "---------------------\n";
}

// Check win condition
template <typename T>
bool NumericalBoard<T>::is_win() {
    for (int i = 0; i < this->rows; ++i) {
        if (this->board[i][0] + this->board[i][1] + this->board[i][2] == 15 || // Rows
            this->board[0][i] + this->board[1][i] + this->board[2][i] == 15) { // Columns
            return true;
        }
    }
    if (this->board[0][0] + this->board[1][1] + this->board[2][2] == 15 ||    // Diagonals
        this->board[0][2] + this->board[1][1] + this->board[2][0] == 15) {
        return true;
    }
    return false;
}

// Check draw condition
template <typename T>
bool NumericalBoard<T>::is_draw() {
    return this->n_moves == 9 && !is_win();
}

// Check if the game is over
template <typename T>
bool NumericalBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for NumericalPlayer
template <typename T>
NumericalPlayer<T>::NumericalPlayer(string name, T symbol) : Player<T>(name, symbol) {
    if (symbol % 2 != 0) {
        availableNumbers = {1, 3, 5, 7, 9};
    } else { // Even numbers (Player 2)
        availableNumbers = {2, 4, 6, 8};
    }
}

// Get move for a NumericalPlayer
template <typename T>
void NumericalPlayer<T>::getmove(int& x, int& y) {
    bool validMove = false;
    while (!validMove) {
        cout << this->getname() << ", enter your move (row and column): ";
        cin >> x >> y;

        cout << "Enter a number: ";
        cin >> this->symbol;

        if (find(availableNumbers.begin(), availableNumbers.end(), this->symbol) != availableNumbers.end()) {
            validMove = true;
        } else {
            cout << "Invalid number or move. Try again.\n";
        }
    }
}

// Constructor for X_O_Random_Player
template <typename T>
TicTacToe_Random_Player<T>::TicTacToe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    srand(static_cast<unsigned int>(time(0)));
    this->dimension = 3;
    this->name = "Random Computer Player";
    if (symbol % 2 != 0) { // Odd numbers (Player 1)
        availableNumbers = {1, 3, 5, 7, 9};
    } else { // Even numbers (Player 2)
        availableNumbers = {2, 4, 6, 8};
    }

}

// Get move for X_O_Random_Player
template <typename T>
void TicTacToe_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    this->symbol = availableNumbers[rand() % availableNumbers.size()];

}


#endif //A3_NUMERICAL_TICTACTOE_H
