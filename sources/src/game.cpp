#include "to_include.hpp"

/// @brief entier aléatoire dans [min, max]
int Game::rand_int1(int min, int max)
{
    return (genrand_int31() % (max+1 - min) + min);
}
/// @brief entier aléatoire dans [min, max[
int Game::rand_int2(int min, int max)
{
    return (genrand_int31() % (max - min) + min);
}

/// @brief float aléatoire dans [min, max]
float Game::rand_real1(float min, float max)
{
    return genrand_real1() * (max - min) + min;
}

/// @brief float aléatoire dans [min, max[
float Game::rand_real2(float min, float max)
{
    return genrand_real2() * (max - min) + min;
}

void Game::init_game(int nb_cm, int nb_impos, int nb_sherif, int nb_task)
{
    int maxIter;
    nb_crewmate = nb_cm;
    // lst_crewmate =  new Crewmate[nb_cm];
    // lst_impostor = new Impostor[nb_impos];
    lst_task = new Task[nb_task];
    
    // for (int i = 0; i < nb_task; i++)
    // {
    //     cout << lst_crewmate[i].get_position().get_x() << lst_crewmate->get_position().get_y() << endl;
    // }
}
