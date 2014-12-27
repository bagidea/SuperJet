#ifndef BISSMOKE_H
#define BISSMOKE_H

#include <SDL.h>

#include <BisTexture.h>

class BisSmoke
{
    public:
        BisSmoke(int x, int y, BisTexture& texture);

        void move();
        void render(SDL_Renderer* renderer);

        bool getDead();
    private:
        BisTexture* thisTexture;

        int thisSpeed;
        Uint8 thisAlpha;

        int thisX;
        int thisY;

        bool isDead;
};

#endif // BISSMOKE_H
