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

int Task::get_duree() {return duree;}

Vect& Task::get_position() {return position;}

Vect* Task::get_adr_position() {return &position;}

int Task::get_taskId() {return id;}

int Task::getNextFreeId(){return nextFreeID;}

void Task::draw()
{
    DrawTexture(sprite, position.get_x() - 48, position.get_y() - 48, WHITE);
    DrawText(to_string(id).c_str(), position.get_x(), position.get_y(), 15, BLACK);
}

void Task::initAnim()
{
    sprite = LoadTexture(ASSETS_PATH "Task.png");
}
