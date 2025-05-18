    #ifndef SUDOKUGENERATOR_HPP
#define SUDOKUGENERATOR_HPP

#include "sudokugame.hpp"

enum class Difficulty {
    Easy,
    Medium,
    Hard
};

class SudokuGenerator {
public:
    // Visszaad egy egyértelműen megoldható SudokuGame pályát
    static SudokuGame generate(Difficulty);
};

#endif // SUDOKUGENERATOR_HPP
