#include "sudokuapp.hpp"

SudokuApp::SudokuApp(int szeles, int magas):
    App(szeles, magas)
{
    // 9x9-es palyahoz widgetek letrehozasa
    for (int i = 0; i < 81; ++i)
    {
        int row = i/9;
        int columb = i%9;
        // tiles.push_back();
    }
}
