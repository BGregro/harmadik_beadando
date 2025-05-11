#include "sudokunumber.hpp"
#include "graphics.hpp"
#include <string>
#include <iostream>

using namespace genv;
using namespace std;

const color black(0,0,0), grey(200,200,200), white(255,255,255);
const int defaultMin = 0, defaultMax = 9;

SudokuNumber::SudokuNumber(App *parent, int _x, int _y, int _sx, int _sy):
    Widget(parent, _x, _y, _sx, _sy), ertek(0), minErtek(defaultMin), maxErtek(defaultMax)
{

}

void SudokuNumber::draw() const
{
    // Draw main box background (number area + arrows)
    gout << white << move_to(x, y) << box(sx, sy);

    int numH = gout.cascent();
    int numW = gout.twidth("1");

    if (ertek != 0)
    {
        gout << black
             << move_to(x + (sx - numW)/2, y + (sy - numH)/2)
             << text(to_string(ertek));
    }
}

void SudokuNumber::handle(event ev)
{
    if (ev.type == ev_key && ev.keycode > 0) // key felengedesenel ne fusson le megegyszer
    {
        if (ev.keycode == key_backspace)
        {
            ertek = ertek/10;
        }
        else if (ev.keycode == key_pgdn && ertek-10 > minErtek)
            ertek -= 10;
        else if (ev.keycode == key_pgup && ertek+10 < maxErtek)
            ertek += 10;

        // szam beirasa a widgetbe
        if (!ev.keyutf8.empty() && ev.keyutf8.size() == 1 &&
            ev.keyutf8[0] >= '0' && ev.keyutf8[0] <= '9')
        {
            // beirt szam beallitasa
            int number = ev.keyutf8[0] - '0';
            setErtek(number);
        }
    }
}

void SudokuNumber::setErtek(int ujErtek)
{
    if (ertek >= minErtek && ertek <= maxErtek)
        ertek = ujErtek;
}

void SudokuNumber::novelNum()
{
    if (ertek < maxErtek)
        ++ertek;
}

void SudokuNumber::csokkentNum()
{
    if (ertek > minErtek)
        --ertek;
}

int SudokuNumber::getErtek() const
{
    return ertek;
}

string SudokuNumber::getValueString() const
{
    return to_string(ertek);
}




