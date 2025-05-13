#ifndef SUDOKUAPP_HPP
#define SUDOKUAPP_HPP

#include "app.hpp"
#include "sudokunumber.hpp"
#include "sudokugame.hpp"

class SudokuApp : public App
{
protected:
    std::vector<SudokuNumber*> tiles;
    SudokuGame sg;
public:
    SudokuApp(int, int);
    void updateBoard();
};

// Ötletek:
    // sudoku-ban lock-olni a már kész sorokat/oszlopokat/3x3masokat
    // TODO: highlight errors
    // ?: nyilakkal navigalni tile-ok között?
    // nem csak a kijelölt négyzet, de annak a sora és oszlopa is ki legyen jelölve?
        // ez lehet olyan, hogy pl segítség bekapcsolása/kiválasztása
    // amikor rossz számot ír be, akkor jelölje be az egyező számot is


#endif // SUDOKUAPP_HPP
