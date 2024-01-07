#include "to_include.hpp"


const float Game::RATIO_TASK_PER_CREWMATE = .7;
const float Game::SCREEN_HEIGHT = 1080.;
const float Game::SCREEN_WIDTH = 1920.;


float Game::dt = 0;

/// @brief Génère de nouveaux amogus pour une nouvelle partie
/// @param nb_cm nombre de crewmate (comprends le nb de shérifs)
/// @param nb_impos nombre d'imosteurs
/// @param nb_sherif nombre de crewmates armés dès le départ et sans tasks (inclus dans nb_cm)
/// @param nb_task nombre de taches sur la map
void Game::generate_entities(int nb_cm, int nb_impos, int nb_sherif, int nb_task)
{
    // int maxIter;
    vector<Task*> listetask;
    nb_crewmate = nb_cm;
    nb_impostor = nb_impos;

    lstTask.reserve(nb_task);
    lstAmogus.reserve(nb_cm + nb_impos);

    float rand1, rand2;
    int rand3; //temps necessaire pour faire la tâche
    
    int nbTx = ceil(sqrtf(nb_task));
    int nbTy = ceil(nb_task / nbTx);

    float xStep = (SCREEN_WIDTH - Crewmate::DRAW_RADIUS * 4)  / nbTx;
    float yStep = (SCREEN_HEIGHT - Crewmate::DRAW_RADIUS * 8) / nbTy;



    for (int i = 0; i < nb_task; i++)
    {
        float xGrid = floorf(i% nbTx);
        float yGrid = floorf(i/ nbTy);

        // rand1 = rand_real2(Crewmate::DRAW_RADIUS, SCREEN_WIDTH - Crewmate::DRAW_RADIUS);
        // rand2 = rand_real2(Crewmate::DRAW_RADIUS, SCREEN_HEIGHT - Crewmate::DRAW_RADIUS);
        rand1 = rand_real2(xGrid * xStep, (xGrid+1) * xStep) + Crewmate::DRAW_RADIUS * 2;
        rand2 = rand_real2(yGrid * yStep, (yGrid+1) * yStep) + Crewmate::DRAW_RADIUS * 2;
        // rand1 = SCREEN_WIDTH - Crewmate::DRAW_RADIUS*2;
        printf("x =%lf\ty = %lf\n", rand1, rand2);
        rand3 = rand_int2(0, 10);
        lstTask.push_back(new Task(rand1, rand2, rand3));
    }

    listetask.assign(lstTask.begin(), lstTask.end());

    for (int i = 0; i < nb_impos; i++)
    {
        rand1 = rand_real2(Crewmate::DRAW_RADIUS, SCREEN_WIDTH - Crewmate::DRAW_RADIUS);
        rand2 = rand_real2(Crewmate::DRAW_RADIUS, SCREEN_HEIGHT - Crewmate::DRAW_RADIUS);
        printf("%lf && %lf et %d\n", rand1, rand2, i);
        Imposteur* newImpos = new Imposteur(rand1, rand2, 1);
        lstAmogus.push_back(newImpos); 
    }

    for (int i = 0; i < nb_cm; i++)
    {
        rand1 = rand_real2(Crewmate::DRAW_RADIUS, SCREEN_WIDTH - Crewmate::DRAW_RADIUS);
        rand2 = rand_real2(Crewmate::DRAW_RADIUS, SCREEN_HEIGHT - Crewmate::DRAW_RADIUS);
        printf("%lf && %lf et %d\n", rand1, rand2, i);
        Crewmate* newCrewmate = new Crewmate(rand1, rand2, nb_sherif-- > 0);
        if (nb_sherif < 1)
        {
            melange_task(listetask);
            newCrewmate->setTask(listetask);

        }
        lstAmogus.push_back(newCrewmate); 
    }
    printf("FIN\n");
}

/// @brief Détermine si la partie est terminée ou pas
/// @return un booléan (true si partie terminée)
bool Game::testEndGame()
{
    //printf("C: %d , I: %d\n", get_nbCrewmateAlive(), get_nbImpostorAlive());
    return (get_nbCrewmateAlive() == 0 ||get_nbImpostorAlive() == 0);
}

/// @brief Appelle la fonction update de chaque Amongus
/// @param dt delta time
void Game::update(float dt)
{
    vector<Amogus*>::iterator amgs;
    for (amgs = lstAmogus.begin(); amgs != lstAmogus.end(); amgs++)
    {
        (*amgs)->update(dt);
    }
}

/// @brief Met à jour la nouvelle destination de chaque amongus
void Game::nextDest()
{
    vector<Amogus*>::iterator amgs;
    for (amgs = lstAmogus.begin(); amgs != lstAmogus.end(); amgs++)
    {
        (*amgs)->findNextDest();
    }
}

/// @brief Dessine les informations du Amongus
void Game::draw()
{
    vector<Amogus*>::iterator amgs;
    for (amgs = lstAmogus.begin(); amgs != lstAmogus.end(); amgs++)
    {
        (*amgs)->draw();
        if (Game::show_all_interaction_range)
        {
            (*amgs)->drawInteractRange();
        }
        if (Game::show_all_vision_range)
        {
            (*amgs)->drawVisionRange();
        }
        if (Game::show_all_dest)
        {
            (*amgs)->drawDest();
        }
    }
    vector<Task*>::iterator task;
    for (task = lstTask.begin(); task != lstTask.end(); task++)
    {
        (*task)->draw();
    }
    
    Vector2 pos = {-110, -100};
    Amogus::lstAnimBody[1].drawFrame(pos, 0, WHITE);
    
}

