#include "AssetManager.h"

bool AssetManager::LoadTextures()
{
    BoxTexture = LoadTexture("PicturesPBL/Box_0.png");
    BoxOnTargetTexture = LoadTexture("PicturesPBL/Box_1.png");
    WallTexture = LoadTexture("PicturesPBL/Wall.png");
    FloorTexture = LoadTexture("PicturesPBL/Floor.png");
    CharacterDownTexture = LoadTexture("PicturesPBL/character_down.png");

    if (
        BoxTexture.id == 0 ||
        BoxOnTargetTexture.id == 0 ||
        WallTexture.id == 0 ||
        FloorTexture.id == 0 ||
        CharacterDownTexture.id == 0)
    {
        TraceLog(LOG_ERROR, "Failed to load textures");
        Unload();
        return false;
    }

    return true;
}

void AssetManager::Unload()
{
    if (BoxTexture.id != 0)
        UnloadTexture(BoxTexture);
    if (BoxOnTargetTexture.id != 0)
        UnloadTexture(BoxOnTargetTexture);
    if (WallTexture.id != 0)
        UnloadTexture(WallTexture);
    if (FloorTexture.id != 0)
        UnloadTexture(FloorTexture);
    if (CharacterDownTexture.id != 0)
        UnloadTexture(CharacterDownTexture);

    BoxTexture = {};
    BoxOnTargetTexture = {};
    WallTexture = {};
    FloorTexture = {};
    CharacterDownTexture = {};
}

Texture2D AssetManager::GetTexture(TextureAsset Asset) const
{
    switch (Asset)
    {
        case TextureAsset::Box:
            return BoxTexture;
        case TextureAsset::BoxOnTarget:
            return BoxOnTargetTexture;
        case TextureAsset::Wall:
            return WallTexture;
        case TextureAsset::Floor:
            return FloorTexture;
        case TextureAsset::CharacterDown:
            return CharacterDownTexture;

        default:
            TraceLog( LOG_ERROR , "Unknown texture asset" );
            return {};

    }
}