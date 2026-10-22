#pragma once
#include<raylib.h>
#include"Colour.h"
class Entity
{
    protected:
        int x;
        int y;
        int cellSize;
        int offsetX;
        int offsetY;
    public:
        Entity() { x = 0 ; y = 0 ; cellSize = 0 ; offsetX = 0 ; offsetY = 0; }
        Entity( int x , int y , int cellSize , int offSetX , int offsetY );
        int getX() const;
        int getY() const;
        virtual void Draw() = 0;
        virtual ~Entity() {}    

};