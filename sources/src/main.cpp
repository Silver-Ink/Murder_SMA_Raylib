#include "to_include.hpp"

#define SCREEN_WIDTH (1920)
#define SCREEN_HEIGHT (1080)

#define WINDOW_TITLE "AMOGUS"

void test_window()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    // SetWindowState(FLAG_FULLSCREEN_MODE);
    SetTargetFPS(60);
    Crewmate test;
    
    
    Vector2 pos_start = {100, 200};
    Vector2 pos = pos_start;
    double speed = 3.;
    int t = 0;
    int dir = 0;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        

        ClearBackground(RAYWHITE);


        test.drawDest();
        test.draw();
        test.drawRange();

        // const char* text = "It Works !";
        // const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
        // DrawText(text, SCREEN_WIDTH / 2 - text_size.x / 2, 100, 20, BLACK);


        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            pos.x += speed;
            dir = 1;
        }
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_Q)) {
            pos.x -= speed;
            dir = 3;
        }
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_Z))   {
            pos.y -= speed;
            dir = 0;
        }
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
            pos.y += speed;
            dir = 2;
        }

        if (IsKeyDown(KEY_P)) { speed += 0.1;}
        if (IsKeyDown(KEY_M)) { speed -= 0.1;}
        if (IsKeyDown(KEY_R)) {pos = pos_start;}

        EndDrawing();
        t++;
        Vect p{pos.x, pos.y};

        test.move(&p);
    }

    CloseWindow();
}

int main(void)
{   
    test_window();
    
    Game::init_game(10, 10, 10, 10);

    return 0;
}
