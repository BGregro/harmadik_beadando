#ifndef APP_HPP
#define APP_HPP

#include "widget.hpp"
#include <vector>

class App
{
public:
    App(int, int);

    void addWidget(Widget*);

    Widget* selectWidget(int mx, int my);
    void event_loop();

protected:
    int szelesseg, magassag;
    std::vector<Widget*> widgets;
    Widget* focus;
};

#endif // APP_HPP
