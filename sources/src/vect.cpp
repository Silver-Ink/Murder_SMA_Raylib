#include "to_include.hpp"

Vect::Vect() {}

Vect::Vect(float x, float y)
{
    x_ = x;
    y_ = y;
}

float Vect::get_x()
{
    return x_;
}
float Vect::get_y()
{
    return y_;
}

void Vect::set_p(float x, float y)
{
    x_ = x;
    y_ = y;
}
void Vect::set_x(float x)
{
    x_ = x;
}
void Vect::set_y(float y)
{
    y_ = y;
}

float Vect::dist_sq(Vect v)
{
    float x = v.x_ - x_;
    float y = v.y_ - y_;
    return x*x + y*y;
}
float Vect::dist(Vect v)
{
    return sqrt(dist_sq(v));
}

float Vect::norm_sq(Vect v)
{
    return v.x_*v.x_ + v.y_* v.y_;
}
float Vect::norm(Vect v)
{
    return sqrt(norm_sq(v));
}

/// @brief Calcule l'angle du vecteur 
/// @return L'angle du vecteur compris dans ]-π;π]
float Vect::angle()
{
    return atan2(y_, x_);
}
/// @brief Angle du vecteur par rapport au vecteur v
/// @param v 
/// @return 
float Vect::angle(Vect v)
{
    float angle = atan2(v.y_, v.x_) - atan2(y_, x_);
    if (angle > PI)        { angle -= 2 * PI; }
    else if (angle <= -PI) { angle += 2 * PI; }
    return angle;
}

Vector2 Vect::toVect2()
{
    Vector2 v;
    v.x = x_;
    v.y = y_;
    return v;
}