#include "to_include.hpp"

Task::Task():Task(Vector2{0.,0.}, 3) {}

Task::Task(Vector2 pos, int duree)
{
    position = pos;
    duree = duree;
}

int Task::get_duree() {return duree;}
Vector2 Task::get_position() {return position;}
