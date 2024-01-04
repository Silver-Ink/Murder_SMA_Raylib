#ifndef GAME
#define GAME

#include "to_include.hpp"
#include "../include/amogus.hpp"
#include "../include/task.hpp"

class Game{
public:
    // ===== CONST ======
    /// @brief pourcentage de tache sur le nombre total de taches
    /// présentes qu'un crewmate se voit attribué
    const static float RATIO_TASK_PER_CREWMATE;
    const static float SCREEN_HEIGHT;
    const static float SCREEN_WIDTH ;
private:
    // ===== AMOGUS =====
    /// @brief contients tous les amogus (crewmates, imposteurs)
    /// leur indice dans le vector correspond a leur id.
    static vector<Amogus *> lstAmogus;

    /// @brief nb de crewmates vivants
    static int nb_crewmate;

    /// @brief nb d'imposteurs vivants
    static int nb_impostor;

    // /// @brief nb de crewmate armés vivants
    // int nb_sherif;


    /// ===== TACHES =====
    /// @brief liste des taches présentes sur la map,
    /// une tache peut être assignée a plusieurs crewmate et doit 
    /// donc etre réalisée plusieurs fois.
    static vector<Task *> lstTask;

    /// @brief nombre total de tache pour tous les crewmates
    static int nb_distributed_tasks;

    /// @brief nombre total de taches effectuées
    static int nb_completed_tasks;


public:
    //RNG
    /// @brief entier aléatoire dans [min, max]
    static int rand_int1(int min, int max);
    /// @brief entier aléatoire dans [min, max[
    static int rand_int2(int min, int max);
    /// @brief float aléatoire dans [min, max]
    static float rand_real1(float min, float max);
    /// @brief float aléatoire dans [min, max[
    static float rand_real2(float min, float max);

    //game logic
    static float dt;
    static void generate_entities(int nb_cm, int nb_impos, int nb_sherif, int nb_task);
    static void melange_task(vector<Task*>& listeTask);
    static void update(float dt);
    static void draw();

    //getter
    static int get_nbAmogus();
    static int get_nbAmogusAlive();
    static int get_nbCrewmateAlive();
    static int get_nbImpostorAlive();
    static vector<Amogus *> get_lstAmogus();

    static Amogus* get_AmogusById(int id);

    static int get_nbPhysicalTask();
    static int get_nbTaskPerCrewmate();

    static Task* get_TaskById(int id);
    
    


    //debug
    static void debug_update();
    static Vect debug_txt_pos;
    static Vect debug_txt_pos_def;
    static int debug_txt_size;
    static void drawDebugText(string txt);
    static void drawArrow(Vect& p1, Vect& p2, Color& tint);

        //switch
        static bool show_debug_txt;
        static bool show_all_dest;
        static bool show_all_vision_range;
        static bool show_all_interaction_range;

    static void initScreen();
};

#endif