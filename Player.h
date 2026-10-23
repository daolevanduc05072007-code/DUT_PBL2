#pragma once
#include"Entity.h"
class Player : public Entity
{
    public:
        Player();
        Player(int x , int y , int cellSize , int offsetX , int offsetY );
        void Draw(const AssetManager& assets) override;
};