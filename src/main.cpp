#include <string>
#include<iostream>
#include <vector>
#include <raylib.h>
#include "block.hpp"

using namespace std;

void creatingMap(vector<vector<Block>> &playMap, int size, Texture2D texWall, Texture2D texFloor){//25 * 21 map
    int width = 25 * size;
    int height = 21 * size;

    for (int i = 0; i < height / size; i++)
    {
        vector<Block> emptyVec; 
        playMap.push_back(emptyVec);
    }
    
    //first level---------------------------------------------
    for(int i = 0; i < width / size; i++){
        if(i == 0 || i == 15 || i == 17 || i == 24){
            Block f(texFloor, {float(i * size), 0.f}, {size, size});
            playMap[0].push_back(f);            
        }
        else{
            Block w(texWall, {float(i * size), 0.f}, {size, size});
            playMap[0].push_back(w);
        }
    }
    //----------------------------------------------------------
}

int main()
{   

    Color warmColor = {179, 148, 74, 255};
    Vector2 size ={50, 50};

    

    const int screenWidth = 1260;
    const int screenHeight = 1060;

    InitWindow(screenWidth, screenHeight, "Cool game");

    Texture2D wall = LoadTexture("../wallTexture.png");
    Texture2D floor = LoadTexture("../floorTexture.png");
    vector<vector<Block>> mapPlaying;
    creatingMap(mapPlaying, size.x, wall, floor);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        for(int i = 0; i < mapPlaying.size(); i++){
            for(int j = 0; j < mapPlaying[i].size(); j++){
                DrawTextureEx(mapPlaying[i][j].texture, mapPlaying[i][j].pos, 0.f, 1, WHITE);
            }
        }
            
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
