#ifndef SUDOKUAPP_HPP
#define SUDOKUAPP_HPP

#include "app.hpp"
#include "sudokunumber.hpp"
#include "sudokugame.hpp"
#include "sudokugenerator.hpp"

class SudokuApp : public App
{
protected:
    std::vector<SudokuNumber*> tiles;
    SudokuGame sg;
public:
    SudokuApp(int, int);

    void generateBoard(Difficulty diff);
    void update();
};

// Ötletek:
    // sudoku-ban lock-olni a már kész sorokat/oszlopokat/3x3masokat
    // TODO: highlight errors -> hogyan?
        // amikor rossz számot ír be, akkor jelölje be az egyező számot is ?
    // ?: nyilakkal navigalni tile-ok között?

    // nem csak a kijelölt négyzet, de annak a sora és oszlopa is ki legyen jelölve?
        // ez lehet olyan, hogy pl segítség bekapcsolása/kiválasztása

    // a pálya eleinte ne legyen legenerálva
        // egy menüvel ki lehessen választani, hogy milyen a nehézség
        // utána egy gombbal lehessen generálni
        // egy másik gomb legyen clear-elésre/újra generálásra

#endif // SUDOKUAPP_HPP
