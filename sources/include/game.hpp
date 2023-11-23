#ifndef GAME
#define GAME

#include "to_include.hpp"

class Game{
private:
    Crewmate* lst_crewmate;
    Impostor* lst_impostor;
    Sherif* lst_Sheriff;
    Task * lst_task;
    int nb_crewmate;
    int nb_sherif;
    int nb_imposter;
    int nb_task;

public:
    double randome(int max, int min);
    void init_game(int nb_cm, int nb_impos, int nb_sherif, int nb_task);
};

#endif