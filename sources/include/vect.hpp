#ifndef DEF_VECT
#define DEF_VECT

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
    

    //other

    float dist_sq(Vect v);
    float dist(Vect v);

    float norm_sq();
    float norm();

    float angle();
    float angle(Vect v);

    Vector2 toVect2();

    void normalise();
    void set_norm(float n);
    //cast
    operator Vector2() const{
        Vector2 v;
        v.x = x_;
        v.y = y_;
        return v;
    }
    

};

#endif