#include "sudokuapp.hpp"
#include "sudokugenerator.hpp"

#include <iostream>
using namespace std;

using namespace genv;

const int tileSize = 50, tileNum = 81;

SudokuApp::SudokuApp(int szeles, int magas):
    App(szeles, magas)
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
                                               [&](){update();});
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


void SudokuApp::update()
{
    bool allValid = true;

    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            int ertek = tiles[row][col]->getErtek();
            sg.setCell(row, col, 0);

            // TODO: ezt csak annál kéne megváltoztatni, amelyiket átírtam (?)
            bool isValid = (ertek == 0 || sg.isValidMove(row, col, ertek));

            sg.setCell(row, col, ertek);
            tiles[row][col]->setValid(isValid);

            if (!isValid)
                allValid = false;
        }
    }

    if (allValid && sg.isFull())
    {
        std::cout << "nyert" << std::endl;
        // TODO: ide a victory screen vagy ilyesmi
    }
}









