#include "sudokuapp.hpp"

int main()
{
    SudokuApp app(800,800);
    app.event_loop();

    return 0;
}
