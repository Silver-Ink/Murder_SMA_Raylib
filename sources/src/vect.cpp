#include "to_include.hpp"

Vect::Vect() {}

/// @param x si polar, ce paramètre est l'ANGLE
/// @param y si polar, ce paramètre est la NORME
/// @param polar false par défaut
Vect::Vect(float x, float y, bool polar)
{
    if (polar)
    {
        x_ = cos(x) * y;
        y_ = sin(x) * y; 
    }
    else
    {
        x_ = x;
        y_ = y;
    }
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

float Vect::length_sq()
{
    return x_*x_ + y_* y_;
}
float Vect::length()
{
    return sqrt(length_sq());
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

void Vect::normalize()
{
    set_length(1.);
}

void Vect::set_length(float l)
{
    float new_length = l/length();
    x_ *= new_length;
    y_ *= new_length;
}

bool Vect::in(Vect v, float range)
{
    float coord = (v.get_x() - x_) * (v.get_x() - x_) + (v.get_y() - y_) * (v.get_y() - y_);
    return (coord <= range * range);
}

Vect Vect::fromVector2(Vector2& v)
{
    Vect v2{v.x, v.y};
    return v2;
}
Vect Vect::fromVector2(const Vector2& v)
{
    Vect v2{v.x, v.y};
    return v2;
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
