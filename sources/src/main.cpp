#include "to_include.hpp"
#include <typeinfo>

#define SCREEN_WIDTH (1920)
#define SCREEN_HEIGHT (1080)

#define WINDOW_TITLE "AMOGUS"

void init_amogus_dance(int n = 10)
{
    Game::generate_entities(n, 0, 0, 0);
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
}

void init_muder_game(int nbrCrewmate, int nbrImpostor, int nbrSherif, int nbrTask)
{
    Game::generate_entities(nbrCrewmate, nbrImpostor, nbrSherif, nbrTask);
    printf("Début?\n");
    printf("oui?\n");
    int n = Game::get_nbAmogus();
    for (int i = 0; i < n; i++)
    {
        if (Game::get_AmogusById(i)->get_type() == 0)
        {
            printf("CrewMate détecté\n");
        }
        else
        {
            printf("Impostor détecté\n");
        }
    }
}

void startGameLoop()
{
    while (!WindowShouldClose())
    {
        Game::initScreen();
        if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) // DEBUG KEY
        {
            Game::debug_update();
        }
        Game::update(Game::dt);
        Game::draw();
        EndDrawing();
    }
}

int main(void)
{   
    init_muder_game(9, 1, 1, 10);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(200);
    Amogus::initAnim();
    Task::initAnim();
    startGameLoop();
    CloseWindow();    

    return 0;
}
