#include "block.hpp"
#include <cmath>
float Block::countingDist(Vector2 posPlayer){
    float proectionX = abs(pos.x - posPlayer.x);      
    float proectionY = abs(pos.y - posPlayer.y);

    float d = sqrt(pow(proectionX, 2) + pow(proectionY, 2));
    return d;      
}

Block::Block(Texture2D tex, Vector2 position, Vector2 siz){
    texture = tex;
    pos = position;
    size = siz;
}