#include "to_include.hpp"

int Task::nextFreeID = 0;

Task::Task():Task(0., 0., 3) {}

Task::Task(float x, float y, int durees) :
position(x, y),
duree(durees),
id(nextFreeID++)
{

}

int Task::get_duree() {return duree;}
Vect Task::get_position() {return position;}
int Task::getNextFreeId(){return nextFreeID;}
