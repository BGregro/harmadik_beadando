#ifndef LEGORDULOWIDGET_HPP
#define LEGORDULOWIDGET_HPP

#include "widget.hpp"
#include "graphics.hpp"
#include <string>

class LegorduloWidget : public Widget
{
protected:
    std::vector<std::string> options;
    std::vector<int> visibleIndexes;
    int textH, selectedIndex, hoverIndex, startOption, showCount;
    int arrowX, arrowW, arrowH;
    bool opened;
public:
    LegorduloWidget(App *parent, int x, int y, int _showCount, std::vector<std::string> _options);

    void draw() const override;
    void handle(genv::event) override;

    bool clickedInside(int mx, int my);
    void hoverOption(int mx, int my);
    void arrowPressed(int mx, int my);

    std::vector<int> getVisibleOptionIndexes() const;
    void selectOption(int mx, int my);
    void open_menu();
    void close_menu();
    void clear_draw() const;

    std::string getValueString() const override;
    std::string getSelected() const;
    int getSelectedIndex() const;
    void update(std::vector<std::string>);

    void add_option(std::string);
    void remove_selected();
};

#endif // LEGORDULOWIDGET_HPP
