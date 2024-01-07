#include "to_include.hpp"

/// @brief Contient les informations et les données sur la spritesheet
/// @param filename nom de l'image a charger
/// @param frameSize largeur d'une frame de la spritesheet
Spritesheet::Spritesheet(string filename, int frameSize) :
                         frameSize(frameSize)
{
    texture = LoadTexture(filename.c_str());
    nbFrameW = texture.width  / frameSize;
    nbFrameH = texture.height / frameSize;
    nbFrame = nbFrameH * nbFrameW;

    lstFrame = new Rectangle[nbFrame];

    for (int i = 0; i < nbFrameH; i++)
    {
        for (int j = 0; j < nbFrameW; j++)
        {
            int framePos = i * nbFrameW + j;
            lstFrame[framePos].x = (float) (j * frameSize);
            lstFrame[framePos].y = (float) (i * frameSize);
            lstFrame[framePos].width  = (float)(frameSize);
            lstFrame[framePos].height = (float)(frameSize);
        }
    }
}

/// @brief Réccupère les coordonnées d'une image depuis la liste d'image
/// @param frameID id de l'image voulue
/// @return coordonnées de l'image actuelle
Rectangle Spritesheet::getFrame(int frameID)
{
    return  lstFrame[frameID];
}
int Spritesheet::getNbFrame()
{
    return nbFrame;
}

Anim::Anim() {}
Anim::Anim(string filename, int frameSize, int start, int end, int fps) : 
            Anim(new Spritesheet(filename, frameSize), start, end, fps)
            {}

/// @brief créée une animation étant un partie des images dans une spritesheet
/// @param s spritesheet a utiliser pour l'image
/// @param start image de début
/// @param end image de fin
/// @param fps image par seconde
Anim::Anim(Spritesheet* s, int start, int end, int fps)
{
    spritesheet = s;
    frameDuration = 1000 / fps;
    frameStart = start;
    frameEnd = end;
    if (frameEnd == -1 )
    {
        frameEnd = s->getNbFrame() - 1;                                                                                                                                                   
    }            
    frameEnd ++;
}

/// @brief Dessine l'animation au temps t
/// @param pos position de dessin
/// @param t moment de l'animation a dessiner (timer)
/// @param tint couleur
void Anim::drawFrame(Vector2 pos, int t, Color tint)
{
    int frameID;
    // printf("t = %d\n", t);
    // printf("frameEnd = %d\n", frameEnd);
    // printf("frameStart = %d\n", frameStart);
    // printf("frameDuration = %d\n", frameDuration);
    if (frameDuration != 0)
        frameID = (t / frameDuration) % (frameEnd - frameStart) + frameStart;
    // cout << frameID << endl;
    DrawTextureRec(spritesheet->texture, spritesheet->getFrame(frameID), pos, tint); 
    // cout << "1" << spritesheet->texture.id << endl;
    // cout << "2" << spritesheet->getFrame(0).height << endl;
    // cout << "3" <<spritesheet->getNbFrame() << endl;
    // cout << "4" <<pos.x << endl;
    // cout << "5" <<tint.b << endl;
    // cout << "end " << endl;
    // DrawTextureRec(spritesheet->texture, Rectangle{0., 0., 16., 16.} , Vector2{}, tint); 
}

/// @brief Récupère le temps necessaire à une animation complète
/// @return le temps necessaire à une animation complète
int Anim::getAnimDuration()
{
    return (frameEnd - frameStart) * frameDuration;
}