#include <raylib.h>
#include "block.hpp"
#include <vector>

class Player
{
public:
    Player(Vector2 position, int Speed, Texture2D tex);

    Vector2 pos;
    Vector2 playerSize = {40, 40};
    int speed;
    int numberInImage = 0;
    int direction = 0;//0 - backward

    Texture2D texture;

    void moving();
    void animaDrawing();
};