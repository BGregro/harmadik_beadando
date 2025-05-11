#include "sudokuapp.hpp"

using namespace genv;

const int tileSize = 50;

SudokuApp::SudokuApp(int szeles, int magas):
    App(szeles, magas)
{
    // 9x9-es palyahoz widgetek letrehozasa
    for (int i = 0; i < 81; ++i)
    {
        int row = i/9;
        int col = i%9;

        int x = (50+col) + tileSize*col + (col/3 * 3); // minden 3. tile utan vastagabb vonal
        int y = (50+row) + tileSize*row + (row/3 * 3);

        tiles.push_back(new SudokuNumber(this, x, y, tileSize, tileSize));

        tiles[i]->draw();
    }

    for (Widget *w : widgets)
        w->draw();

    gout << refresh;
}
