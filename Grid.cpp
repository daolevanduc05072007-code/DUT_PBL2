#include"Grid.h"

const int mx[4] = {  0 , 0 ,  -1 , 1 };
const int my[4] = { -1 , 1 ,   0 , 0 };

Grid::Grid( vector<string> &LevelData ,  const int &sw , const int &sh )
{
    cellSize = 48;
    cntMove = 0;

    // Lay so cot lon nhat trong LevelData
    int MaxRow = LevelData.size();
    int MaxCol = 0;
    for ( string &row : LevelData )
    {
        if ( row.length() > MaxCol )
            MaxCol = row.length();
    }
    
    // Lay vien cua Grid de can giua LevelData
    offsetX = ( sw - MaxCol * cellSize ) / 2;
    offsetY = ( sh - MaxRow * cellSize ) / 2;

    // Khoi tao FloorMap voi gia tri mac dinh la 0 (floor)
    vector<int> tmpRow;
    for ( int i = 0 ; i < MaxCol ; ++i )
        tmpRow.push_back(0);
    for ( int i = 0 ; i < MaxRow ; ++i )
        FloorMap.push_back(tmpRow);

    // Duyet LevelData de khoi tao FloorMap, Boxes va Player
        for ( int i = 0 ; i < MaxRow ; ++i )
        {
            for ( int j = 0 ; j < LevelData[i].length() ; ++j )
            {
                if ( LevelData[i][j] == '#' )
                    FloorMap[i][j] = 1; // wall
                if ( LevelData[i][j] == '.' )
                    FloorMap[i][j] = 2; // target
                if ( LevelData[i][j] == '$' )
                    Boxes.push_back(Box(j , i , cellSize , offsetX , offsetY )); // box
                if ( LevelData[i][j] == '@' )
                    player = Player(j, i , cellSize , offsetX , offsetY ); // player
            }
        }


}

void Grid::MovePlayer( int keymove )
{
    MoveState previousState{ player , Boxes };

    if ( CheckLegitMove(keymove) == true )
    {
        moveHistory.push_back( previousState );
        cntMove++;
        player = Player(player.getX()+mx[keymove], player.getY()+my[keymove] , cellSize , offsetX , offsetY );
    }
}

bool Grid::CheckLegitMove( int keymove )
{
    int newX = player.getX() + mx[keymove];
    int newY = player.getY() + my[keymove];

    if ( FloorMap[newY][newX] == 1 )
        return false;

    for ( auto &box : Boxes )
    {
        if ( box.getX() == newX && box.getY() == newY )
        {
            int boxNewX = box.getX() + mx[keymove];
            int boxNewY = box.getY() + my[keymove];

            if ( FloorMap[boxNewY][boxNewX] == 1 )
                return false;

            for ( auto &otherBox : Boxes )
            {
                if ( otherBox.getX() == boxNewX && otherBox.getY() == boxNewY )
                    return false;
            }

            box.setX( boxNewX );
            box.setY( boxNewY );
            return true;
        }
    }
    return true;
}

bool Grid::CheckWin()
{
    int cnt = 0;
    for ( auto &box : Boxes )
    {
        if ( FloorMap[box.getY()][box.getX()] == 2 )
            cnt++;
    }

    if ( cnt == Boxes.size() )
        return true;
    else 
        return false;
}

int Grid::GetMove()
{
    return cntMove;
}

void Grid::Draw()
{
    for ( int i = 0 ; i < FloorMap.size() ; ++i )
        for ( int j = 0 ; j < FloorMap[i].size() ; ++j )
        {
            int x = offsetX + j * cellSize;
            int y = offsetY + i * cellSize;

            if ( FloorMap[i][j] == 1 )
                DrawRectangle( x , y , cellSize , cellSize , wallColor );
            if ( FloorMap[i][j] == 2 )
            {
                int CenterX = x + cellSize/2;
                int CenterY = y + cellSize/2;

                float radius = cellSize / 4.0f;
                DrawCircle( CenterX , CenterY , radius , targetColor );
            }
        }

    for ( auto &box : Boxes )
    {
        if ( FloorMap[box.getY()][box.getX()] == 2 )
            box.SetOnTarget(true);
        else
            box.SetOnTarget(false);

        box.Draw();
    }

    player.Draw();
}

bool Grid::UndoMove()
{
    if ( moveHistory.empty() )
    {
        return false;
    }

    MoveState previousState = moveHistory.back();
    moveHistory.pop_back();

    player = previousState.player;
    Boxes = previousState.boxes;
    cntMove--;

    return true;
}