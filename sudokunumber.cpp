#include "sudokunumber.hpp"
#include "graphics.hpp"
#include <string>

using namespace genv;
using namespace std;

const color black(0,0,0), grey(200,200,200), white(255,255,255), red(255,0,0);
const int defaultMin = 0, defaultMax = 9;

enum State
{

};

SudokuNumber::SudokuNumber(App *parent, int _x, int _y, int _sx, int _sy,
                           int r, int c,
                           int num, bool lock,
                           std::function<void()> f):
    Widget(parent, _x, _y, _sx, _sy),
    ertek(num), minErtek(defaultMin), maxErtek(defaultMax),
    row(r), col(c), locked(lock), valid(true),
    onValueChanged(f)
{

}

void SudokuNumber::draw() const
{
    if (selected)
        gout << grey << move_to(x, y) << box(sx, sy);
    else
        gout << white << move_to(x, y) << box(sx, sy);

    int numH = gout.cascent();
    int numW = gout.twidth("1");

    if (ertek != 0)
    {
        if (valid)
            gout << black
                 << move_to(x + (sx - numW)/2, y + (sy - numH)/2)
                 << text(to_string(ertek));
        else
            gout << red
                 << move_to(x + (sx - numW)/2, y + (sy - numH)/2)
                 << text(to_string(ertek));
    }
}

void SudokuNumber::handle(event ev)
{
    if (ev.type == ev_key && ev.keycode > 0)
    {
        if (ev.keycode == key_backspace)
            clear();

        // szam beirasa a widgetbe
        if (!ev.keyutf8.empty() && ev.keyutf8.size() == 1 &&
            ev.keyutf8[0] >= '0' && ev.keyutf8[0] <= '9')
        {
            int number = ev.keyutf8[0] - '0';
            setErtek(number);
        }
    }
}

void SudokuNumber::action()
{
    onValueChanged();
}

void SudokuNumber::clear()
{
    ertek = 0;
}

void SudokuNumber::setErtek(int ujErtek)
{
    if (ertek >= minErtek && ertek <= maxErtek && ujErtek != ertek)
    {
        ertek = ujErtek;
        action(); // amikor megvaltozik az ertek, akkor update-eli a jatekot az app-on keresztul
    }
}

void SudokuNumber::setLocked(bool lock)
{
    locked = lock;
}
/*
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
*/

void SudokuNumber::setValid(bool newValid)
{
    valid = newValid;
}

int SudokuNumber::getErtek() const
{
    return ertek;
}

int SudokuNumber::getRow() const
{
    return row;
}

int SudokuNumber::getCol() const
{
    return col;
}


