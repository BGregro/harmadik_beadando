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
            int x = (75+col) + tileSize*col + (col/3 * 3);
            int y = (75+row) + tileSize*row + (row/3 * 3);

            tiles[row][col] = new SudokuNumber(this, x, y, tileSize, tileSize, row, col, 0,
                                               [&](int row, int col){update(row, col);});
        }
    }

    vector<string> difficulties = {"Easy", "Medium", "Hard"};
    difficultyMenu = new LegorduloWidget(this, 550, 75, 3, difficulties);

    ujJatekBtn = new Gomb(this, 550, 150, 120, 50, "New Game",
                       [&](){
                           removeVictoryText();
                           generateBoard(getDifficulty());
                        });

    resetBtn = new Gomb(this, 550, 210, 120, 50, "Reset Game",
                        [&](){
                            removeVictoryText();
                            sudokuGame = generated;
                            setBoard(sudokuGame);
                        });

    clearBtn = new Gomb(this, 550, 270, 120, 50, "Clear",
                        [&](){
                            removeVictoryText();
                            resetTiles();
                        });

    victoryText = nullptr;

    for (Widget *w : widgets)
        w->draw();

    gout << refresh;
}

// difficulty beállítása kiválasztó widgetből
Difficulty SudokuApp::getDifficulty()
{
    string diff = difficultyMenu->getSelected();

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

// egy játék alapján beállítja a kijelzendő számokat
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
                // a generált pálya számait ne lehessen változtatni
                tiles[row][col]->setLocked(true);
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

// rossz szám beírása esetén kijelöli a vele ütköző számokat
void SudokuApp::setConflicts()
{
    auto conflicts = sudokuGame.checkValid();

    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c)
            tiles[r][c]->setValid(true);

    for (const auto& [r, c] : conflicts)
        tiles[r][c]->setValid(false);

    allValid = conflicts.empty();
}

void SudokuApp::lockAll()
{
    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c)
            tiles[r][c]->setLocked(true);
}

// victory felirat megjelenítése + összes mező lock-olása
void SudokuApp::showVictoryScreen()
{
    string msg = "Gratulálunk! Megoldottad a feladatot!";
    int textWidth = gout.twidth(msg);
    int centerX = (szelesseg - textWidth) / 2;

    victoryText = new StaticText(this, centerX, 20, textWidth + 20, 40, msg);

    lockAll();
}

// kitörli a victory widgetet
void SudokuApp::removeVictoryText()
{
    if (victoryText != nullptr) {
        victoryText->clearWidget();
        widgets.erase(remove(widgets.begin(), widgets.end(), victoryText), widgets.end());
        delete victoryText;
        victoryText = nullptr;
    }
}

void SudokuApp::update(int row, int col)
{
    // board frissítése az aktuális értékkel
    sudokuGame.setCell(row, col, tiles[row][col]->getErtek());

    setConflicts();

    if (allValid && sudokuGame.isFull())
    {
        cout << "nyert" << endl;
        showVictoryScreen();
    }
}

