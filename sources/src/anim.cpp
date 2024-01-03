#include "to_include.hpp"

Spritesheet::Spritesheet(string filename, int frameSize) :
                         frameSize(frameSize)
{
    cout << "-" << endl;
    cout << filename.c_str() << endl;
    cout << "-" << endl;
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
    cout << 'j' <<j << endl;
        }
    cout << 'i' << i << endl;
    }
    cout << "Spritesheet initialisee" << endl;
}

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

    cout << frameEnd << endl;            
    cout << "Anim init !" << endl;            
}

void Anim::drawFrame(Vector2 pos, int t, Color tint)
{
    int frameID = (t / frameDuration) % (frameEnd - frameStart) + frameStart;
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

int Anim::getAnimDuration()
{
    return (frameEnd - frameStart) * frameDuration;
}