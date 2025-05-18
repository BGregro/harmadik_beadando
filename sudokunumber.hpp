#ifndef SUDOKUNUMBER_HPP
#define SUDOKUNUMBER_HPP

#include "widget.hpp"
#include <functional>

class SudokuNumber : public Widget
{
protected:
    int ertek, minErtek, maxErtek;
    int row, col;
    bool locked, valid;
    std::function<void(int, int)> onValueChanged;
public:
    SudokuNumber(App *parent, int _x, int _y, int _sx, int _sy,
                 int r, int c, int num,
                 std::function<void(int, int)> f);

    void draw() const override;
    void handle(genv::event) override;

    void action();

    void setErtek(int);
    void ujErtek(int);
    void setLocked(bool lock);
    void clear();

    void setValid(bool);

    int getErtek() const;
    int getRow() const;
    int getCol() const;

};

#endif // SUDOKUNUMBER_HPP
