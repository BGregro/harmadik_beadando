#ifndef STATICTEXT_HPP
#define STATICTEXT_HPP

#include "widget.hpp"
#include <string>

class StaticText : public Widget
{
protected:
    std::string _text;
    genv::color bgColor, textColor;
public:
    StaticText(App *parent, int x, int y, int sx, int sy, std::string text);

    void setBGcolor(genv::color);
    void setTextColor(genv::color);

    void draw() const override;
    void clearWidget();
    void showWidget();
    void handle(genv::event) override;
};

#endif // STATICTEXT_HPP
