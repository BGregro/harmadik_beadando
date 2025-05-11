#ifndef SUDOKUAPP_HPP
#define SUDOKUAPP_HPP

#include "app.hpp"
#include "sudokunumber.hpp"

class SudokuApp : public App
{
public:
    SudokuApp(int, int);
protected:
    std::vector<SudokuNumber*> tiles;
};

#endif // SUDOKUAPP_HPP
