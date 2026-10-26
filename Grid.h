#pragma once
#include<vector>
#include<string>
#include"Box.h"
#include"Player.h"
#include"AssetManager.h"
#include"Colour.h"
#include<raylib.h>
using namespace std;

class Grid
{
    private:
        struct MoveState
        {
            Player PlayerState;
            vector<Box> BoxStates;
        };
        
        int CellSize;
        int OffsetX;
        int OffsetY;
        int MoveCount;

        vector<vector<int>> FloorMap; // 0: floor, 1: wall, 2: target
        vector<MoveState> MoveHistory;
    public:
        Grid(vector<string>& LevelData, const int& ScreenWidth, const int& ScreenHeight);

        vector<Box> Boxes;
        Player CurrentPlayer;

        void MovePlayer(int KeyMove);
        bool UndoMove();
        bool CheckLegitMove(int KeyMove);
        bool CheckWin();
        int GetMove();

        void Draw(const AssetManager& Assets);
    
};
