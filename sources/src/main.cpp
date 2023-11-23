#include "../include/to_include.hpp"

#define SCREEN_WIDTH (1920)
#define SCREEN_HEIGHT (1080)

#define WINDOW_TITLE "AMOGUS"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetWindowState(FLAG_FULLSCREEN_MODE);
    SetTargetFPS(60);
    

    Texture2D texture = LoadTexture(ASSETS_PATH"amogus-spin.gif"); // Check README.md for how this works
    Vector2 pos_start = {SCREEN_WIDTH / 2 - texture.width / 2, SCREEN_HEIGHT / 2 - texture.height / 2};
    Vector2 pos = pos_start;
    double speed = 3.;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(texture, pos.x, pos.y, WHITE);

        const char* text = "zqsd ou flèches !";
        const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
        DrawText(text, 0, 0, 20, BLACK);


        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) pos.x += speed;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_Q)) pos.x -= speed;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_Z)) pos.y -= speed;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) pos.y += speed;

        if (IsKeyDown(KEY_P)) { speed += 0.1;}
        if (IsKeyDown(KEY_M)) { speed -= 0.1;}
        if (IsKeyDown(KEY_R)) {pos = pos_start;}

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
