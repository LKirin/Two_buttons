#include "player.hpp"

Player::Player(Vector2 position, int Speed, Texture2D tex)
{
    pos = position;
    speed = Speed;
    texture = tex;
}

bool Player::checkCollision(vector<vector<Block>>& walls, Vector2 plannedSpeed)
{
    for (int i = 0; i < walls.size(); i++)
    {
        for (int j = 0; j < walls[i].size(); j++)
        {
            if (walls[i][j].type == true && CheckCollisionRecs(/*player*/ {pos.x + plannedSpeed.x, pos.y + plannedSpeed.y, playerSize.x, playerSize.y}, /*wall*/ {walls[i][j].pos.x, walls[i][j].pos.y, walls[i][j].size.x, walls[i][j].size.x}))
            {
                return true;
            }
        }
    }
    return false;
}

void Player::moving(vector<vector<Block>>& walls)
{
    // movement
    static double lastFrameTime = 0;
    double animFrameTime = 1.0 / 8;
    bool hasCollision = false;

    if (lastFrameTime + animFrameTime < GetTime())
    {
        numberInImage++;
        lastFrameTime = GetTime();
    }
    int oldDirection = direction;

    if (IsKeyDown(KEY_W))
    {
        // walls
        if (!checkCollision(walls, {0, -speed}))
        {
            pos.y -= speed;
        }
        //-----------------------------------------
        direction = 2;
    }
    else if (IsKeyDown(KEY_S))
    {
        if (!checkCollision(walls, {0, speed}))
        {
            pos.y += speed;
        }
        //-----------------------------------------
        direction = 0;
    }

    if (IsKeyDown(KEY_A))
    {
        // walls
        
        if (!checkCollision(walls, {-speed, 0}))
        {
            pos.x -= speed;
        }
        direction = 1;
    }
    else if (IsKeyDown(KEY_D))
    {
       
        if (!checkCollision(walls, {speed, 0}))
        {
            pos.x += speed;
        }
        //-----------------------------------------
        direction = 3;
    }

    if (oldDirection != direction)
    {
        numberInImage = 0;
    }
}

void Player::animaDrawing(float kLight, Color WARM)
{
    DrawTexturePro(texture, {float((numberInImage / 2) * 118), float(direction * 120), 118.f, 120.f}, 
    {pos.x, pos.y, playerSize.x + 10, playerSize.y + 10}, {0, 0}, 0, {WARM.r / kLight, WARM.g / kLight, WARM.b / kLight, 255});
}
