#ifndef SUDOKUGAME_HPP
#define SUDOKUGAME_HPP

#include <vector>

class SudokuGame
{
protected:
    std::vector<std::vector<int>> board;
public:
    SudokuGame();

    void setCell(int row, int col, int num);

    int getCell(int, int);

    bool isValidMove(int row, int col, int num);
    bool isFull() const;
};

#endif // SUDOKUGAME_HPP
