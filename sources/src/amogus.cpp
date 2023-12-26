#include "to_include.hpp"

float const Amogus::DEFAULT_distVision = 100.;
float const Amogus::DEFAULT_distInterract = 10.;
float const Amogus::DEFAULT_vitesse = 2.;

float const Amogus::DRAW_RADIUS = 25;
float const Amogus::DRAW_OUTLINE_RADIUS = 6;


Amogus::Amogus(float x, float y, bool weapon) : 
    position(x, y),
    destination(nullptr),
    distVision(DEFAULT_distVision),
    distInterract(DEFAULT_distInterract),
    vitesse(DEFAULT_vitesse),
    weapon(weapon),
    alive(true),
    highlightColor()
{
    highlightColor.r = Game::rand_int1(50, 225);
    highlightColor.g = Game::rand_int1(50, 225);
    highlightColor.b = Game::rand_int1(50, 225);
    highlightColor.a = 255;
}

Amogus::Amogus() : Amogus(Game::rand_int1(0, 500), Game::rand_int1(0, 500))
{}


//getter
Vect Amogus::get_position() {return position;}
float Amogus::get_vision(){return distVision;}
float Amogus::get_interaction(){return distInterract;}
float Amogus::get_vitesse(){return vitesse;}
bool Amogus::isArmed(){return weapon;}
bool Amogus::isAlive(){return alive;}

//setter
void Amogus::set_position(Vect pos) {position = pos;}
void Amogus::set_interaction(float i){distInterract = i;}
void Amogus::set_vision(float v){distVision = v;}
void Amogus::set_vitesse(float v){vitesse = v;}
void Amogus::setArmed(bool w){weapon = w;}
void Amogus::setAlive(bool life) {alive = life;}

void Amogus::move(Vect* destination)
{
}

void Amogus::update()
{
}

void Amogus::draw()
{
    float x = position.get_x();
    float y = position.get_y();


    DrawCircle(x, y, DRAW_OUTLINE_RADIUS + DRAW_RADIUS, highlightColor);

    DrawCircle(x, y , DRAW_RADIUS, RED);
    // DrawPixel(p.x, p.y, BLACK);
    // DrawRectangle(p.x - AMOGUS_WIDTH /2, p.y - AMOGUS_WIDTH / 2, AMOGUS_WIDTH, AMOGUS_WIDTH, RED);

}

void Amogus::drawDest()
{
}

// void Amogus::initAnim()
// {
//     Spritesheet* s_bg =   new Spritesheet(ASSETS_PATH "BIGamogus_bg.png"   , 32*3);
//     Spritesheet* s_body = new Spritesheet(ASSETS_PATH "BIGamogus_blank.png", 32*3);

//     for (int i = 0; i < 4; i++)
//     {
//         lstAnimBG[i]   = Anim{s_bg  , 6*i, 5 + 6*i, 200};
//         lstAnimBody[i] = Anim{s_body, 6*i, 5 + 6*i, 200};
//     } 
// }

// void Amogus::draw(int t)
// {
//     Vector2 p;
//     p.x = position.get_x();
//     p.y = position.get_y();
//     Amogus::lstAnimBG[dir].drawFrame(p, t, WHITE);
//     Amogus::lstAnimBody[dir].drawFrame(p, t, ColorFromHSV((float)(t%360), 1., 1.));
// }
