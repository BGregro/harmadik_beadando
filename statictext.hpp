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
    StaticText(App *parent, int x, int y, int sx, int sy, std::string text,
               genv::color bgC = genv::color(255,255,255), genv::color textC = genv::color(0,0,0));

    void setBGcolor(genv::color);
    void setTextColor(genv::color);

    void draw() const override;
    void clearWidget();
    void showWidget();
    void handle(genv::event) override;
};

#endif // STATICTEXT_HPP
