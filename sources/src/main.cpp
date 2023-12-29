#include "to_include.hpp"

#define SCREEN_WIDTH (1920)
#define SCREEN_HEIGHT (1080)

#define WINDOW_TITLE "AMOGUS"

void test_window()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    // SetWindowState(FLAG_FULLSCREEN_MODE);
    SetTargetFPS(180);
    Crewmate test;
    
    
    Vector2 pos_start = {100, 200};
    Vector2 pos = pos_start;
    double speed = 200.;
    int t = 0;
    int dir = 0;
    while (!WindowShouldClose())
    {
        double dt = GetFrameTime();
        BeginDrawing();
        

        Game::clearScreen();
        Game::drawDebugText("FPS : " + std::to_string(GetFPS()));

        test.drawDest();
        test.draw();
        test.drawRange();

        // const char* text = "It Works !";
        // const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
        // DrawText(text, SCREEN_WIDTH / 2 - text_size.x / 2, 100, 20, BLACK);

        if (IsKeyDown(KEY_TAB)) // DEBUG KEY
        {
            if (IsKeyPressedRepeat(KEY_EQUAL) || IsKeyPressedRepeat(KEY_KP_ADD) ||
                IsKeyPressed(KEY_EQUAL) || IsKeyPressed(KEY_KP_ADD))
            {
                Game::debug_txt_size ++;
            }
            if ((IsKeyPressedRepeat(KEY_SIX) || IsKeyPressedRepeat(KEY_KP_SUBTRACT) ||
                IsKeyPressed(KEY_SIX) || IsKeyPressed(KEY_KP_SUBTRACT)
                ) && 
                Game::debug_txt_size > 0)
            {
                Game::debug_txt_size --;
            }
            if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN))
            {
                Game::debug_txt_pos_def += Vect{0, 10};
            }
            if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP))
            {
                Game::debug_txt_pos_def -= Vect{0, 10};
            }
            if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT))
            {
                Game::debug_txt_pos_def -= Vect{10, 0};
            }
            if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT))
            {
                Game::debug_txt_pos_def += Vect{10, 0};
            }
            if (IsKeyPressed(KEY_SPACE))
            {
                Game::show_debug_txt ^= 1; 
            }

        }
        else
        {
            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
                pos.x += speed * dt;
                dir = 1;
            }
            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_Q)) {
                pos.x -= speed * dt;
                dir = 3;
            }
            if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_Z))   {
                pos.y -= speed * dt;
                dir = 0;
            }
            if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
                pos.y += speed * dt;
                dir = 2;
            }

            if (IsKeyDown(KEY_P)) { speed += 0.1;}
            if (IsKeyDown(KEY_M)) { speed -= 0.1;}
            if (IsKeyDown(KEY_R)) {pos = pos_start;}
        }
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
