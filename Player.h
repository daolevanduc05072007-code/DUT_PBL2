#pragma once
#include"Entity.h"


enum PlayerDirection
{
    Up,
    Down,
    Left,
    Right
};
class Player : public Entity
{
    private:
        PlayerDirection Direction = PlayerDirection::Down;
    public:
        Player();
        Player(int X, int Y, int CellSize, int OffsetX, int OffsetY);
        
        
        void SetDirection(PlayerDirection NewDirection );
        PlayerDirection GetDirection()  const;
        
        void Draw(const AssetManager& Assets) override;
};