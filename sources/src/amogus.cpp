#include "to_include.hpp"

float const Amogus::DEFAULT_distVision = 300.;
float const Amogus::DEFAULT_distInterract = 50.;
float const Amogus::DEFAULT_vitesse = 300.;

float const Amogus::DRAW_RADIUS = 52;
float const Amogus::DRAW_OUTLINE_RADIUS = 4;

int Amogus::nextFreeID = 0;

Spritesheet* Amogus::s_bg = nullptr ;
Spritesheet* Amogus::s_body = nullptr;
Anim* Amogus::lstAnimBG = nullptr;
Anim* Amogus::lstAnimBody = nullptr;
Texture2D Amogus::deadSprite;


Amogus::Amogus(float x, float y, int types) : 
    position(x, y),
    destination(nullptr),
    distVision(DEFAULT_distVision),
    distInterract(DEFAULT_distInterract),
    speed(DEFAULT_vitesse),
    alive(true),
    highlightColor(),
    id(nextFreeID++),
    type(types),
    dir(2),
    follow_dest(true)
{
    highlightColor.r = Game::rand_int1(50, 225);
    highlightColor.g = Game::rand_int1(50, 225);
    highlightColor.b = Game::rand_int1(50, 225);
    highlightColor.a = 255;
}

Amogus::Amogus() : Amogus(Game::rand_int1(0, 500), Game::rand_int1(0, 500), 0)
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
void Amogus::die() {alive = false;}

void Amogus::setDestination(Vect* dest)
{
    destination = dest;
}

/// @brief déplace le amongus peut importe sa destination
/// @param dest position ABSOLUE à vers laquelle se déplacer.
void Amogus::moveToward(Vect dest)
{
    printf("MOVETOWARD\n");
    dest_prioritaire = dest;
    follow_dest = false;
    printf("FIN MOVETOWARD\n");
}

/// @brief déplace le amongus peut importe sa destination
/// @param angle_dir direction par rapport au amongus vers laquelle il se dirige
void Amogus::moveToward(float angle_dir, float distance)
{
    Vect dest = {angle_dir, distance, true};
    moveToward(dest);
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
    Vect* local_dest = destination;
    if (!follow_dest)
    {
        local_dest = &dest_prioritaire;
    }
    else if (destination == nullptr)
        return;

    Vect dir = *local_dest - position;
    updateFacingDir(dir);
    dir.set_length(dt * speed);
    position += dir;
}

int Amogus::get_type()
{
    return type;
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
    if (follow_dest && destination != nullptr)
    {
        Game::drawArrow(position, *destination, highlightColor);
    }
    else if (!follow_dest)
    {
        Game::drawArrow(position, dest_prioritaire, highlightColor);
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

    deadSprite = LoadTexture(ASSETS_PATH "dead.png");
}

void Amogus::draw()
{
    int t = GetTime() * 30;
    Vector2 p;
    DrawCircle(position.get_x(), position.get_y(), DRAW_OUTLINE_RADIUS + DRAW_RADIUS, highlightColor);
    p.x = position.get_x() - 48;
    p.y = position.get_y() - 48;
    if (p.x > -50 && p.x < 1970 && p.y > -50 && p.y < 1130) 
    {
        if (alive)
        {
            Amogus::lstAnimBG[dir].drawFrame(p, t, WHITE);
            Amogus::lstAnimBody[dir].drawFrame(p, t, getRoleColor());
        }
        else
        {
            DrawTextureV(deadSprite, p, getRoleColor());
        }
    }
}
