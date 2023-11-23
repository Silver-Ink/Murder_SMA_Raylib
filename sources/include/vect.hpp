#ifndef VECT
#define VECT

class Vect
{
private:
    double x_;
    double y_;
public:
    //constructor
    Vect();
    Vect(double x, double y);
    //getter 
    double get_x();
    double get_y();

    //set
    void set_p(double x, double y);
    void set_x(double x);
    void set_y(double y);

    //operator
    double dist_sq(Vect v);
    double dist(Vect v);

    double norm_sq(Vect v);
    double norm(Vect v);

    double angle();
    double angle(Vect v);

};

#endif