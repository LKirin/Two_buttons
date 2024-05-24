#include <raylib.h>
#include "block.hpp"

class Button{
    public:

    bool isPressed = false;
    Vector2 position;
    Vector2 size = {50, 50};

    Button(const std::vector<std::vector<Block>> &map);

    void generatePos(const std::vector<std::vector<Block>> &map);
    float countingDist(Vector2 posPlayer);
    void pressButton(Vector2 posPlayer);
};