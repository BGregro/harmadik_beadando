#ifndef SUDOKUAPP_HPP
#define SUDOKUAPP_HPP

#include "app.hpp"
#include "sudokunumber.hpp"
#include "sudokugame.hpp"
#include "sudokugenerator.hpp"
#include "gomb.hpp"
#include "legordulowidget.hpp"
#include "statictext.hpp"


class SudokuApp : public App
{
protected:
    std::vector<std::vector<SudokuNumber*>> tiles;
    SudokuGame sudokuGame, generated;
    Gomb *ujJatekBtn, *resetBtn, *clearBtn;
    LegorduloWidget *difficultyMenu;
    StaticText *victoryText;
    bool allValid;
public:
    SudokuApp(int, int);

    Difficulty getDifficulty();

    void resetTiles();
    void setBoard(SudokuGame);
    void generateBoard(Difficulty);

    void setAllValid();
    void setConflicts();
    void lockAll();

    void removeVictoryText();
    void showVictoryScreen();
    void update(int, int);
};

#endif // SUDOKUAPP_HPP
