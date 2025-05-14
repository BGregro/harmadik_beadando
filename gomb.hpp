#ifndef GOMB_HPP
#define GOMB_HPP

#include "widget.hpp"
#include "functional"

class Gomb : public Widget
{
protected:
    std::string label;
    bool pushed;
    std::function<void()> _f;
public:
    Gomb(App *, int, int, int, int,
         std::string,
         std::function<void()> f);

    void draw() const override;
    void handle(genv::event) override;

    void push();
    void unpush();

    void action();
};

#endif // GOMB_HPP
