#include "sudokunumber.hpp"
#include "graphics.hpp"
#include <string>
#include <iostream>

using namespace genv;
using namespace std;

const color black(0,0,0), grey(200,200,200), white(255,255,255);
const int defaultMin = 1, defaultMax = 9;
const int padding = 3;

SudokuNumber::SudokuNumber(App *parent, int _x, int _y, int _sx, int _sy, int _sx, int _sy):
    Widget(parent, _x, _y, 0, 0), minErtek(defaultMin), maxErtek(defaultMax)
{

}

void SudokuNumber::draw() const
{
    // Draw main box background (number area + arrows)
    gout << white << move_to(x, y) << box(sx, sy);

    int numH = gout.cascent();
    int numW = gout.twidth("1");


    gout << black
         << move_to(x+padding, y + sy/2 - numH/2)
         << text(to_string(ertek));

    // draw cursor
    gout << black
         << move_to(x+padding + to_string(ertek).size()*numW, y+padding)
         << line(0, sy-padding*2);

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
            setErtek(ertek*10 + number);
        }
    }
}

void SudokuNumber::setErtek(int ujErtek)
{
    if (ertek <= maxErtek && ertek >= minErtek )
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




