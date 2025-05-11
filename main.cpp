#include "sudokuapp.hpp"

int main()
{
    SudokuApp app(600,600);
    app.event_loop();

    return 0;
}
