#pragma once
#include<raylib.h>
#include"Grid.h"
#include"Level.h"
#include"Colour.h"
#include"AssetManager.h"

enum class GameState
{
    Menu,
    Playing

};
class Game
{
    private:
        Grid* GridInstance;
        Level Levels;
        GameState CurrentState = GameState::Menu;
        AssetManager Assets;
        int CurrentLevel = 0;
        bool IsComplete = false;
        bool HasWonAllLevels = false;

       
        
    
    public:
        Game();
        ~Game();

        void Run();
        void LoadLevel(int Index);
        void HandleInput();
        void Update();
        bool CheckWinCondition();

        void Render();
        void DrawMenu();
        void AllLevelDone();
        void SetWinAllLevel();

};