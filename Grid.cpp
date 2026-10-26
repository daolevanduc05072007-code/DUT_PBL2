#include"Grid.h"

const int MoveX[4] = {0, 0, -1, 1};
const int MoveY[4] = {-1, 1, 0, 0};

Grid::Grid(vector<string>& LevelData, const int& ScreenWidth, const int& ScreenHeight)
{
    CellSize = 48;
    MoveCount = 0;

    // Lay so cot lon nhat trong LevelData
    int MaxRow = static_cast<int>(LevelData.size());
    int MaxCol = 0;
    for (string& Row : LevelData)
    {
        if (static_cast<int>(Row.length()) > MaxCol)
            MaxCol = static_cast<int>(Row.length());
    }
    
    // Lay vien cua Grid de can giua LevelData
    OffsetX = (ScreenWidth - MaxCol * CellSize) / 2;
    OffsetY = (ScreenHeight - MaxRow * CellSize) / 2;

    // Khoi tao FloorMap voi gia tri mac dinh la 0 (floor)
    vector<int> TempRow(MaxCol, 0);
    for (int Row = 0; Row < MaxRow; ++Row)
        FloorMap.push_back(TempRow);

    // Duyet LevelData de khoi tao FloorMap, Boxes va Player
        for (int Row = 0; Row < MaxRow; ++Row)
        {
            for (int Col = 0; Col < static_cast<int>(LevelData[Row].length()); ++Col)
            {
                if (LevelData[Row][Col] == '#')
                    FloorMap[Row][Col] = 1; // wall
                if (LevelData[Row][Col] == '.')
                    FloorMap[Row][Col] = 2; // target
                if (LevelData[Row][Col] == '$')
                    Boxes.push_back(Box(Col, Row, CellSize, OffsetX, OffsetY)); // box
                if (LevelData[Row][Col] == '@')
                    CurrentPlayer = Player(Col, Row, CellSize, OffsetX, OffsetY); // player
            }
        }


}

void Grid::MovePlayer(int KeyMove)
{
    MoveState PreviousState{CurrentPlayer, Boxes};

    if (CheckLegitMove(KeyMove))
    {
        MoveHistory.push_back(PreviousState);
        MoveCount++;
        CurrentPlayer = Player(CurrentPlayer.GetX() + MoveX[KeyMove], CurrentPlayer.GetY() + MoveY[KeyMove],
                               CellSize, OffsetX, OffsetY);
    }
}

bool Grid::CheckLegitMove(int KeyMove)
{
    int NewX = CurrentPlayer.GetX() + MoveX[KeyMove];
    int NewY = CurrentPlayer.GetY() + MoveY[KeyMove];

    if (FloorMap[NewY][NewX] == 1)
        return false;

    for (auto& BoxItem : Boxes)
    {
        if (BoxItem.GetX() == NewX && BoxItem.GetY() == NewY)
        {
            int BoxNewX = BoxItem.GetX() + MoveX[KeyMove];
            int BoxNewY = BoxItem.GetY() + MoveY[KeyMove];

            if (FloorMap[BoxNewY][BoxNewX] == 1)
                return false;

            for (auto& OtherBox : Boxes)
            {
                if (OtherBox.GetX() == BoxNewX && OtherBox.GetY() == BoxNewY)
                    return false;
            }

            BoxItem.SetX(BoxNewX);
            BoxItem.SetY(BoxNewY);
            return true;
        }
    }
    return true;
}

bool Grid::CheckWin()
{
    int BoxCountOnTargets = 0;
    for (auto& BoxItem : Boxes)
    {
        if (FloorMap[BoxItem.GetY()][BoxItem.GetX()] == 2)
            BoxCountOnTargets++;
    }

    return BoxCountOnTargets == static_cast<int>(Boxes.size());
}

int Grid::GetMove()
{
    return MoveCount;
}

void Grid::Draw(const AssetManager& Assets)
{
    Texture2D FloorTexture = Assets.GetTexture(TextureAsset::Floor);
    Texture2D WallTexture = Assets.GetTexture(TextureAsset::Wall);

    for (int Row = 0; Row < static_cast<int>(FloorMap.size()); ++Row)
        for (int Col = 0; Col < static_cast<int>(FloorMap[Row].size()); ++Col)
        {
            int TileX = OffsetX + Col * CellSize;
            int TileY = OffsetY + Row * CellSize;
            bool IsWall = FloorMap[Row][Col] == 1;
            Texture2D Texture = IsWall ? WallTexture : FloorTexture;

            if (Texture.id != 0)
            {
                Rectangle Source = {
                    0.0f,
                    0.0f,
                    static_cast<float>(Texture.width),
                    static_cast<float>(Texture.height)
                };
                Rectangle Destination = {
                    static_cast<float>(TileX),
                    static_cast<float>(TileY),
                    static_cast<float>(CellSize),
                    static_cast<float>(CellSize)
                };
                DrawTexturePro(Texture, Source, Destination, {0.0f, 0.0f}, 0.0f, WHITE);
            }
            else
            {
                DrawRectangle(TileX, TileY, CellSize, CellSize, IsWall ? WallColor : BackgroundColor);
            }

            if (FloorMap[Row][Col] == 2)
            {
                int CenterX = TileX + CellSize / 2;
                int CenterY = TileY + CellSize / 2;
                float Radius = CellSize / 4.0f;
                DrawCircle(CenterX, CenterY, Radius, TargetColor);
            }
        }

    for (auto& BoxItem : Boxes)
    {
        if (FloorMap[BoxItem.GetY()][BoxItem.GetX()] == 2)
            BoxItem.SetOnTarget(true);
        else
            BoxItem.SetOnTarget(false);

        BoxItem.Draw(Assets);
    }

    CurrentPlayer.Draw(Assets);
}

bool Grid::UndoMove()
{
    if (MoveHistory.empty())
    {
        return false;
    }

    MoveState PreviousState = MoveHistory.back();
    MoveHistory.pop_back();

    CurrentPlayer = PreviousState.PlayerState;
    Boxes = PreviousState.BoxStates;
    MoveCount--;

    return true;
}