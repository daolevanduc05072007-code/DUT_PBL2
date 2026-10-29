#include"Player.h"
#include"AssetManager.h"

Player::Player() : Entity( 0 , 0 , 0 , 0 , 0 ) {}

Player::Player(int X, int Y, int CellSize, int OffsetX, int OffsetY)
    : Entity(X, Y, CellSize, OffsetX, OffsetY) {}

void Player::Draw(const AssetManager& Assets)
{
    int PlayerX = OffsetX + X * CellSize;
    int PlayerY = OffsetY + Y * CellSize;
    
    TextureAsset Asset = TextureAsset::CharacterDown;

    switch (Direction)
    {
        case PlayerDirection::Up:
            Asset = TextureAsset::CharacterUp;
            break;

        case PlayerDirection::Down:
            Asset = TextureAsset::CharacterDown;
            break;

        case PlayerDirection::Left:
            Asset = TextureAsset::CharacterLeft;
            break;

        case PlayerDirection::Right:
            Asset = TextureAsset::CharacterRight;
            break;
    }

    Texture2D Texture = Assets.GetTexture(Asset);

    if (Texture.id == 0)
    {
        DrawRectangle(PlayerX, PlayerY, CellSize, CellSize, PlayerColor);
        return;
    }

    Rectangle Source = 
    {
        0.0f,
        0.0f,
        static_cast<float>(Texture.width),
        static_cast<float>(Texture.height)
    };
    Rectangle Destination = 
    {
        static_cast<float>(PlayerX),
        static_cast<float>(PlayerY),
        static_cast<float>(CellSize),
        static_cast<float>(CellSize)
    };

    DrawTexturePro(Texture, Source, Destination, {0.0f, 0.0f}, 0.0f, WHITE);
}


void Player::SetDirection( PlayerDirection NewDirection )
{
    Direction = NewDirection;
}

PlayerDirection Player::GetDirection()  const
{
    return Direction;
}