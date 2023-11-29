#ifndef VECT
#define VECT

#include "to_include.hpp"

class Vect
{
private:
    float x_;
    float y_;
public:
    //constructor
    Vect();
    Vect(float x, float y);
    //getter 
    float get_x();
    float get_y();

    //set
    void set_p(float x, float y);
    void set_x(float x);
    void set_y(float y);

    //operator
    float dist_sq(Vect v);
    float dist(Vect v);

    float norm_sq(Vect v);
    float norm(Vect v);

    float angle();
    float angle(Vect v);

    Vector2 toVect2();

};

#endif