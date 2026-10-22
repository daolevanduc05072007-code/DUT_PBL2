#include"Player.h"

Player::Player() : Entity( 0 , 0 , 0 , 0 , 0 ) {}

Player::Player(int x, int y, int cellSize, int offsetX, int offsetY) : Entity(x, y, cellSize, offsetX, offsetY) {}

void Player::Draw()
{
    int playerX = offsetX + x * cellSize;
    int playerY = offsetY + y * cellSize;
    DrawRectangle( playerX , playerY , cellSize , cellSize , playerColor );
}