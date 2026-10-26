#include"Game.h"

const int ScreenWidth = 1440;
const int ScreenHeight = 1080;

Game::Game()
{
    InitWindow(ScreenWidth, ScreenHeight, "PBL2-SOKOBAN");
    if (!Assets.LoadTextures())
    {
        TraceLog( LOG_ERROR , "Some game textures could not be loaded ");
    }
    SetTargetFPS(120);
    GridInstance = nullptr;
    LoadLevel(0);   

}

Game::~Game()
{
    delete GridInstance;
    Assets.Unload();
    CloseWindow();
}

void Game::Run()
{
    while (!WindowShouldClose())
    {
        HandleInput();
        Update();
        BeginDrawing();
        ClearBackground(BackgroundColor);
        Render();
        EndDrawing();
    }
}

void Game::LoadLevel(int Index)
{
    vector<string> LevelData = Levels.GetLevel(Index);
    if (GridInstance != nullptr)
    {
        delete GridInstance;
        GridInstance = nullptr;
    }
    GridInstance = new Grid(LevelData, ScreenWidth, ScreenHeight);
}

void Game::HandleInput()
{
    if (CurrentState == GameState::Menu)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            CurrentState = GameState::Playing;
            LoadLevel(CurrentLevel);
        }
        return;
    }

    if (IsKeyPressed(KEY_Z))
    {
        if (GridInstance != nullptr && GridInstance->UndoMove())
        {
            IsComplete = false;
            HasWonAllLevels = false;
        }
        return;

    }
    if (IsComplete)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            if (CurrentLevel + 1 < Levels.GetSizeLevel())
            {
                CurrentLevel++;
                LoadLevel(CurrentLevel);
                IsComplete = false;
            }
            else
                SetWinAllLevel();
        }
        return;
    }

    if (IsKeyPressed(KEY_R))
    {
        LoadLevel(CurrentLevel);
        return;
    }
    if (GridInstance != nullptr)
    {
        if (IsKeyPressed(KEY_UP))
        {
            GridInstance->MovePlayer(0);
        }
        else if (IsKeyPressed(KEY_DOWN))
        {
            GridInstance->MovePlayer(1);
        }
        else if (IsKeyPressed(KEY_LEFT))
        {
            GridInstance->MovePlayer(2);
        }
        else if (IsKeyPressed(KEY_RIGHT))
        {
            GridInstance->MovePlayer(3);
        }
    }
}

void Game::Update()
{
    if (CheckWinCondition())
        IsComplete = true;
}

bool Game::CheckWinCondition()
{
    return GridInstance != nullptr && GridInstance->CheckWin();
}

void Game::Render()
{
    if (CurrentState == GameState::Menu)
    {
        DrawMenu();
        return;
    }

    if (GridInstance != nullptr)
    {
        GridInstance->Draw(Assets);
        int CurrentMoves = GridInstance->GetMove();

        const char* MoveText = TextFormat("MOVES: %d", CurrentMoves);
        int FontSize = 30;
        int TextWidth = MeasureText(MoveText, FontSize);

        int XPos = ScreenWidth - TextWidth - 30;
        int YPos = 20;

        DrawText(MoveText, XPos, YPos, FontSize, BLACK);
    }

    if (HasWonAllLevels)
    {
        const char* Text = "Congratulations!";
        int FontSize = 60;
        int X = (ScreenWidth - MeasureText(Text, FontSize)) / 2;
        int Y = ScreenHeight / 2;

        DrawRectangle(0, 0, ScreenWidth, ScreenHeight, Fade(BLACK, 0.7f));
        DrawText(Text, X, Y, FontSize, YELLOW);
        return;
    }
    if (IsComplete)
    {
        DrawRectangle(0, 0, ScreenWidth, ScreenHeight, Fade(BLACK, 0.6f));

        const char* WinText = "LEVEL CLEARED!";
        int FontSize = 60;

        int TextWidth = MeasureText(WinText, FontSize);
        int XPos = (ScreenWidth - TextWidth) / 2;
        int YPos = (ScreenHeight / 2) - 50;

        DrawText(WinText, XPos, YPos, FontSize, YELLOW);

        const char* SubText = "Press ENTER to next level";
        int SubFontSize = 25;
        int SubTextWidth = MeasureText(SubText, SubFontSize);
        int SubXPos = (ScreenWidth - SubTextWidth) / 2;
        int SubYPos = YPos + FontSize + 20;

        DrawText(SubText, SubXPos, SubYPos, SubFontSize, WHITE);
    }
}

void Game::DrawMenu()
{
    DrawRectangle(0, 0, ScreenWidth, ScreenHeight, Fade(BLACK, 0.8f));

    const char* Title = "PBL2: SOKOBAN GAME";
    const char* StudentName = "DAO LE VAN DUC - LE TUC TRI";
    const char* ClassName = "25T_DT1";
    const char* Prompt = "PRESS [ENTER] TO START";

    int TitleSize = 50;
    int StudentNameSize = 24;
    int ClassSize = 22;
    int PromptSize = 30;

    int TitleX = (ScreenWidth - MeasureText(Title, TitleSize)) / 2;
    int StudentNameX = (ScreenWidth - MeasureText(StudentName, StudentNameSize)) / 2;
    int ClassX = (ScreenWidth - MeasureText(ClassName, ClassSize)) / 2;
    int PromptX = (ScreenWidth - MeasureText(Prompt, PromptSize)) / 2;

    DrawText(Title, TitleX, 200, TitleSize, RED);
    DrawText(StudentName, StudentNameX, 320, StudentNameSize, WHITE);
    DrawText(ClassName, ClassX, 360, ClassSize, WHITE);
    DrawText(Prompt, PromptX, 480, PromptSize, GREEN);
}

void Game::SetWinAllLevel()
{
    HasWonAllLevels = true;
}