#include "sudokuapp.hpp"

using namespace genv;

const int tileSize = 50, tileNum = 81;

SudokuApp::SudokuApp(int szeles, int magas):
    App(szeles, magas)
{
    // 9x9-es palyahoz widgetek letrehozasa
    for (int i = 0; i < tileNum; ++i)
    {
        int row = i/9;
        int col = i%9;

        int x = (50+col) + tileSize*col + (col/3 * 3); // minden 3. tile utan vastagabb vonal
        int y = (50+row) + tileSize*row + (row/3 * 3);

        tiles.push_back(new SudokuNumber(this, x, y, tileSize, tileSize, row, col,
                                         [&](){update();}));

        tiles[i]->draw();
    }

    for (Widget *w : widgets)
        w->draw();

    gout << refresh;
}

void SudokuApp::update()
{
    bool allValid = true;

    for (int i = 0; i < tileNum; ++i)
    {
        int row = tiles[i]->getRow();
        int col = tiles[i]->getCol();
        int ertek = tiles[i]->getErtek();

        // TODO: ezt így vagy máshogy lehet?
        sg.setCell(row, col, 0);

        // TODO: ezt csak annál kéne megváltoztatni, amelyiket átírtam (?)
        bool isValid = (ertek == 0 || sg.isValidMove(row, col, ertek));

        sg.setCell(row, col, ertek);

        tiles[i]->setValid(isValid);

        if (!isValid)
            allValid = false;
    }

    if (allValid && sg.isFull())
    {
        // TODO: ide a victory screen vagy ilyesmit
    }
}








