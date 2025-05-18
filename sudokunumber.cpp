#include "sudokunumber.hpp"
#include "graphics.hpp"
#include <string>

using namespace genv;
using namespace std;

const color black(0,0,0), grey(220, 220, 220), white(255,255,255), red(255,0,0), blue(210, 230, 255);
const int defaultMin = 0, defaultMax = 9;

enum State
{

};

SudokuNumber::SudokuNumber(App *parent, int _x, int _y, int _sx, int _sy,
                           int r, int c, int num,
                           std::function<void(int, int)> f):
    Widget(parent, _x, _y, _sx, _sy),
    ertek(num), minErtek(defaultMin), maxErtek(defaultMax),
    row(r), col(c), locked(false), valid(true),
    onValueChanged(f)
{

}

void SudokuNumber::draw() const
{
    if (locked)
        gout << blue;
    else if (selected)
        gout << grey;
    else
        gout << white;

    gout << move_to(x, y) << box(sx, sy);

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
    if (locked)
        return;

    if (ev.type == ev_key && ev.keycode > 0)
    {
        if (ev.keycode == key_backspace || ev.keyutf8 == "0") {
            clear();
            return;
        }

        // szam beirasa a widgetbe
        if (!ev.keyutf8.empty() && ev.keyutf8.size() == 1) {
            char ch = ev.keyutf8[0];
            if (ch >= '1' && ch <= '9') {
                int number = ch - '0';
                ujErtek(number);
            }
        }
    }
}

void SudokuNumber::action()
{
    onValueChanged(row, col);
}

void SudokuNumber::clear()
{
    ertek = 0;
    action();
}

void SudokuNumber::setErtek(int uj)
{
    if (ertek >= minErtek && ertek <= maxErtek && uj != ertek)
    {
        ertek = uj;
    }
}

void SudokuNumber::ujErtek(int uj)
{
    if (!locked &&
        ertek >= minErtek && ertek <= maxErtek &&
        uj != ertek)
    {
        ertek = uj;
        action(); // amikor megvaltozik az ertek, akkor update-eli a jatekot az app-on keresztul
    }
}

void SudokuNumber::setLocked(bool lock)
{
    locked = lock;
}

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


