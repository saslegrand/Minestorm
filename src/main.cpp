#include <stdlib.h>
#include <crtdbg.h>

#include <raylib.h>
#include <cstdlib>
#include <ctime>

#include "../include/text.h"
#include "../include/game.h"

int main(int argc, char* argv[])
{
    // Check for leak
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Minestorm");
    InitAudioDevice();
    SetMasterVolume(0.2f);
    SetTargetFPS(60);

    Game game;

    srand((unsigned int)time(NULL));

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Update game
        game.update();

        //Render game
        game.draw();

        EndDrawing();
    }

    // Delete game
    game.deleteGame();

    // Close project
    CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context

    return 0;
}