#include <raylib.h>
#include "block.hpp"
#include <vector>

using namespace std;

class Player
{
public:
    Player(Vector2 position, int Speed, Texture2D tex);

    Vector2 pos;
    Vector2 playerSize = {30, 30};
    int speed;
    int numberInImage = 0;
    int direction = 0;

    Texture2D texture;

    void moving(vector<vector<Block>>& walls);
    void animaDrawing(Color WARM);

private:
    bool checkCollision(vector<vector<Block>>& walls, Vector2 speed);
};