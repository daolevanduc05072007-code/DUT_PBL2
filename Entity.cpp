#include"Entity.h"

Entity::Entity(int X, int Y, int CellSize, int OffsetX, int OffsetY)
{
    this->X = X;
    this->Y = Y;
    this->CellSize = CellSize;
    this->OffsetX = OffsetX;
    this->OffsetY = OffsetY;
}

int Entity::GetX() const { return X; }
int Entity::GetY() const { return Y; }
