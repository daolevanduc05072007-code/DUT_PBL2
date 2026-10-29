#include "AssetManager.h"

bool AssetManager::LoadTextures()
{
    BoxTexture = LoadTexture("PicturesPBL/Box_0.png");
    BoxOnTargetTexture = LoadTexture("PicturesPBL/Box_1.png");
    WallTexture = LoadTexture("PicturesPBL/Wall.png");
    FloorTexture = LoadTexture("PicturesPBL/Floor.png");
    CharacterDownTexture = LoadTexture("PicturesPBL/character_down.png");
    CharacterUpTexture = LoadTexture("PicturesPBL/character_up.png");
    CharacterLeftTexture = LoadTexture("PicturesPBL/character_left.png");
    CharacterRightTexture = LoadTexture("PicturesPBL/character_right.png");
    MenuBackgroundTexture = LoadTexture("PicturesPBL/MenuBackground.png");

    if 
    (
        BoxTexture.id == 0 ||
        BoxOnTargetTexture.id == 0 ||
        WallTexture.id == 0 ||
        FloorTexture.id == 0 ||
        CharacterDownTexture.id == 0 ||
        CharacterUpTexture.id == 0 ||
        CharacterLeftTexture.id == 0 ||
        CharacterRightTexture.id == 0 ||
        MenuBackgroundTexture.id == 0
    )
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

    if (CharacterUpTexture.id != 0)
        UnloadTexture(CharacterUpTexture);

    if (CharacterLeftTexture.id != 0)
        UnloadTexture(CharacterLeftTexture);

    if (CharacterRightTexture.id != 0)
        UnloadTexture(CharacterRightTexture);

    if (MenuBackgroundTexture.id != 0)
        UnloadTexture(MenuBackgroundTexture);

    BoxTexture = {};
    BoxOnTargetTexture = {};
    WallTexture = {};
    FloorTexture = {};
    CharacterDownTexture = {};
    CharacterUpTexture = {};
    CharacterLeftTexture = {};
    CharacterRightTexture = {};
    MenuBackgroundTexture = {};
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
        
        case TextureAsset::CharacterUp:
            return CharacterUpTexture;

        case TextureAsset::CharacterLeft:
            return CharacterLeftTexture;
        
        case TextureAsset::CharacterRight:
            return CharacterRightTexture;

        case TextureAsset::MenuBackground:
            return MenuBackgroundTexture;

        default:
            TraceLog( LOG_ERROR , "Unknown texture asset" );
            return {};

    }
}