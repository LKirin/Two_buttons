#include <string>
#include <iostream>
#include <raylib.h>
#include "player.hpp"//vector, block.hpp are inside

using namespace std;

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
                Block w(texWall, /*pos*/{float(j * size), float(i * size)}, /*size*/{float(size), float(size)}, true);
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
    //variables---------------------------------------------------
    Color warmColor = {179, 148, 74, 255};

    const int screenWidth = 1250;
    const int screenHeight = 1050;

    InitWindow(screenWidth, screenHeight, "Cool game");

    Texture2D wallTex = LoadTexture("../wallTexture.png");
    Texture2D floorTex = LoadTexture("../floorTexture.png");
    Texture2D playerTex = LoadTexture("../playerTexture.png");
    Image schema = LoadImage("../LabirintSchema.png");
    Vector2 blockSize = {50, 50};

    vector<vector<Block>> mapPlaying;
    creatingMap(mapPlaying, blockSize.x, wallTex, floorTex, schema);
    //---------------------------------------------------------------
    Player player({50, 50}, 3, playerTex);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {   
        player.moving();

        BeginDrawing();
        ClearBackground(WHITE);

        // Drawing map------------------------------------------------------
        for (int i = 0; i < mapPlaying.size(); i++)
        {
            for (int j = 0; j < mapPlaying[i].size(); j++)
            {
                DrawTextureEx(mapPlaying[i][j].texture, mapPlaying[i][j].pos, 0.f, 0.05, WHITE);
            }
        }
        //---------------------------------------------------------------------

        player.animaDrawing();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
