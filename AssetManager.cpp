#include "AssetManager.h"

bool AssetManager::LoadTextures()
{
    boxTexture = LoadTexture("PicturesPBL/Box_0.png");
    boxOnTargetTexture = LoadTexture("PicturesPBL/Box_1.png");

    if (boxTexture.id == 0 || boxOnTargetTexture.id == 0)
    {
        TraceLog(LOG_ERROR, "Failed to load box textures");
        Unload();
        return false;
    }

    return true;
}

void AssetManager::Unload()
{
    if (boxTexture.id != 0)
        UnloadTexture(boxTexture);
    if (boxOnTargetTexture.id != 0)
        ::UnloadTexture(boxOnTargetTexture);

    boxTexture = {};
    boxOnTargetTexture = {};
}

Texture2D AssetManager ::GetTexture( TextureAsset asset ) const 
{
    switch ( asset )
    {
        case TextureAsset::Box:
            return boxTexture;
        case TextureAsset::BoxOnTarget:
            return boxOnTargetTexture;
        
        default:
            TraceLog( LOG_ERROR , "Unknown texture asset" );
            return {};

    }
}