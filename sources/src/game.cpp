#include "to_include.hpp"

double Game::randome(int min, int max)
{
    return ((double) (genrand_int31() % (max - min) + min));
}

void Game::init_game(int nb_cm, int nb_impos, int nb_sherif, int nb_task)
{
    int maxIter;
    nb_crewmate = nb_cm;
    lst_crewmate = (Crewmate*) malloc(sizeof(Crewmate)*nb_cm);
    lst_impostor = (Impostor*) malloc(sizeof(Impostor)*nb_impos);
    lst_task = (Task*) malloc(sizeof(Task)*nb_task);
    
    for (int i = 0; i < nb_task; i++)
    {
        Task * task = new Task();
        Vect * pos = new Vect();
    }
}
