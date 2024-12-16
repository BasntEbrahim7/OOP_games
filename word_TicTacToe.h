#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <ctime>
#include "BoardGame_Classes.h"

using namespace std;

template<typename T>
class X4_Board : public Board<T> {  // Ensure that Board<T> is defined elsewhere
private:
    int rows, columns, n_moves;
    T **board;
    unordered_set<string> words; // Dictionary of valid words

public:
    unordered_set<string> load_dictionary(const string &filename);
    bool is_valid_word(const string &word, const unordered_set<string> &words);
    X4_Board();
    ~X4_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

// Constructor for X_Board
template<typename T>
unordered_set<string> X4_Board<T>::load_dictionary(const string &filename) {
    unordered_set<string> words;
    ifstream file(filename);
    string word;
    while (file >> word) {
        words.insert(word);
    }
    return words;
}

template<typename T>
bool X4_Board<T>::is_valid_word(const string &word, const unordered_set<string> &words) {
    return words.find(word) != words.end();
}

template<typename T>
X4_Board<T>::X4_Board() {
    this->rows = this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = '-';
        }
    }
    ifstream file("dic.txt");
    if (file.is_open()) {
        string word;
        while (file >> word) {
            words.insert(word);
        }
        file.close();
    }
    this->n_moves = 0;
}


// Destructor for X_Board
template<typename T>
X4_Board<T>::~X4_Board() {
    for (int i = 0; i < rows; i++) {
        delete[] board[i];
    }
    delete[] board;
}

template<typename T>
bool X4_Board<T>::update_board(int x, int y, T mark) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != '-') {
        return false;
    }
    this->n_moves++;
    this->board[x][y] = toupper(mark);  // Use symbol instead of 'move'
    return true;
}

// Display the current state of the board
template<typename T>
void X4_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ") " << (this->board[i][j] ? this->board[i][j] : ' ') << " | ";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Check if there is a winner
template<typename T>
bool X4_Board<T>::is_win() {
    for (int i = 0; i < rows; i++) {
        string row = "", col = "";
        for (int j = 0; j < columns; j++) {
            row += board[i][j];
            col += board[j][i];
        }
        if (is_valid_word(row, words) || is_valid_word(col, words)) {
            return true;
        }
    }

    // Check diagonals
    string diag1 = "", diag2 = "";
    for (int i = 0; i < rows; i++) {
        diag1 += board[i][i];
        diag2 += board[i][rows - i - 1];
    }
    return is_valid_word(diag1, words) || is_valid_word(diag2, words);
}

// Check if the game is a draw
template<typename T>
bool X4_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

// Check if the game is over
template<typename T>
bool X4_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template<typename T>
class pb4_Player : public Player<T> {
public:
    pb4_Player(string name, T symbol);

    void getmove(int &x, int &y);
};
// Constructor for pb4_Player
template<typename T>
pb4_Player<T>::pb4_Player(string name, T symbol) : Player<T>(name, symbol)
{

}

template<typename T>
void pb4_Player<T>::getmove(int &x, int &y) {
    cout <<this->getname()<<":" <<"\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    char c ;
    cin >> x >> y ;
    cout << "\nPlease enter your char only one char";
    cin>>c;
    this->symbol = c ;  // Human player enters their symbol
}

template<typename T>
class pb4_Random_Player : public RandomPlayer<T> {
private:
    char ch;
public:
    pb4_Random_Player(T symbol);
    void getmove(int &x, int &y);
};

template<typename T>
pb4_Random_Player<T>::pb4_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

// Get random move
template<typename T>
void pb4_Random_Player<T>::getmove(int &x, int &y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    this->ch = 'A' + (rand() % 26); // Random uppercase letter
}