#include "BisBombEffect.h"

#include <SDL.h>

#include <BisTexture.h>

BisBombEffect::BisBombEffect(int x, int y, BisTexture& texture)
{
    thisTexture = &texture;

    clip[0].x = 0;
    clip[0].y = 0;
    clip[0].w = 100;
    clip[0].h = 100;

    clip[1].x = 100;
    clip[1].y = 0;
    clip[1].w = 100;
    clip[1].h = 100;

    clip[2].x = 200;
    clip[2].y = 0;
    clip[2].w = 100;
    clip[2].h = 100;

    clip[3].x = 300;
    clip[3].y = 0;
    clip[3].w = 100;
    clip[3].h = 100;

    clip[4].x = 400;
    clip[4].y = 0;
    clip[4].w = 100;
    clip[4].h = 100;

    clip[5].x = 0;
    clip[5].y = 100;
    clip[5].w = 100;
    clip[5].h = 100;

    clip[6].x = 100;
    clip[6].y = 100;
    clip[6].w = 100;
    clip[6].h = 100;

    clip[7].x = 200;
    clip[7].y = 100;
    clip[7].w = 100;
    clip[7].h = 100;

    clip[8].x = 300;
    clip[8].y = 100;
    clip[8].w = 100;
    clip[8].h = 100;

    clip[9].x = 400;
    clip[9].y = 100;
    clip[9].w = 100;
    clip[9].h = 100;

    clip[10].x = 0;
    clip[10].y = 200;
    clip[10].w = 100;
    clip[10].h = 100;

    currentFrame = 0;

    thisX = x;
    thisY = y;

    isDead = false;
}

void BisBombEffect::render(SDL_Renderer* renderer)
{
    if(thisTexture != NULL)
    {
        thisTexture->render(thisX-=10, thisY, renderer,&clip[currentFrame/2],100,100);

        if(currentFrame/2 < 10)
        {
            currentFrame++;
        }else{
            isDead = true;
        }
    }
}

int BisBombEffect::getX()
{
    return thisX;
}

int BisBombEffect::getY()
{
    return thisY;
}

bool BisBombEffect::getDead()
{
    return isDead;
}
