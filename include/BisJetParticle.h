#ifndef BISJETPARTICLE_H
#define BISJETPARTICLE_H

#include <SDL.h>

#include <BisTexture.h>

class BisJetParticle
{
    public:
        BisJetParticle(int x, int y, BisTexture& texture);

        void move();
        void render(SDL_Renderer* renderer);

        bool getDead();
    private:
        BisTexture* thisTexture;

        int thisSpeedX;
        int thisSpeedY;
        Uint8 thisAlpha;

        int thisX;
        int thisY;
        int thisSize;

        bool isDead;
};

#endif // BISJETPARTICLE_H
