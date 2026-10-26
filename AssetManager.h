#pragma once
#include <raylib.h>

enum class TextureAsset
{
    Box, 
    BoxOnTarget,
    Wall,
    Floor,
    CharacterDown
};

class AssetManager
{
    private:
        Texture2D BoxTexture = {};
        Texture2D BoxOnTargetTexture = {};
        Texture2D WallTexture = {};
        Texture2D FloorTexture = {};
        Texture2D CharacterDownTexture = {};
    public:
        bool LoadTextures();
        void Unload();
        Texture2D GetTexture(TextureAsset Asset) const;
};