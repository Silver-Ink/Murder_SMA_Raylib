#include "to_include.hpp"


const float Game::RATIO_TASK_PER_CREWMATE = .7;


/// @brief Génère de nouveaux amogus pour une nouvelle partie
/// @param nb_cm nombre de crewmate (comprends le nb de shérifs)
/// @param nb_impos nombre d'imosteurs
/// @param nb_sherif nombre de crewmates armés dès le départ et sans tasks (inclus dans nb_cm)
/// @param nb_task nombre de taches sur la map
void Game::init_game(int nb_cm, int nb_impos, int nb_sherif, int nb_task)
{
    // int maxIter;
    nb_crewmate = nb_cm;
    nb_impostor = nb_impos;

    lstTask.reserve(nb_task);
    lstAmogus.reserve(nb_cm + nb_impos);

    for (int i = 0; i < nb_task; i++)
    {
        lstTask.push_back(new Task{});
    }
    

    for (int i = 0; i < nb_impos; i++)
    {
        lstAmogus.push_back(new Imposteur{});
    }
    for (int i = 0; i < nb_cm; i++)
    {
        lstAmogus.push_back(new Crewmate(0, 0, nb_sherif-- > 0));
    }

}

int Game::get_nbAmogus()
{
	return lstAmogus.capacity();
}

int Game::get_nbAmogusAlive()
{
	return nb_crewmate + nb_impostor;
}

int Game::get_nbCrewmateAlive()
{
	return nb_crewmate;
}

int Game::get_nbImpostorAlive()
{
	return nb_impostor;
}

Amogus* Game::get_AmogusById(int id)
{
	return lstAmogus[id];
}

Task* Game::get_TaskById(int id)
{
	return lstTask[id];
}

int Game::get_nbPhysicalTask()
{
    return lstTask.capacity();
}

int Game::get_nbTaskPerCrewmate()
{
    return (int)(RATIO_TASK_PER_CREWMATE * (float)get_nbPhysicalTask());
}


int Game::debug_txt_size = 30;
Vect Game::debug_txt_pos_def = Vect(10, 10);
Vect Game::debug_txt_pos = Vect(10, 10);
bool Game::show_debug_txt = true;
void Game::drawDebugText(string txt)
{
    if (show_debug_txt)
    {
        DrawText(txt.c_str(), debug_txt_pos.get_x(), debug_txt_pos.get_y(), debug_txt_size, GRAY);
        const Vector2 text_size = MeasureTextEx(GetFontDefault(), txt.c_str(), debug_txt_size, 1);
        debug_txt_pos += Vect(0, text_size.y);
    }
}

void Game::clearScreen()
{
    ClearBackground(RAYWHITE);
    debug_txt_pos = debug_txt_pos_def;
}

vector<Amogus *> Game::lstAmogus = vector<Amogus *>{};
int Game::nb_crewmate = 0;
int Game::nb_impostor = 0;

vector<Task *> Game::lstTask = vector<Task *>{};
int Game::nb_distributed_tasks = 0;
int Game::nb_completed_tasks = 0;

// =============== RANDOM ====================

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