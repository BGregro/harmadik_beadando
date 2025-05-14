#include "legordulowidget.hpp"
#include "graphics.hpp"
#include <string>
#include <iostream>

using namespace genv;
using namespace std;

const color black(0,0,0), grey(200,200,200), white(255,255,255);
const int padding = 3;

int maxTextWidth(vector<string> v)
{
    int maxW = 0;
    for (string s: v)
    {
        int sW = gout.twidth(s);
        if (sW > maxW)
            maxW = sW;
    }

    return maxW;
}

LegorduloWidget::LegorduloWidget(App *parent, int x, int y, int _showCount, vector<string> _options):
    Widget(parent, x, y, 0, 0), options(_options), showCount(_showCount)
{
    if (options.size() == 0)
    {
        options.push_back("Error: No Options Given");
        showCount = 1;
    }

    showCount = max(1, showCount); // ha 0 lenne megadva konstruktorban
    visibleIndexes = getVisibleOptionIndexes();
    startOption = 0;
    selectedIndex = 0;
    hoverIndex = -1;
    opened = false;

    int maxW = maxTextWidth(options);
    arrowW = 20;
    arrowH = gout.cascent() + gout.cdescent() + padding;
    // sx a legszelesebb szoveg szelessege lesz, hogy beleferjen
    sx = maxW + arrowW + 2*padding;
    arrowX = x + sx - arrowW;
    sy = gout.cascent() + gout.cdescent() + padding;
    textH = gout.cascent() + gout.cdescent() + padding;
}

void LegorduloWidget::draw() const
{
    gout << white
         << move_to(x, y)
         << box(sx, sy);

    int textY = y + padding;

    if (opened)
    {
        int safeStart = min(startOption, max(0, (int)visibleIndexes.size() - showCount));

        // highlight hovered option
        if (hoverIndex >= 0 && hoverIndex < showCount &&
            safeStart + hoverIndex < visibleIndexes.size())
        {
            gout << grey
                 << move_to(x, textY-padding + hoverIndex*textH)
                 << box(sx, textH);
        }

        // draw visible options starting from safeStart
        for (int i = 0; i < showCount && safeStart + i < visibleIndexes.size(); ++i)
        {
            int optionIndex = visibleIndexes[safeStart + i];
            gout << black
                 << move_to(x + padding, textY)
                 << text(options[optionIndex]);
            textY += textH;
        }
    }
    else
    {
        // draw selected option
        gout << black
             << move_to(x + padding, textY)
             << text(options[selectedIndex]);
    }

    // arrow background
    gout << grey
         << move_to(arrowX, y)
         << box(arrowW, arrowH);

    // down arrow
    int arrowCenterX = x + sx - arrowW/2;
    int arrowTop = y + arrowH/4;
    int arrowBottom = y + 3*arrowH/4;

    gout << black
         << move_to(arrowCenterX, arrowBottom)
         << line_to(arrowCenterX - arrowW/3, arrowTop)
         << line_to(arrowCenterX + arrowW/3, arrowTop)
         << line_to(arrowCenterX, arrowBottom);

}

void LegorduloWidget::clear_draw() const
{
    gout << black << move_to(x, y) << box(sx, sy);
}

void LegorduloWidget::open_menu()
{
    opened = true;
    visibleIndexes = getVisibleOptionIndexes();
    startOption = 0;
    sy = textH * min(showCount, (int)options.size());
}

void LegorduloWidget::close_menu()
{
    opened = false;
    clear_draw();
    sy /= showCount;
}

void LegorduloWidget::arrowPressed(int mx, int my)
{
    if (mx >= arrowX && mx <= x+sx &&
        my >= y && my <= y+arrowH)
    {
        if (opened)
            close_menu();
        else
            open_menu();
    }
}

bool LegorduloWidget::clickedInside(int mx, int my)
{
    return mx >= x && mx <= x + sx &&
           my >= y && my <= y + sy;
}

vector<int> LegorduloWidget::getVisibleOptionIndexes() const
{
    vector<int> indices;
    indices.push_back(selectedIndex);

    int nextIndex = (selectedIndex + 1) % options.size();
    while (indices.size() < options.size())
    {
        if (nextIndex != selectedIndex)
            indices.push_back(nextIndex);

        nextIndex = (nextIndex + 1) % options.size();
    }

    return indices;
}

void LegorduloWidget::selectOption(int mx, int my)
{
    if (clickedInside(mx, my))
    {
        int clickedPos = (my-y) / textH;

        if (clickedPos >= 0 && startOption + clickedPos < visibleIndexes.size())
        {
            selectedIndex = visibleIndexes[startOption + clickedPos];
            visibleIndexes = getVisibleOptionIndexes();
            startOption = 0;
            hoverIndex = -1;
        }

        close_menu();
    }
}

void LegorduloWidget::hoverOption(int mx, int my)
{
    if (clickedInside(mx, my))
        hoverIndex = (my-y) / textH;
}

void LegorduloWidget::handle(event ev)
{
    if (ev.type == ev_mouse)
    {
        if (ev.button == btn_left)
        {
            if (clickedInside(ev.pos_x, ev.pos_y))
            {
                if (opened)
                    selectOption(ev.pos_x, ev.pos_y);
                else
                    arrowPressed(ev.pos_x, ev.pos_y);
            }
            else
                close_menu();
        }

        if (opened)
        {
            if (ev.button == btn_wheeldown)
            {
                if (startOption + showCount < visibleIndexes.size())
                    ++startOption;
            }
            else if (ev.button == btn_wheelup)
            {
                if (startOption > 0)
                    --startOption;
            }
        }

        hoverOption(ev.pos_x, ev.pos_y);

    }
}

string LegorduloWidget::getSelected() const
{
    return options[selectedIndex];
}

string LegorduloWidget::getValueString() const
{
    return options[selectedIndex];
}

int LegorduloWidget::getSelectedIndex() const
{
    return selectedIndex;
}

void LegorduloWidget::update(vector<string> newOptions)
{
    if (newOptions.size() > 0)
    {
        options = newOptions;
    }
    else
    {
        options.clear();
        selectedIndex = -1;
    }
}






