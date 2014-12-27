#ifndef BISBOMB_H
#define BISBOMB_H

#include <SDL.h>

#include <BisTexture.h>

class BisBomb
{
    public:
        BisBomb(int x, int y, BisTexture& texture);

        void move();
        void render(SDL_Renderer* renderer);

        int getX();
        int getY();
        int getWidth();
        int getHeight();
    private:
        BisTexture* thisTexture;

        int thisX;
        int thisY;
        int thisWidth;
        int thisHeight;

        double degree;
        SDL_Point thisCenter;

        int thisSpeed;
};

#endif // BISBOMB_H
