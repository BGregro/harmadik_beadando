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

    // generateBoard(Difficulty::Easy);

    vector<string> difficulties = {"Easy", "Medium", "Hard"};
    difficulty = new LegorduloWidget(this, 500, 50, 3, difficulties);

    ujJatek = new Gomb(this, 500, 150, 120, 50, "New Game",
                       [&](){generateBoard(getDifficulty());});

    reset = new Gomb(this, 500, 210, 120, 50, "Reset Game",
                     [&](){sudokuGame = generated;
                           setBoard(sudokuGame);
                          });

    clear = new Gomb(this, 500, 270, 120, 50, "Clear",
                     [&](){resetTiles();});

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

void SudokuApp::setBoard(SudokuGame game)
{
    resetTiles();

    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            int num = game.getCell(row, col);
            if (num > 0)
            {
                tiles[row][col]->setErtek(num);
                tiles[row][col]->setLocked(true); // a generált pálya számait ne lehessen változtatni

            }
        }
    }
}

void SudokuApp::generateBoard(Difficulty diff)
{
    sudokuGame = SudokuGenerator::generate(diff);
    generated = sudokuGame;

    setBoard(sudokuGame);
}

void SudokuApp::checkConflicts()
{
    auto conflicts = sudokuGame.checkValid();

    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c)
            tiles[r][c]->setValid(true);

    for (const auto& [r, c] : conflicts)
        tiles[r][c]->setValid(false);

    allValid = conflicts.empty();
}

void SudokuApp::update(int row, int col)
{
    // board frissítése az aktuális értékkel
    sudokuGame.setCell(row, col, tiles[row][col]->getErtek());

    checkConflicts();

    if (allValid && sudokuGame.isFull())
    {
        cout << "nyert" << endl;
        // TODO: ide a victory screen vagy ilyesmi
    }
}








