#include "to_include.hpp"

Task::Task() {}

Task::Task(Vect pos, int duree)
{
    position = pos;
    duree = duree;
}

int Task::get_duree() {return duree;}
Vect Task::get_position() {return position;}
