#include "statictext.hpp"
#include <string>

using namespace std;
using namespace genv;

StaticText::StaticText(App *parent, int x, int y, int sx, int sy,
                       string text, color bgC, color textC):
    Widget(parent, x, y, sx, sy), _text(text), bgColor(bgC), textColor(textC)
{}

void StaticText::draw() const
{
    gout << bgColor
         << move_to(x, y)
         << box(sx, sy)
         << textColor
         << move_to(x + (sx - gout.twidth(_text))/2, (y + (sy - (gout.cascent() + gout.cdescent()))/2))
         << text(_text);
}

void StaticText::clearWidget()
{
    gout << color(0,0,0)
         << move_to(x, y)
         << box(sx, sy);
}

void StaticText::showWidget()
{
    draw();
}

// háttér színét beállítja
void StaticText::setBGcolor(color c)
{
    bgColor = c;
}

// szöveg színét beállítja
void StaticText::setTextColor(color c)
{
    textColor = c;
}

void StaticText::handle(event ev)
{

}
