#ifndef BISBOMBEFFECT_H
#define BISBOMBEFFECT_H

#include <SDL.h>

#include <BisTexture.h>

class BisBombEffect
{
    public:
        BisBombEffect(int x, int y, BisTexture& texture);

        void render(SDL_Renderer* renderer);

        int getX();
        int getY();

        bool getDead();
    private:
        BisTexture* thisTexture;

        SDL_Rect clip[11];
        int currentFrame = 0;

        int thisX;
        int thisY;

        bool isDead;
};

#endif // BISBOMBEFFECT_H
