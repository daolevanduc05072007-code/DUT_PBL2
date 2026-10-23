#pragma once
#include<vector>
#include<string>
#include"Box.h"
#include"Player.h"
#include"Colour.h"
#include<raylib.h>
using namespace std;

class Grid
{
    private:
        struct MoveState
        {
            Player player;
            vector<Box> boxes;
        };
        
        int cellSize;
        int offsetX;
        int offsetY;
        int cntMove;

        vector<vector<int> > FloorMap; // 0: floor, 1: wall, 2: target
        vector<MoveState> moveHistory;
    public:
        Grid( vector<string> &LevelData , const int &sw , const int &sh );

        vector<Box> Boxes;
        Player player;

        void MovePlayer( int keymove );
        bool UndoMove();
        bool CheckLegitMove( int keymove );
        bool CheckWin();
        int  GetMove();

        void Draw();
    
};
