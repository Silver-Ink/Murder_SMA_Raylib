#include "to_include.hpp"

Vect::Vect() {}

Vect::Vect(double x, double y)
{
    x_ = x;
    y_ = y;
}

double Vect::get_x()
{
    return x_;
}
double Vect::get_y()
{
    return y_;
}

void Vect::set_p(double x, double y)
{
    x_ = x;
    y_ = y;
}
void Vect::set_x(double x)
{
    x_ = x;
}
void Vect::set_y(double y)
{
    y_ = y;
}

double Vect::dist_sq(Vect v)
{
    double x = v.x_ - x_;
    double y = v.y_ - y_;
    return x*x + y*y;
}
double Vect::dist(Vect v)
{
    return sqrt(dist_sq(v));
}

double Vect::norm_sq(Vect v)
{
    return v.x_*v.x_ + v.y_* v.y_;
}
double Vect::norm(Vect v)
{
    return sqrt(norm_sq(v));
}

/// @brief Calcule l'angle du vecteur 
/// @return L'angle du vecteur compris dans ]-π;π]
double Vect::angle()
{
    return atan2(y_, x_);
}
/// @brief Angle du vecteur par rapport au vecteur v
/// @param v 
/// @return 
double Vect::angle(Vect v)
{
    double angle = atan2(v.y_, v.x_) - atan2(y_, x_);
    if (angle > PI)        { angle -= 2 * PI; }
    else if (angle <= -PI) { angle += 2 * PI; }
    return angle;
}