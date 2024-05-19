#include <vector>
#include <raylib.h>

class Block{
    public:
    Block(Texture2D tex, Vector2 position, Vector2 siz, bool Type);

    bool type;
    Texture2D texture;
    Vector2 pos;
    Vector2 size = {50, 50};
    float countingDist(Vector2 posPlayer);
};