/// @brief Mélange des tâches dans une liste
/// @param listeTask (la liste à mélanger)
void Game::melange_task(vector<Task*>& listeTask)
{
    int rand1, rand2;
    for (int i = 0; i < listeTask.size(); i++)
    {
        rand1 = rand_int2(0, ((int) (listeTask.size())));
        rand2 = rand_int2(0, ((int) (listeTask.size())));
        std::swap(listeTask[rand1], listeTask[rand2]);
    }
}

/// @brief Retourne le nombre d'amongus
/// @return le nombre d'amongus
int Game::get_nbAmogus()
{
	return lstAmogus.capacity();
}

/// @brief Retourne le nombre d'amongus encore en vie
/// @return le nombre d'amongus encore en vie
int Game::get_nbAmogusAlive()
{
	return nb_crewmate + nb_impostor;
}

/// @brief Retourne le nombre de crewmate encore en vie
/// @return le nombre de crewmate encore en vie
int Game::get_nbCrewmateAlive()
{
	return nb_crewmate;
}

/// @brief Retourne le nombre d'imposteur encore en vie
/// @return le nombre d'imposteur encore en vie
int Game::get_nbImpostorAlive()
{
	return nb_impostor;
}

/// @brief Décrémente le nombre de crewmate encore en vie
void Game::killCrewmate()
{
    nb_crewmate--;
}

/// @brief Décrémente le nombre d'imposteur encore en vie
void Game::killImposteur()
{
    nb_impostor--;
}

/// @brief Récupère l'amongus correspondant par rapport à son id
/// @param id id de l'amongus
/// @return l'amongus en question
Amogus* Game::get_AmogusById(int id)
{
	return lstAmogus[id];
}

/// @brief Récupère la tâche correspondant par rapport à son id
/// @param id id de la tâche
/// @return la tâche en question
Task* Game::get_TaskById(int id)
{
	return lstTask[id];
}

/// @brief récupère le nombre totale de tâches
/// @return le nombre totale de tâches
int Game::get_nbPhysicalTask()
{
    return lstTask.capacity();
}

/// @brief récupère le nombre totale de tâche à faire par crewmate
/// @return le nombre de tâches totale à faire par crewmate
int Game::get_nbTaskPerCrewmate()
{
    return (int)(RATIO_TASK_PER_CREWMATE * (float)get_nbPhysicalTask());
}

/// @brief retourne la liste d'amongus
/// @return la liste d'amongus
vector<Amogus *> Game::get_lstAmogus()
{
    return lstAmogus;
}

/// @brief Intialise l'affichage
void Game::initScreen()
{
    dt = GetFrameTime();
    BeginDrawing();

    ClearBackground(RAYWHITE);
    debug_txt_pos = debug_txt_pos_def;
    drawDebugText("FPS : " + std::to_string(GetFPS()));
}

vector<Amogus *> Game::lstAmogus = vector<Amogus *>{};
int Game::nb_crewmate = 0;
int Game::nb_impostor = 0;

vector<Task *> Game::lstTask = vector<Task *>{};
int Game::nb_distributed_tasks = 0;
int Game::nb_completed_tasks = 0;

// =============== DEBUG ====================

void Game::debug_update()
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

int Game::debug_txt_size = 30;
Vect Game::debug_txt_pos_def = Vect(10, 10);
Vect Game::debug_txt_pos = Vect(10, 10);
void Game::drawDebugText(string txt)
{
    if (show_debug_txt)
    {
        DrawText(txt.c_str(), debug_txt_pos.get_x(), debug_txt_pos.get_y(), debug_txt_size, GRAY);
        const Vector2 text_size = MeasureTextEx(GetFontDefault(), txt.c_str(), debug_txt_size, 1);
        debug_txt_pos += Vect(0, text_size.y);
    }
}

void Game::drawArrow(Vect& p1, Vect& p2, Color& tint)
{
    DrawLineEx((Vector2)p1,
                   (Vector2)(p2),
                   3.,
                   tint);
        // DrawLineBezier((Vector2)position, (Vector2)(*destination), 4., highlightColor);
        

        // float edge = 10;
        // float angle = (p1 - p2).angle();
        // Vector2 v1{};
        // float angleOffSet = Vect::toRad(30);
        // v1.x = p1.get_x() - cos(angle - angleOffSet) * edge;
        // v1.y = p1.get_y() - sin(angle - angleOffSet) * edge;
        // Vector2 v2{};
        // v2.x = p2.get_x() - cos(angle + angleOffSet) * edge;
        // v2.y = p2.get_y() - sin(angle + angleOffSet) * edge;
        // DrawTriangle((Vector2)(p2), v2, v1, tint);
}
bool Game::show_debug_txt = true;
bool Game::show_all_dest = false;
bool Game::show_all_interaction_range = false;
bool Game::show_all_vision_range = false;

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