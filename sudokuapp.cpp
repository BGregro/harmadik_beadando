#include "sudokuapp.hpp"
#include "sudokugenerator.hpp"

#include <iostream>
using namespace std;

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

        int x = (25+col) + tileSize*col + (col/3 * 3); // minden 3. tile utan vastagabb vonal
        int y = (25+row) + tileSize*row + (row/3 * 3);

        tiles.push_back(new SudokuNumber(this, x, y, tileSize, tileSize, row, col, 0,
                                         [&](){update();}));

        tiles[i]->draw();
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
    for (int i = 0; i < tileNum; ++i)
    {
        tiles[i]->setErtek(0);
        tiles[i]->setLocked(false);
        tiles[i]->setValid(true);
    }
}

void SudokuApp::generateBoard(Difficulty diff)
{
    sg = SudokuGenerator::generate(diff);

    resetTiles();

    for (int i = 0; i < tileNum; ++i)
    {
        int num = sg.getCell(tiles[i]->getRow(), tiles[i]->getCol());

        if (num > 0)
        {
            tiles[i]->setErtek(num);
            tiles[i]->setLocked(true); // a generált pálya számait ne lehessen változtatni
        }
    }
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
        cout << "nyert" << endl;
        // TODO: ide a victory screen vagy ilyesmi
    }
}








