#include "sudokuapp.hpp"
#include "sudokugenerator.hpp"

#include <iostream>
using namespace std;

using namespace genv;

const int tileSize = 50;

SudokuApp::SudokuApp(int szeles, int magas):
    App(szeles, magas), allValid(true)
{

    tiles.resize(9, std::vector<SudokuNumber*>(9, nullptr)); // a 2D-s vektor inicializálása

    // 9x9-es palyahoz widgetek letrehozasa
    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            int x = (25+col) + tileSize*col + (col/3 * 3);
            int y = (25+row) + tileSize*row + (row/3 * 3);

            tiles[row][col] = new SudokuNumber(this, x, y, tileSize, tileSize, row, col, 0,
                                               [&](int row, int col){update(row, col);});
        }

    }

    generateBoard(Difficulty::Easy);

    vector<string> difficulties = {"Easy", "Medium", "Hard"};
    difficulty = new LegorduloWidget(this, 500, 50, 3, difficulties);

    generate = new Gomb(this, 500, 150, 100, 50, "Generálás", [&](){generateBoard(getDifficulty());});


    for (Widget *w : widgets)
        w->draw();

    gout << refresh;
}

Difficulty SudokuApp::getDifficulty()
{
    string diff = difficulty->getSelected();

    if (diff == "Easy")
        return Difficulty::Easy;
    else if (diff == "Medium")
        return Difficulty::Medium;
    else if (diff == "Hard")
        return Difficulty::Hard;
    else
        return Difficulty::Medium;
}

// default értékek visszaállítása
void SudokuApp::resetTiles()
{
    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            tiles[row][col]->setErtek(0);
            tiles[row][col]->setLocked(false);
            tiles[row][col]->setValid(true);
        }
    }
}

void SudokuApp::generateBoard(Difficulty diff)
{
    sg = SudokuGenerator::generate(diff);

    resetTiles();

    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            int num = sg.getCell(row, col);
            if (num > 0)
            {
                tiles[row][col]->setErtek(num);
                tiles[row][col]->setLocked(true); // a generált pálya számait ne lehessen változtatni

            }
        }
    }
}

void SudokuApp::checkValid(int row, int col)
{
    int ertek = sg.getCell(row, col);
    tiles[row][col]->setErtek(0); // hogy magát ne ellenőrizze

    allValid = true;

    // azonos sor ellenőrzése
    for (int c = 0; c < 9; ++c)
    {
        if (tiles[row][c]->getErtek() == ertek)
        {
            tiles[row][c]->setValid(false);
            allValid = false;
        }
        else
            tiles[row][c]->setValid(true);
    }

    // azonos oszlop ellenőrzése
    for (int r = 0; r < 9; ++r)
    {
        if (tiles[r][col]->getErtek() == ertek)
        {
            tiles[r][col]->setValid(false);
            allValid = false;
        }
        else
            tiles[r][col]->setValid(true);
    }

    // azonos blokk ellenőrzése
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int r = startRow; r < startRow + 3; ++r)
    {
        for (int c = startCol; c < startCol + 3; ++c)
        {
            if (tiles[r][c]->getErtek() == ertek)
            {
                tiles[r][c]->setValid(false);
                allValid = false;
            }
            else
                tiles[r][c]->setValid(true);
        }
    }

    tiles[row][col]->setErtek(ertek); // érték visszaállítása
}

void SudokuApp::update(int row, int col)
{
    // board frissítése az aktuális értékkel
    sg.setCell(row, col, tiles[row][col]->getErtek());

    checkValid(row, col);

    if (allValid && sg.isFull())
    {
        std::cout << "nyert" << std::endl;
        // TODO: ide a victory screen vagy ilyesmi
    }
}









