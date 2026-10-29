#pragma once
#include <raylib.h>

enum class TextureAsset
{
    Box, 
    BoxOnTarget,
    Wall,
    Floor,
    CharacterDown,
    CharacterUp,
    CharacterLeft,
    CharacterRight,
    MenuBackground
};

class AssetManager
{
    private:
        Texture2D BoxTexture = {};
        Texture2D BoxOnTargetTexture = {};
        Texture2D WallTexture = {};
        Texture2D FloorTexture = {};
        Texture2D CharacterDownTexture = {};
        Texture2D CharacterUpTexture = {};
        Texture2D CharacterLeftTexture = {};
        Texture2D CharacterRightTexture = {};
        Texture2D MenuBackgroundTexture = {};

    public:
        bool LoadTextures();
        void Unload();
        Texture2D GetTexture(TextureAsset Asset) const;
};