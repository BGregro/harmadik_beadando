#ifndef SUDOKUNUMBER_HPP
#define SUDOKUNUMBER_HPP

#include "widget.hpp"
#include <functional>

class SudokuNumber : public Widget
{
protected:
    int ertek, minErtek, maxErtek;
    int row, col;
    std::function<void()> onValueChanged;
public:
    SudokuNumber(App *parent, int _x, int _y, int _sx, int _sy,
                 int r, int c,
                 std::function<void()> f);

    void draw() const override;
    void handle(genv::event) override;

    void action();

    void setErtek(int);
    void novelNum();
    void csokkentNum();
    void clear();

    int getErtek() const;
    std::string getValueString() const override;
};

// TODO:
    // lehessen növelni le/fel gombokkal is?
    // ertek csak 1-9 között legyen és legyen egy külön state törölt-re?

#endif // SUDOKUNUMBER_HPP
