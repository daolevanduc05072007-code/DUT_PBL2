#include"Box.h"

Box::Box(int X, int Y, int CellSize, int OffsetX, int OffsetY)
    : Entity(X, Y, CellSize, OffsetX, OffsetY) {}

void Box::SetX(int X) { this->X = X; }

void Box::SetY(int Y) { this->Y = Y; }

void Box::SetOnTarget(bool Status)
{
    IsOnTarget = Status;
}

void Box::Draw(const AssetManager& Assets)
{
    TextureAsset Image = IsOnTarget ? TextureAsset::BoxOnTarget : TextureAsset::Box;
    Texture2D Texture = Assets.GetTexture(Image);
    int BoxX = OffsetX + X * CellSize;
    int BoxY = OffsetY + Y * CellSize;
    
    Rectangle Source =
    {
        0.0f,
        0.0f,
        static_cast<float>(Texture.width),
        static_cast<float>(Texture.height)
    };

    Rectangle Destination =
    {
        static_cast<float>(BoxX),
        static_cast<float>(BoxY),
        static_cast<float>(CellSize),
        static_cast<float>(CellSize)
    };

    Vector2 Origin = {0.0f, 0.0f};

    DrawTexturePro(Texture, Source, Destination, Origin, 0.0f, WHITE);
}
