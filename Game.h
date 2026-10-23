#pragma once
#include<raylib.h>
#include"Grid.h"
#include"Level.h"
#include"Colour.h"
#include"AssetManager.h"

enum GameState
{
    MENU = 0,
    PLAYING = 1

};
class Game
{
    private:
        Grid *grid;
        Level levels;
        GameState CurState = MENU;
        AssetManager assets;
        int currentLevel = 0;
        bool iscomplete = false;
        bool Flag_Win = 0 ;

       
        
    
    public:
        Game();
        ~Game();

        void Run();
        void LoadLevel( int index );
        void HandleInput();
        void Update();
        bool CheckWinCondition();

        void Render();
        void DrawMenu();
        void AllLevelDone();
        void SetWinAllLevel();

};