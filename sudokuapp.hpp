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
    void setConflicts();
    void lockAll();

    void removeVictoryText();
    void showVictoryScreen();
    void update(int, int);
};

// Ötletek:
    // sudoku-ban lock-olni a már kész sorokat/oszlopokat/3x3masokat
    // TODO: highlight errors -> hogyan?
        // amikor rossz számot ír be, akkor jelölje be az egyező számot is ?
    // ?: nyilakkal navigalni tile-ok között?

    // nem csak a kijelölt négyzet, de annak a sora és oszlopa is ki legyen jelölve?
        // ez lehet olyan, hogy pl segítség bekapcsolása/kiválasztása

    // extra szám gombok, amik megnyomásával be lehet írni számokat ?
        // vagy csak legyenek alul számok, amik eltűnnek, ha egyikből mindet leraktam ?

    // néhány példa pályát ki lehessen választani egy legördülő menüből (pl.: easy1, easy2, medium1, medium2, hard1, hard2)

    // nyert képernyő:
        // nyert felirat + zöldre változzanak a beírt számok?
        // lockolni az összes számot

#endif // SUDOKUAPP_HPP
