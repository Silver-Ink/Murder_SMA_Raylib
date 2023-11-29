#include "../include/to_include.hpp"

#define SCREEN_WIDTH (1920)
#define SCREEN_HEIGHT (1080)

#define WINDOW_TITLE "AMOGUS"

int main(void)
{   
    Game *game = new Game();
    game->init_game(10, 10, 10, 10);

    return 0;
}
