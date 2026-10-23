#pragma once
#include <raylib.h>

enum class TextureAsset
{
    Box, 
    BoxOnTarget
};

class AssetManager
{
    private:
        Texture2D boxTexture = {};
        Texture2D boxOnTargetTexture = {};
    public:
        bool LoadTextures();
        void Unload();
        Texture2D GetTexture( TextureAsset asset ) const; 
};