#include <string>
#include <iostream>
#include <raylib.h>
#include "player.hpp" //vector, block.hpp are inside

using namespace std;

Color colorMultiply(Color color, float k)
{
    int red = color.r * k > 255 ? 255 : color.r * k;
    int green = color.g * k > 255 ? 255 : color.g * k;
    int blue = color.b * k > 255 ? 255 : color.b * k;
    Color result = {red, green, blue, 255};
    return result;
}

void creatingMap(vector<vector<Block>> &playMap, int size, Texture2D texWall, Texture2D texFloor, Image schema)
{ // 25 * 21 map
    int width = 25 * size;
    int height = 21 * size;
    for (int i = 0; i < height / size; i++)
    {
        vector<Block> emptyVec;
        playMap.push_back(emptyVec);
    }

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            if (GetImageColor(schema, j, i).r == 0)
            {
                Block w(texWall, /*pos*/ {float(j * size), float(i * size)}, /*size*/ {float(size), float(size)}, true);
                playMap[i].push_back(w);
            }
            else
            {
                Block f(texFloor, {float(j * size), float(i * size)}, {float(size), float(size)}, false);
                playMap[i].push_back(f);
            }
        }
    }
}

int main()
{
    // variables---------------------------------------------------
    Color warmColor = {179, 148, 74, 255};
    float kLightning = 0.01;

    const int screenWidth = 1250;
    const int screenHeight = 1050;

    InitWindow(screenWidth, screenHeight, "Cool game");

    Texture2D wallTex = LoadTexture("../wallTexture.png");
    Texture2D floorTex = LoadTexture("../floorTexture.png");
    Texture2D playerTex = LoadTexture("../playerTexture.png");
    Image schema = LoadImage("../LabirintSchema.png");
    Vector2 blockSize = {50, 50};

    vector<vector<Block>> gameMap;
    creatingMap(gameMap, blockSize.x, wallTex, floorTex, schema);
    //---------------------------------------------------------------
    Player player({55, 55}, 3, playerTex);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        player.moving(gameMap);

        BeginDrawing();
        ClearBackground(WHITE);

        // Drawing map------------------------------------------------------
        for (int i = 0; i < gameMap.size(); i++)
        {
            for (int j = 0; j < gameMap[i].size(); j++)
            {
                if (gameMap[i][j].type)
                {
                    DrawTextureEx(gameMap[i][j].texture, gameMap[i][j].pos, 0.f, 0.05, colorMultiply(warmColor, 1 / (kLightning * gameMap[i][j].countingDist(player.pos))));
                }
            }
        }
        //---------------------------------------------------------------------

        player.animaDrawing(kLightning, warmColor);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
