#include"Entity.h"

Entity::Entity( int x , int y , int cellSize , int offsetX , int offsetY )
{
    this->x = x;
    this->y = y;
    this->cellSize = cellSize;
    this->offsetX = offsetX;
    this->offsetY = offsetY;
}

int Entity::getX() const { return x; }
int Entity::getY() const { return y; }
