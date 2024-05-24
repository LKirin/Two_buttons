#include "button.hpp"
#include <cmath>

void Button::generatePos(const std::vector<std::vector<Block>> &map)
{

    int posButton = GetRandomValue(15, 80);

    //--------------------------------------
    int num = 0;
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (!map[i][j].type)
            {
                if (num == posButton)
                {
                    position = {map[i][j].pos.x + 5, map[i][j].pos.y + 5};
                    return;
                }
                ++num;
            }
        }
    }
    //-----------------------------------
}

Button::Button(const std::vector<std::vector<Block>> &map)
{
    generatePos(map);
}

float Button::countingDist(Vector2 posPlayer)
{

    float proectionX = abs(position.x - posPlayer.x);
    float proectionY = abs(position.y - posPlayer.y);

    float d = sqrt(pow(proectionX, 2) + pow(proectionY, 2));
    return d;
}

void Button::pressButton(Vector2 posPlayer){
    if(IsKeyPressed(KEY_SPACE) && countingDist(posPlayer) < 15){
        isPressed = true;
    }
}