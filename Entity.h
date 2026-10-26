#pragma once
#include<raylib.h>
#include"Colour.h"
class AssetManager;
class Entity
{
    protected:
        int X;
        int Y;
        int CellSize;
        int OffsetX;
        int OffsetY;
    public:
        Entity() : X(0), Y(0), CellSize(0), OffsetX(0), OffsetY(0) {}
        Entity(int X, int Y, int CellSize, int OffsetX, int OffsetY);
        int GetX() const;
        int GetY() const;
        virtual void Draw(const AssetManager& Assets) = 0;
        virtual ~Entity() {}    

};