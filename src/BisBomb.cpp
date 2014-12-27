#include "BisBomb.h"

#include <SDL.h>
#include <stdlib.h>

#include <BisTexture.h>

BisBomb::BisBomb(int x, int y, BisTexture& texture)
{
    thisTexture = &texture;

    thisX = x;
    thisY = y;
    thisWidth = 60;
    thisHeight = 60;

    degree = rand()%360;
    thisSpeed = 10+(rand()%11);

    thisCenter = {0,0};
}

void BisBomb::move()
{
    thisX -= thisSpeed;
    degree--;
}

void BisBomb::render(SDL_Renderer* renderer)
{
    if(thisTexture != NULL)
    {
        thisCenter = {thisTexture->getWidth()/2,thisTexture->getHeight()/2};
        thisTexture->render(thisX, thisY, renderer,NULL,NULL,NULL,degree, &thisCenter);
    }
}

int BisBomb::getX()
{
    return thisX;
}

int BisBomb::getY()
{
    return thisY;
}

int BisBomb::getWidth()
{
    return thisWidth;
}

int BisBomb::getHeight()
{
    return thisHeight;
}
