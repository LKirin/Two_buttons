#include <string>
#include <iostream>
#include "player.hpp" //vector, block.hpp are inside
#include "button.hpp"
#include <string>

using namespace std;

Color colorMultiply(Color color, float k)
{
    float red = color.r * k > 255 ? 255.f : color.r * k;
    float green = color.g * k > 255 ? 255.f : color.g * k;
    float blue = color.b * k > 255 ? 255.f : color.b * k;
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

enum State
{
    preGame,
    game,
    victory,
    defeat
};

int main()
{
    // variables---------------------------------------------------

    State state;
    state = preGame;

    Color warmColor = {179, 148, 74, 255};
    float kLightning = 0.07;

    const int screenWidth = 1250;
    const int screenHeight = 1050;

    InitWindow(screenWidth, screenHeight, "Cool game");
    InitAudioDevice();

    Music music = LoadMusicStream("../cavernMusic.mp3");
    music.looping = false;

    Texture2D wallTex = LoadTexture("../wallTexture.png");
    Texture2D floorTex = LoadTexture("../floorTexture.png");

    Texture2D playerTex = LoadTexture("../playerTexture.png");

    Texture2D blueButtonTex = LoadTexture("../blueButtonTexture.png");
    Texture2D redButtonTex = LoadTexture("../redButtonTexture.png");

    Texture2D blueIndecatorTex = LoadTexture("../blueIndecator.png");
    Texture2D redIndecatorTex = LoadTexture("../redIndecator.png");

    Image schema = LoadImage("../LabirintSchema.png");

    Vector2 blockSize = {50, 50};
    vector<vector<Block>> gameMap;
    creatingMap(gameMap, blockSize.x, wallTex, floorTex, schema);
    //--------------------------------------------------------------------

    SetTargetFPS(60);


    // PreGame------------------------------------------------------------
    if (state == preGame)
    {
        while (true)
        {
            //-------------------------
            if (WindowShouldClose())
            {
                CloseWindow();
            }
            //------------------------

            // changing state
            if (IsKeyPressed(KEY_ENTER))
            {
                state = game;
                break;
            }

            BeginDrawing();
            ClearBackground(BLACK);

            string preGameText = "Press Enter to start";
            DrawText(preGameText.c_str(), screenWidth / 2 - 240, screenHeight / 2 - 100, 50, {200, 200, 200, 255});

            EndDrawing();
        }
    }
    //--------------------------------------------------------------------

    // Game---------------------------------------------------------------
    if (state == game)
    {
        Button blueButton(gameMap);
        Button redButton(gameMap);

        double remainTime = 80.0;

        Player player({55, 55}, 3, playerTex);

        PlayMusicStream(music);
        while (true)
        {
            UpdateMusicStream(music);

            //--------------------------
            if (WindowShouldClose())
            {
                CloseWindow();
                UnloadMusicStream(music);
                CloseAudioDevice();
            }
            //------------------------

            // changing state
            if (remainTime <= 0)
            {
                state = defeat;
                StopMusicStream(music);

                break;
            }
            if (blueButton.isPressed && redButton.isPressed)
            {
                state = victory;
                StopMusicStream(music);

                break;
            }

            remainTime -= GetTime() / 1000;

            player.moving(gameMap);

            blueButton.pressButton(player.pos);
            redButton.pressButton(player.pos);

            BeginDrawing();
            ClearBackground(WHITE);

            // Drawing map------------------------------------------------------
            for (int i = 0; i < gameMap.size(); i++)
            {
                for (int j = 0; j < gameMap[i].size(); j++)
                {
                    if (gameMap[i][j].type)
                    {
                        DrawTextureEx(gameMap[i][j].texture, gameMap[i][j].pos, 0.f, 0.05, colorMultiply(warmColor, 0.5 / (kLightning * gameMap[i][j].countingDist(player.pos))));
                    }
                    else
                    {
                        DrawTextureEx(gameMap[i][j].texture, gameMap[i][j].pos, 0.f, 0.05, colorMultiply(warmColor, 1 / (kLightning * gameMap[i][j].countingDist(player.pos))));
                        // Drawing buttons
                        DrawTextureEx(blueButtonTex, blueButton.position, 0.f, 0.7, colorMultiply(warmColor, 1 / (kLightning * blueButton.countingDist(player.pos))));
                        DrawTextureEx(redButtonTex, redButton.position, 0.f, 0.7, colorMultiply(warmColor, 1 / (kLightning * redButton.countingDist(player.pos))));
                    }
                }
            }
            //---------------------------------------------------------------------

            player.animaDrawing(warmColor);

            if (!blueButton.isPressed)
            {
                DrawTextureV(blueIndecatorTex, {screenWidth - 100, 5}, WHITE);
            }
            if (!redButton.isPressed)
            {
                DrawTextureV(redIndecatorTex, {screenWidth - 160, 5}, WHITE);
            }

            // Draw remain time
            if (remainTime > 10)
            {
                DrawText(to_string(int(remainTime)).c_str(), screenWidth - 230, 5, 20, {200, 200, 200, 255});
            }
            else
            {
                DrawText(to_string(remainTime).c_str(), screenWidth - 250, 5, 20, {255, 120, 110, 255});
            }

            EndDrawing();
        }
    }
    //--------------------------------------------------------------------

    //Victory-------------------------------------------------------------
    if (state == victory)
    {
        while (true)
        {
            //-------------------------
            if (WindowShouldClose())
            {
                CloseWindow();
            }
            //------------------------

            // changing state
            if (IsKeyPressed(KEY_ENTER))
            {
                state = game;
                break;
            }

            BeginDrawing();
            ClearBackground(BLACK);

            string preGameText = "You are won!\nPress Enter";
            DrawText(preGameText.c_str(), screenWidth / 2 - 240, screenHeight / 2 - 100, 50, {255, 223, 0, 255});

            EndDrawing();
        }
    }
    //--------------------------------------------------------------------

    //defeat--------------------------------------------------------------
    if (state == defeat)
    {
        while (true)
        {
            //-------------------------
            if (WindowShouldClose())
            {
                CloseWindow();
            }
            //------------------------

            // changing state
            if (IsKeyPressed(KEY_ENTER))
            {
                state = game;
                break;
            }

            BeginDrawing();
            ClearBackground(BLACK);

            string preGameText = "Oh you defeated...\nPress Enter";
            DrawText(preGameText.c_str(), screenWidth / 2 - 240, screenHeight / 2 - 100, 50, {200, 15, 5, 255});

            EndDrawing();
        }
    }
}
