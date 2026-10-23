#include"Box.h"

Box::Box(int x, int y , int cellSize , int offsetX , int offsetY ) : Entity( x, y , cellSize , offsetX , offsetY )    {}

void Box::setX(int x) { this->x = x; }

void Box::setY(int y) { this->y = y; }

void Box::SetOnTarget( bool status)
{
    onTarget = status;
}

void Box::Draw( const AssetManager &assets ) 
{
    TextureAsset image = onTarget ? TextureAsset::BoxOnTarget : TextureAsset::Box;
    Texture2D texture = assets.GetTexture(image); 
    int boxX = offsetX + x * cellSize;
    int boxY = offsetY + y * cellSize;
    
    Rectangle source = 
    {
        0.0f,
        0.0f,
        static_cast<float>(texture.width),
        static_cast<float>(texture.height)
    };

    Rectangle destination = 
    {
        static_cast<float>(boxX),
        static_cast<float>(boxY),
        static_cast<float>(cellSize),
        static_cast<float>(cellSize)
    };

    Vector2 origin = {0.0f, 0.0f};

    DrawTexturePro(texture, source, destination, origin, 0.0f, WHITE);
}

