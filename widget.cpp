#include "widget.hpp"
#include "app.hpp"

Widget::Widget(App *_parent, int _x, int _y, int _sx, int _sy):
    parent(_parent), x(_x), y(_y), sx(_sx), sy(_sy), selected(false)
{
    parent->addWidget(this);
}

bool Widget::is_selected(int mx, int my)
{
    return mx > x && mx < x+sx && my > y && my < y+sy;
}

void Widget::setSelected(bool isSelected)
{
    selected = isSelected;
}

bool Widget::isSelected() const
{
    return selected;
}
