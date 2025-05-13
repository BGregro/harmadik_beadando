#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics.hpp"

class App;

class Widget
{
protected:
    App *parent;
    int x, y, sx, sy;
    bool selected;
public:
    Widget(App *parent, int x, int y, int sx, int sy);

    virtual bool is_selected(int mx, int my);
    virtual void draw() const = 0;
    virtual void handle(genv::event ev) = 0;

    virtual void setSelected(bool isSelected);
    virtual bool isSelected() const;

    virtual std::string getValueString() const { return ""; }
};

#endif // WIDGET_HPP
