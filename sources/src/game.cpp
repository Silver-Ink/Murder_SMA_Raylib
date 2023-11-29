#include "to_include.hpp"

double Game::randome(int min, int max)
{
    return ((double) (genrand_int31() % (max - min) + min));
}

void Game::init_game(int nb_cm, int nb_impos, int nb_sherif, int nb_task)
{
    int maxIter;
    nb_crewmate = nb_cm;
    lst_crewmate =  new Crewmate[nb_cm];
    lst_impostor = new Impostor[nb_impos];
    lst_task = new Task[nb_task];
    
    for (int i = 0; i < nb_task; i++)
    {
        cout << lst_crewmate[i].get_position().get_x() << lst_crewmate->get_position().get_y() << endl;
    }
}
