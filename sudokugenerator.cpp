#include "sudokugenerator.hpp"
#include <algorithm>
#include <random>
#include <ctime>
#include <functional>

using namespace std;

// létrehoz egy teljesen kitöltött sudoku pályát - rekurzívan
bool solve(SudokuGame& game, int row = 0, int col = 0)
{
    static std::mt19937 rng(std::random_device{}());

    if (row == 9)
        return true;
    if (col == 9)
        return solve(game, row + 1, 0);
    if (game.getCell(row, col) != 0)
        return solve(game, row, col + 1);

    vector<int> nums{1,2,3,4,5,6,7,8,9};
    // random sorrendbe rendezi a számokat
    shuffle(nums.begin(), nums.end(), rng);

    for (int num : nums)
    {
        // ha egy szám érvényes, akkor beállítja a jelenlegi cell-re és megy tovább
        if (game.isValidMove(row, col, num))
        {
            game.setCell(row, col, num);
            if (solve(game, row, col + 1))
                return true;
            game.setCell(row, col, 0);
        }
    }

    // ha nincs megfelelő szám, akkor "visszalép"
    return false;
}

// difficulty alapján megadja, hogy mennyi mező legyen üres
int holesForDifficulty(Difficulty d)
{
    switch (d)
    {
        case Difficulty::Easy:
            return 30;   // 51 mező kitöltve
            break;
        case Difficulty::Medium:
            return 45; // 36 mező kitöltve
            break;
        case Difficulty::Hard:
            return 55;   // 26 mező kitöltve
            break;
        default:
            return 45; // default: medium difficulty
    }
}

/*
Visszaadja a megoldások számát
    * ez szükséges ahhoz, hogy megnézzük-e, hogy egyértelmű-e a pálya
    * ha a megoldások száma > 1, akkor nem egyértelmű -> rossz
*/
int countSolutions(SudokuGame game)
{
    int solutions = 0;

    // minden egyes mezőbe kipróbálja az összes érvényes számot
    function<void(int, int)> backtrack = [&](int row, int col)
    {
        if (row == 9)
        {
            ++solutions;
            return;
        }
        if (col == 9)
        {
            backtrack(row + 1, 0);
            return;
        }
        if (game.getCell(row, col) != 0)
        {
            backtrack(row, col + 1);
            return;
        }

        for (int num = 1; num <= 9; ++num)
        {
            if (game.isValidMove(row, col, num))
            {
                game.setCell(row, col, num);
                backtrack(row, col + 1);
                game.setCell(row, col, 0);
                if (solutions > 1) return;
            }
        }
    };

    backtrack(0, 0); // még egy megoldást számol
    return solutions;
}

// generál egy egyételműen megoldható pályát
SudokuGame SudokuGenerator::generate(Difficulty diff)
{
    SudokuGame filled;
    solve(filled);

    // annyi cell lenullázása, amennyi a difficulty alapján be van állítva
    int holes = holesForDifficulty(diff);
    int removed = 0;

    // index párok létrehozása
    vector<pair<int, int>> indices;
    for (int row = 0; row < 9; ++row)
        for (int col = 0; col < 9; ++col)
            indices.emplace_back(row, col);

    // index párok random sorrendbe keverése (mt19937 - véletlenszám generátor)
    static std::mt19937 rng(std::random_device{}());
    shuffle(indices.begin(), indices.end(), rng);

    for (auto [row, col] : indices)
    {
        int backup = filled.getCell(row, col);
        filled.setCell(row, col, 0);

        if (countSolutions(filled) != 1)
            filled.setCell(row, col, backup); // ha nem egyértelmű, akkor visszarakja a számot
        else
            ++removed;

        if (removed >= holes)
            break;
    }

    return filled;
}
