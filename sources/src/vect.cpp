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

float Vect::norm_sq()
{
    return x_*x_ + y_* y_;
}
float Vect::norm()
{
    return sqrt(norm_sq());
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

Vect operator+(const Vect& v, const Vect& w)
{
    Vect r(v.x_ + w.x_, v.y_ + w.y_);
    return r;
}
Vect operator-(const Vect& v, const Vect& w)
{
    Vect r(v.x_ - w.x_, v.y_ - w.y_);
    return r;
}

#define PI_SUR_180 3.1415926 / 180.
float Vect::toDeg(float angleRad){return angleRad / PI_SUR_180;}
float Vect::toRad(float angleDeg){return angleDeg * PI_SUR_180;}

Vect &Vect::operator+=(const Vect &v)
{
    x_ += v.x_; y_ += v.y_;
    return *this;
}

Vect &Vect::operator-=(const Vect &v)
{
    x_ -= v.x_; y_ -= v.y_;
    return *this;
}

Vect &Vect::operator*=(const float s)
{
    x_ *= s; y_ *= s;
    return *this;
}

Vect &Vect::operator/=(const float s)
{
    x_ /= s; y_ /= s;
    return *this;
}
