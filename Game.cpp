#include"Game.h"

const int screenWidth = 1440;
const int screenHeight = 1080;

Game::Game()
{
    InitWindow(screenWidth, screenHeight, "PBL2-SOKOBAN");
    if ( !assets.LoadTextures() )
    {
        TraceLog( LOG_ERROR , "Some game textures could not be loaded ");
    }
    SetTargetFPS(120);
    grid = nullptr;
    LoadLevel(0);   

}

Game::~Game()
{
    delete grid;
    assets.Unload();
    CloseWindow();
}

void Game::Run()
{
    while ( !WindowShouldClose() )
    {
        HandleInput();
        Update();
        BeginDrawing();
        ClearBackground(backgroundColor);
        Render();
        EndDrawing();
    }
}

void Game::LoadLevel( int index )
{
    vector<string> levelData = levels.get(index);
    if ( grid != nullptr )
    {
        delete grid;
        grid = nullptr;
    }
    grid = new Grid(levelData, screenWidth, screenHeight);
}

void Game::HandleInput()
{
    if ( CurState == MENU )
    {
        if ( IsKeyPressed(KEY_ENTER) )
        {
            CurState = PLAYING;
            LoadLevel(currentLevel);
        }
        return;
    }

    if ( IsKeyPressed(KEY_Z) )
    {
        if ( grid != nullptr && grid->UndoMove() )
        {
            iscomplete = false;
            Flag_Win = false;
        }
        return;

    }
    if ( iscomplete == true )
    {
        if ( IsKeyPressed(KEY_ENTER) )
        {
            if ( currentLevel+1 < levels.GetSizeLevel() )
            {
                currentLevel++;
                LoadLevel(currentLevel);
                iscomplete = false;
            }
            else
                SetWinAllLevel();
        }
        return;
    }

    if ( IsKeyPressed(KEY_R ) )
    {
        LoadLevel(currentLevel);
        return;
    }
    if ( grid != nullptr )
    {
        if ( IsKeyPressed(KEY_UP) )
        {
            grid->MovePlayer(0);
        }
        else if ( IsKeyPressed(KEY_DOWN) )
        {
            grid->MovePlayer(1);
        }
        else if ( IsKeyPressed(KEY_LEFT) )
        {
            grid->MovePlayer(2);
        }
        else if ( IsKeyPressed(KEY_RIGHT) )
        {
            grid->MovePlayer(3);
        }
    }
}

void Game::Update()
{
    if ( CheckWinCondition() == true  )
        iscomplete = true;
}

bool Game::CheckWinCondition()
{
    return grid->CheckWin();
}

void Game::Render()
{
    if ( CurState == MENU )
    {
        DrawMenu();
        return;
    }

    if ( grid != nullptr )
    {
        grid->Draw(assets);
        int currentMoves = grid->GetMove();

        const char* moveText = TextFormat("MOVES: %d", currentMoves);
        int fontSize = 30;
        int textWidth = MeasureText(moveText, fontSize);

        int xPos = screenWidth - textWidth - 30;
        int yPos = 20;

        DrawText(moveText, xPos, yPos, fontSize, BLACK);
    }

    if ( Flag_Win == true )
    {
        const char* text = "Congratulations!";
        int fontSize = 60;
        int x = (screenWidth - MeasureText(text, fontSize)) / 2;
        int y = screenHeight / 2;

        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));
        DrawText(text, x, y, fontSize, YELLOW);
        return;
    }
    if ( iscomplete == true )
    {
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.6f));

        const char* winText = "LEVEL CLEARED!";
        int fontSize = 60;

        int textWidth = MeasureText(winText, fontSize);
        int xPos = (screenWidth - textWidth) / 2;
        int yPos = (screenHeight / 2)-50;

        DrawText(winText, xPos, yPos, fontSize, YELLOW);

        const char* subText = "Press ENTER to next level";
        int subFontSize = 25;
        int subTextWidth = MeasureText(subText, subFontSize);
        int subXPos = (screenWidth - subTextWidth) / 2;
        int subYPos = yPos + fontSize + 20;

        DrawText(subText, subXPos, subYPos, subFontSize, WHITE);
    }
}

void Game::DrawMenu()
{
    DrawRectangle( 0 , 0 , screenWidth , screenHeight , Fade(BLACK, 0.8f) );

    const char* Title = "PBL2: SOKOBAN GAME";
    const char* NameStudent = "DAO LE VAN DUC - LE TUC TRI";
    const char* ClassName = "25T_DT1";
    const char* Prompt = "PRESS [ENTER] TO START";

    int TitleSize = 50;
    int NameSize = 24;
    int ClassSize = 22;
    int PromptSize = 30;

    int titleX = (screenWidth - MeasureText(Title, TitleSize)) / 2;
    int nameX  = (screenWidth - MeasureText(NameStudent, NameSize)) / 2;
    int classX = (screenWidth - MeasureText(ClassName, ClassSize)) / 2;
    int promptX = (screenWidth - MeasureText(Prompt, PromptSize)) / 2;

    DrawText(Title, titleX, 200, TitleSize, RED);
    DrawText(NameStudent, nameX, 320, NameSize, WHITE);
    DrawText(ClassName, classX, 360, ClassSize, WHITE);
    DrawText(Prompt, promptX, 480, PromptSize, GREEN);
}

void Game::SetWinAllLevel()
{
    Flag_Win = true;
}