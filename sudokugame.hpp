#ifndef SUDOKUGAME_HPP
#define SUDOKUGAME_HPP

#include <vector>

class SudokuGame
{
protected:
    std::vector<std::vector<int>> board;
public:
    SudokuGame();

    std::vector<std::pair<int, int>> checkValid() const;

    bool isValidMove(int row, int col, int num);
    bool isFull() const;

    void setCell(int row, int col, int num);
    int getCell(int, int);
};

#endif // SUDOKUGAME_HPP
