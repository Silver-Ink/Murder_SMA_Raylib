#ifndef GAME
#define GAME

#include "to_include.hpp"

class Game{
private:
    // Crewmate* lst_crewmate;
    // Impostor* lst_impostor;
    // Sherif* lst_Sheriff;
    Task * lst_task;
    int nb_crewmate;
    int nb_sherif;
    int nb_imposter;
    int nb_task;

public:

    /// @brief entier aléatoire dans [min, max]
    static int rand_int1(int min, int max);
    /// @brief entier aléatoire dans [min, max[
    static int rand_int2(int min, int max);
    /// @brief float aléatoire dans [min, max]
    static float rand_real1(float min, float max);
    /// @brief float aléatoire dans [min, max[
    static float rand_real2(float min, float max);


    void init_game(int nb_cm, int nb_impos, int nb_sherif, int nb_task);
};

#endif