#include "to_include.hpp"

#define SCREEN_WIDTH (1920)
#define SCREEN_HEIGHT (1080)

#define WINDOW_TITLE "AMOGUS"

void test_window()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    // SetWindowState(FLAG_FULLSCREEN_MODE);
    SetTargetFPS(180);


    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        BeginDrawing();
        
        Game::clearScreen();
        Game::drawDebugText("FPS : " + std::to_string(GetFPS()));
        
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
            if (IsKeyPressed(KEY_D))
            {
                Game::show_all_dest ^= 1; 
            }
            if (IsKeyPressed(KEY_V))
            {
                Game::show_all_vision_range ^= 1; 
            }
            if (IsKeyPressed(KEY_I))
            {
                Game::show_all_interaction_range ^= 1; 
            }

        }
        else
        {
            // if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            //     pos.x += speed * dt;
            //     dir = 1;
            // }
            // if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_Q)) {
            //     pos.x -= speed * dt;
            //     dir = 3;
            // }
            // if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_Z))   {
            //     pos.y -= speed * dt;
            //     dir = 0;
            // }
            // if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
            //     pos.y += speed * dt;
            //     dir = 2;
            // }

            // if (IsKeyDown(KEY_P)) { speed += 0.1;}
            // if (IsKeyDown(KEY_M)) { speed -= 0.1;}
            // if (IsKeyDown(KEY_R)) {pos = pos_start;}
        }
        Game::update(dt);
        Game::draw();

        EndDrawing();
    }

    CloseWindow();
}

int main(void)
{   
    int n = 25;
    Game::init_game(n, 0, 0, 0);
    Vect screenCenter{SCREEN_WIDTH / 2., SCREEN_HEIGHT / 2.};
    float rad = 300;

    for (int i = 0; i < n; i++)
    {
        if (i < n-1)
        {
            Game::get_AmogusById(i)->moveToward(&(Game::get_AmogusById(i+1)->get_position()));
        }
        float a = PI * 2 / n * i;
        Vect offset{cos(a) * rad, sin(a) * rad};
        Game::get_AmogusById(i)->set_position(screenCenter + offset);
    }
    Game::get_AmogusById(n-1)->moveToward(&(Game::get_AmogusById(0)->get_position()));
    
    test_window();
    

    return 0;
}
