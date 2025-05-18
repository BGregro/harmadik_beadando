#include "sudokugame.hpp"

using namespace std;

const int gameSize = 9;

SudokuGame::SudokuGame()
{
    for (int i = 0; i < gameSize; ++i)
        board.push_back({0,0,0,0,0,0,0,0,0});
}


bool SudokuGame::isValidMove(int row, int col, int num)
{
    // sor, oszlop check
    for (int i = 0; i < gameSize; i++)
    {
        if (board[row][i] == num || board[i][col] == num)
            return false;
    }

    // 3x3 check
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = startRow; i < startRow + 3; i++)
    {
        for (int j = startCol; j < startCol + 3; j++)
        {
            if (board[i][j] == num)
                return false;
        }
    }
    return true;
}

// visszaadja az olyan összes mező koordináta párját, aminek az értéke ütközik egy másikkal
vector<pair<int, int>> SudokuGame::checkValid() const
{
    vector<pair<int, int>> conflicts;

    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            int val = board[row][col];
            if (val == 0) continue;

            // sor ellenőrzése
            for (int c = 0; c < 9; ++c)
            {
                if (c != col && board[row][c] == val)
                {
                    conflicts.push_back({row, col});
                    conflicts.push_back({row, c});
                }
            }

            // oszlop ellenőrzése
            for (int r = 0; r < 9; ++r)
            {
                if (r != row && board[r][col] == val)
                {
                    conflicts.push_back({row, col});
                    conflicts.push_back({r, col});
                }
            }

            // block ellenőrzése
            int startRow = row - row % 3;
            int startCol = col - col % 3;
            for (int r = startRow; r < startRow + 3; ++r)
            {
                for (int c = startCol; c < startCol + 3; ++c)
                {
                    if ((r != row || c != col) && board[r][c] == val)
                    {
                        conflicts.push_back({row, col});
                        conflicts.push_back({r, c});
                    }
                }
            }
        }
    }

    return conflicts;
}

// ellenőrzi, hogy tele van-e a pálya
bool SudokuGame::isFull() const
{
    for (int i = 0; i < gameSize; i++)
        for (int j = 0; j < gameSize; j++)
            if (board[i][j] == 0)
                return false;

    return true;
}

void SudokuGame::setCell(int row, int col, int num)
{
    board[row][col] = num;
}

int SudokuGame::getCell(int row, int col)
{
    return board[row][col];
}
