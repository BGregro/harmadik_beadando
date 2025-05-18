#include "gomb.hpp"
#include "graphics.hpp"

using namespace std;
using namespace genv;

Gomb::Gomb(App *parent, int x, int y, int sx, int sy, string _label, function<void()> f):
    Widget(parent,x,y,sx,sy), label(_label), pushed(false), _f(f)
{}

void Gomb::draw() const
{
    gout << color(128,128,128)
         << move_to(x,y)
         << box(sx, sy);

    if (pushed)
        gout << color(255,255,255);
    else
        gout << color(0,0,0);

    gout << move_to(x + (sx - gout.twidth(label))/2, (y + (sy - (gout.cascent() + gout.cdescent()))/2))
         << text(label);
}

void Gomb::push()
{
    pushed = true;
}

void Gomb::unpush()
{
    pushed = false;
}

void Gomb::handle(event ev)
{
    if (ev.type == ev_mouse)
    {
        if (ev.button == btn_left)
        {
            action();
            push();
        }
        else if (ev.button == -btn_left)
            unpush();
    }

}

void Gomb::action()
{
    _f();
}











