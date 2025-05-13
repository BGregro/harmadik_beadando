#include "sudokugame.hpp"

using namespace std;

const int gameSize = 9;

SudokuGame::SudokuGame()
{
    for (int i = 0; i < gameSize; ++i)
        board.push_back({0,0,0,0,0,0,0,0,0});

}

bool SudokuGame::isValidMove(int row, int col, int num) {
    // sor, oszlop check
    for (int i = 0; i < gameSize; i++) {
        if (board[row][i] == num || board[i][col] == num)
            return false;
    }

    // 3x3 check
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (board[i][j] == num)
                return false;
        }
    }
    return true;
}

bool SudokuGame::isFull() const
{
    for (int i = 0; i < gameSize; i++)
        for (int j = 0; j < gameSize; j++)
            if (board[i][j] == 0)
                return false;

    return true;
}

void SudokuGame::update()
{

}
