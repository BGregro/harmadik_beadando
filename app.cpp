#include "app.hpp"
#include "widget.hpp"
#include "graphics.hpp"
#include <vector>

using namespace genv;
using namespace std;

App::App(int _szelesseg, int _magassag):
    szelesseg(_szelesseg), magassag(_magassag)
{
    focus = 0;

    gout.open(szelesseg, magassag);
    gout.load_font("LiberationSans-Regular.ttf", 20);
}

void App::addWidget(Widget* w)
{
    widgets.push_back(w);
}

Widget* App::selectWidget(int mx, int my)
{
    for (int i = 0; i < widgets.size(); ++i)
    {
        if (widgets[i]->is_selected(mx, my))
            return widgets[i];
    }

    return 0;
}

void App::event_loop()
{
    event ev;
    while(gin >> ev)
    {
        if (ev.type == ev_mouse && ev.button == btn_left)
        {
            if (focus != nullptr) {
                focus->setSelected(false);
            }

            focus = selectWidget(ev.pos_x, ev.pos_y);

            if (focus != nullptr) {
                focus->setSelected(true);
            }
        }

        for (Widget *w : widgets)
        {
            if (w != focus)
                w->draw();
        }

        if (focus != nullptr)
        {
            focus->handle(ev);
            focus->draw();
        }

        gout << refresh;
    }
}
