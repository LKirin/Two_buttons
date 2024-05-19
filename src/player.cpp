#include "player.hpp"

Player::Player(Vector2 position, int Speed, Texture2D tex)
{
    pos = position;
    speed = Speed;
    texture = tex;
}

void Player::moving()
{
    // movement
    if (IsKeyDown(KEY_W))
    {
        pos.y -= speed;

        if (direction != 2)
        {
            numberInImage = 0;
        }
        else
        {
            ++numberInImage;
        }
        direction = 2;
    }
    else if (IsKeyDown(KEY_S))
    {
        pos.y += speed;

        if (direction != 0)
        {
            numberInImage = 0;
        }
        else
        {
            ++numberInImage;
        }
        direction = 0;
    }

    if (IsKeyDown(KEY_A))
    {
        pos.x -= speed;

        if (direction != 1)
        {
            numberInImage = 0;
        }
        else
        {
            ++numberInImage;
        }
        direction = 1;
    }
    else if (IsKeyDown(KEY_D))
    {
        pos.x += speed;

        if (direction != 3)
        {
            numberInImage = 0;
        }
        else
        {
            ++numberInImage;
        }
        direction = 3;
    }
}

void Player::animaDrawing()
{
    DrawTexturePro(texture, {float((numberInImage / 2) * 118), float(direction * 120), 118.f, 120.f}, {pos.x, pos.y, playerSize.x, playerSize.y}, {0, 0}, 0, WHITE);

}
