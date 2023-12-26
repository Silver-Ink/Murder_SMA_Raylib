#ifndef ANIM
#define ANIM

class Spritesheet{
private:
    Rectangle* lstFrame;

    int nbFrameW;
    int nbFrameH;
    int frameSize;
    int nbFrame;
public:
    Texture2D texture;
    Spritesheet(string filename, int frameSize);
    Rectangle getFrame(int frameID);
    int getNbFrame();
};

class Anim
{
private:
    Spritesheet* spritesheet;
    int frameDuration; //ms
    int frameStart;
    int frameEnd;

public:
    Anim();
    Anim(Spritesheet* s, int start = 0, int end = -1, int fps = 6);
    Anim(string filename, int frameSize, int start = 0, int end = -1, int fps = 6);
    void drawFrame(Vector2 pos, int t, Color tint = WHITE);

    int getAnimDuration();
};

#endif