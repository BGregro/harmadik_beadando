#ifndef SUDOKUNUMBER_HPP
#define SUDOKUNUMBER_HPP

#include "widget.hpp"

class SudokuNumber : public Widget
{
protected:
    int ertek, minErtek, maxErtek;
public:
    SudokuNumber(App *parent, int _x, int _y, int _sx, int _sy);

    void draw() const override;
    void handle(genv::event event) override;

    void setErtek(int ujErtek);
    void novelNum();
    void csokkentNum();

    int getErtek() const;
    std::string getValueString() const override;
};

// TODO:
    // amikor ki van törölve a szám, akkor semmi ne legyen a widgetben (csak a cursor?)
    // kijelölést a widget színének megváltozása jelezze
    // lehessen növelni le/fel gombokkal is?

#endif // SUDOKUNUMBER_HPP
