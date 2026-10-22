#include"Box.h"

Box::Box(int x, int y , int cellSize , int offsetX , int offsetY ) : Entity( x, y , cellSize , offsetX , offsetY )    {}

void Box::setX(int x) { this->x = x; }

void Box::setY(int y) { this->y = y; }

void Box::SetOnTarget( bool status)
{
    onTarget = status;
}

void Box::Draw()
{
    int boxX = offsetX + x * cellSize;
    int boxY = offsetY + y * cellSize;
    Color CurColor = onTarget ? boxOnTargetColor : boxColor ;
    DrawRectangle( boxX , boxY , cellSize , cellSize , CurColor );
}
