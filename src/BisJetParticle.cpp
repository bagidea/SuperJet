#include "BisJetParticle.h"

#include <SDL.h>
#include <stdlib.h>

#include <BisTexture.h>

BisJetParticle::BisJetParticle(int x, int y, BisTexture& texture)
{
    thisTexture = &texture;
    thisX = x;
    thisY = y;

    thisSpeedX = 10+(rand()%21);
    thisSpeedY = -1+(rand()%3);
    thisAlpha = 100+rand()%155;

    thisSize = rand()%300;

    isDead = false;
}

void BisJetParticle::move()
{
    thisX -= thisSpeedX;
    thisY -= thisSpeedY;

    if(thisAlpha-0.5 < 0)
    {
        thisAlpha = 0;
        isDead = true;
    }else{
        thisAlpha -= 0.5;
    }

    thisTexture->setAlpha(thisAlpha);
}

void BisJetParticle::render(SDL_Renderer* renderer)
{
    if(thisTexture != NULL)
    {
        thisTexture->render(thisX, thisY, renderer,NULL,thisSize,thisSize);
    }
}

bool BisJetParticle::getDead()
{
    return isDead;
}

