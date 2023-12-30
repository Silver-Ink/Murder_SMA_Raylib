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

    float length_sq();
    float length();

    float angle();
    float angle(Vect v);

    void normalize();
    void set_length(float l);
    //cast
    operator Vector2() const{
        Vector2 v;
        v.x = x_;
        v.y = y_;
        return v;
    }

    static Vect fromVector2(Vector2& v); 
    static Vect fromVector2(const Vector2& v); 

    static float toDeg(float angleRad);
    static float toRad(float angleDeg);
    
    //operators
    Vect& operator+=(const Vect& v);
    Vect& operator-=(const Vect& v);
    Vect& operator*=(const float s);
    Vect& operator/=(const float s);

    //friend operators
    friend Vect operator+(const Vect& v, const Vect& w);
    friend Vect operator-(const Vect& v, const Vect& w);

};

#endif