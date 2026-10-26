#pragma once
#include"Entity.h"
class Player : public Entity
{
    public:
        Player();
        Player(int X, int Y, int CellSize, int OffsetX, int OffsetY);
        void Draw(const AssetManager& Assets) override;
};