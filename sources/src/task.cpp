#include "to_include.hpp"


Texture2D Task::sprite;

Task::Task():Task(Vect{0.,0.}, 3) {}

Task::Task(Vect pos, int duree)
{
    position = pos;
    duree = duree;
}

int Task::get_duree() {return duree;}
Vect Task::get_position() {return position;}
void Task::draw()
{
    DrawTexture(sprite, position.get_x() - 48, position.get_y() - 48, WHITE);
}

void Task::initAnim()
{
    sprite = LoadTexture(ASSETS_PATH "Task.png");
}
