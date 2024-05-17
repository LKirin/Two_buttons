#include <string>
#include <iostream>
#include <vector>
#include <raylib.h>
#include "block.hpp"

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
                Block w(texWall, {float(j * size), float(i * size)}, {float(size), float(size)});
                playMap[i].push_back(w);
            }
            else
            {
                Block f(texFloor, {float(j * size), float(i * size)}, {float(size), float(size)});
                playMap[i].push_back(f);
            }
        }
    }

}

int main()
{

    Color warmColor = {179, 148, 74, 255};
    Vector2 size = {50, 50};

    const int screenWidth = 1250;
    const int screenHeight = 1050;

    InitWindow(screenWidth, screenHeight, "Cool game");

    Texture2D wall = LoadTexture("../wallTexture.png");
    Texture2D floor = LoadTexture("../floorTexture.png");
    Image schema = LoadImage("../LabirintSchema.png");

    vector<vector<Block>> mapPlaying;
    creatingMap(mapPlaying, size.x, wall, floor, schema);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        for (int i = 0; i < mapPlaying.size(); i++)
        {
            for (int j = 0; j < mapPlaying[i].size(); j++)
            {
                DrawTextureEx(mapPlaying[i][j].texture, mapPlaying[i][j].pos, 0.f, 0.05, WHITE);
            }
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
