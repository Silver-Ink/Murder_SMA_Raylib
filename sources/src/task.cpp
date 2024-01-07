#include "to_include.hpp"


Texture2D Task::sprite;

int Task::nextFreeID = 0;

Task::Task():Task(0., 0., 3) {}

Task::Task(float x, float y, int durees) :
position(x, y),
duree(durees),
id(nextFreeID++)
{

}

/// @brief Retourne la durée de la tâche
/// @return la durée de la tâche
int Task::get_duree() {return duree;}

/// @brief retourne la position de la tâche
/// @return la position de la tâche
Vect& Task::get_position() {return position;}

/// @brief retourne l'adresse de la position de la tâche
/// @return l'adresse de la position de la tâche
Vect* Task::get_adr_position() {return &position;}

/// @brief retourne l'id de la tâche
/// @return l'id de la tâche
int Task::get_taskId() {return id;}

/// @brief retourne l'id de la classe
/// @return l'id de la classe
int Task::getNextFreeId(){return nextFreeID;}

/// @brief dessine le sprite d'une tâche
void Task::draw()
{
    DrawTexture(sprite, position.get_x() - 48, position.get_y() - 48, WHITE);
    DrawText(to_string(id).c_str(), position.get_x(), position.get_y(), 15, BLACK);
}

/// @brief initialise l'animation de la tâche
void Task::initAnim()
{
    sprite = LoadTexture(ASSETS_PATH "Task.png");
}
