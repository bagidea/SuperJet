#include "BisSmoke.h"

#include <SDL.h>
#include <stdlib.h>

#include <BisTexture.h>

BisSmoke::BisSmoke(int x, int y, BisTexture& texture)
{
    thisTexture = &texture;
    thisX = x;
    thisY = y;

    thisSpeed = 3+(rand()%5);
    thisAlpha = rand()%100;

    isDead = false;
}

void BisSmoke::move()
{
    thisY -= thisSpeed;

    if(thisAlpha-1 < 0)
    {
        thisAlpha = 0;
        isDead = true;
    }else{
        thisAlpha--;
    }

    thisTexture->setAlpha(thisAlpha);
}

void BisSmoke::render(SDL_Renderer* renderer)
{
    if(thisTexture != NULL)
    {
        thisTexture->render(thisX, thisY, renderer,NULL);
    }
}

bool BisSmoke::getDead()
{
    return isDead;
}
