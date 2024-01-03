#include "to_include.hpp"

float const Amogus::DEFAULT_distVision = 600.;
float const Amogus::DEFAULT_distInterract = 20.;
float const Amogus::DEFAULT_vitesse = 20.;

float const Amogus::DRAW_RADIUS = 52;
float const Amogus::DRAW_OUTLINE_RADIUS = 4;

int Amogus::nextFreeID = 0;

Spritesheet* Amogus::s_bg = nullptr ;
Spritesheet* Amogus::s_body = nullptr;
Anim* Amogus::lstAnimBG = nullptr;
Anim* Amogus::lstAnimBody = nullptr;


Amogus::Amogus(float x, float y) : 
    position(x, y),
    destination(nullptr),
    distVision(DEFAULT_distVision),
    distInterract(DEFAULT_distInterract),
    speed(DEFAULT_vitesse),
    alive(true),
    highlightColor(),
    id(nextFreeID++),
    dir(0)
{
    highlightColor.r = Game::rand_int1(50, 225);
    highlightColor.g = Game::rand_int1(50, 225);
    highlightColor.b = Game::rand_int1(50, 225);
    highlightColor.a = 255;
}

Amogus::Amogus() : Amogus(Game::rand_int1(0, 500), Game::rand_int1(0, 500))
{}


//getter
Vect& Amogus::get_position() {return position;}
float Amogus::get_vision(){return distVision;}
float Amogus::get_interaction(){return distInterract;}
float Amogus::get_speed(){return speed;}
bool Amogus::isAlive(){return alive;}
int Amogus::getNextFreeId(){return nextFreeID;}

//setter
void Amogus::set_position(Vect pos) {position = pos;}
void Amogus::set_interaction(float i){distInterract = i;}
void Amogus::set_vision(float v){distVision = v;}
void Amogus::set_speed(float v){speed = v;}
void Amogus::setAlive(bool life) {alive = life;}

void Amogus::moveToward(Vect* dest)
{
    destination = dest;
}


/// @brief Change la direction du sprite utilisé
/// @param direction vecteur de direction du déplacement
void Amogus::updateFacingDir(Vect& direction)
{
    int d = direction.angle() / PI * 4. + 4.; // [0, 7]
    if (d == 0) {d = 8;}                      // [1, 8]
    d --;                                     // [0, 7]
    d /= 2;                                   // [0, 3]
    dir = d;
}

void Amogus::update(float dt)
{
    Vect directionVect = *destination - position;
    updateFacingDir(directionVect);
    directionVect.set_length(dt * speed);
    position += directionVect;
}

// void Amogus::draw()
// {
//     float x = position.get_x();
//     float y = position.get_y();


//     DrawCircle(x, y, DRAW_OUTLINE_RADIUS + DRAW_RADIUS, highlightColor);

//     DrawCircle(x, y , DRAW_RADIUS, BLUE);
//     // DrawPixel(p.x, p.y, BLACK);
//     // DrawRectangle(p.x - AMOGUS_WIDTH /2, p.y - AMOGUS_WIDTH / 2, AMOGUS_WIDTH, AMOGUS_WIDTH, RED);

// }

void Amogus::drawDest()
{
    if (destination != nullptr)
    {
        DrawLineEx((Vector2)position,
                   (Vector2)(*destination),
                   3.,
                   highlightColor);
        // DrawLineBezier((Vector2)position, (Vector2)(*destination), 4., highlightColor);
        

        float edge = 10;
        float angle = (*destination - position).angle();
        Vector2 v1{};
        float angleOffSet = Vect::toRad(30);
        v1.x = destination->get_x() - cos(angle - angleOffSet) * edge;
        v1.y = destination->get_y() - sin(angle - angleOffSet) * edge;
        Vector2 v2{};
        v2.x = destination->get_x() - cos(angle + angleOffSet) * edge;
        v2.y = destination->get_y() - sin(angle + angleOffSet) * edge;
        DrawTriangle((Vector2)(*destination), v2, v1, highlightColor);
    }
    else
    {
        float x = position.get_x();
        float y = position.get_y();
        float os = DRAW_RADIUS * .5;
        DrawLine(x + os, y + os, x - os, y - os, BLACK);
        DrawLine(x - os, y + os, x + os, y - os, BLACK);
    }
}

void Amogus::drawVisionRange()
{
    DrawCircleLinesV((Vector2)position, distVision, GRAY);
}
void Amogus::drawInteractRange()
{
    DrawCircleLinesV((Vector2)position, distInterract, LIME);
}

void Amogus::initAnim()
{
    Spritesheet* s_bg =   new Spritesheet(ASSETS_PATH "BIGamogus_bg.png"   , 32*3);
    Spritesheet* s_body = new Spritesheet(ASSETS_PATH "BIGamogus_blank.png", 32*3);

    lstAnimBG   = new Anim[4];
    lstAnimBody = new Anim[4];

    for (int i = 0; i < 4; i++)
    {
        lstAnimBG[i]   = Anim{s_bg  , 6*i, 5 + 6*i, 200};
        lstAnimBody[i] = Anim{s_body, 6*i, 5 + 6*i, 200};
    } 
}

void Amogus::draw()
{
    int t = GetTime() * 30;
    Vector2 p;
    DrawCircle(position.get_x(), position.get_y(), DRAW_OUTLINE_RADIUS + DRAW_RADIUS, highlightColor);
    p.x = position.get_x() - 48;
    p.y = position.get_y() - 48;
    Amogus::lstAnimBG[dir].drawFrame(p, t, WHITE);
    Amogus::lstAnimBody[dir].drawFrame(p, t, ColorFromHSV((float)(t%360), 1., 1.));
}
