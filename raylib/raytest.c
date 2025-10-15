// hello.c
#include "raylib.h"

int main() {
    InitWindow(800, 600, "Hello Raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, Raylib!", 350, 280, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

