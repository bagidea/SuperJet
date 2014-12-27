#include "BisTexture.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

using namespace std;

BisTexture::BisTexture()
{
    thisTexture = NULL;

    thisWidth = 0;
    thisHeight = 0;
}

BisTexture::~BisTexture()
{
    free();
}

bool BisTexture::loadTexture(string path, SDL_Renderer* renderer)
{
    SDL_Texture* texture;
    SDL_Surface* thisLoaded = IMG_Load(path.c_str());
    if(thisLoaded == NULL)
    {
        cout << "Load Image Fail :: " << path << " Error:" << IMG_GetError() << endl;
    }else{
        texture = SDL_CreateTextureFromSurface(renderer, thisLoaded);
        if(texture == NULL)
        {
            cout << "Create Texture Fail Error:" << SDL_GetError() << endl;
        }else{
            thisWidth = thisLoaded->w;
            thisHeight = thisLoaded->h;
        }

        SDL_FreeSurface(thisLoaded);
    }

    thisTexture = texture;
    return thisTexture != NULL;
}

bool BisTexture::loadAndRenderText(std::string message,TTF_Font* font,SDL_Color color, SDL_Renderer* renderer)
{
    free();

    SDL_Surface* T = TTF_RenderText_Solid(font, message.c_str(),color);
    if(T == NULL)
    {
        std::cout << "SDL_TTF Error : " << TTF_GetError() << std::endl;
    }else{
        thisTexture = SDL_CreateTextureFromSurface(renderer,T);
        if(thisTexture == NULL)
        {
            std::cout << "Create TTF Texture Error : " << SDL_GetError() << std::endl;
        }else{
            thisWidth = T->w;
            thisHeight = T->h;
        }

        SDL_FreeSurface(T);
    }

    return thisTexture != NULL;
}

void BisTexture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(thisTexture, alpha);
}

void BisTexture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* rectClip,int width, int height, double degree, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect quad = {x,y,thisWidth,thisHeight};

    if(width != NULL)
    {
        quad.w = width;
    }

    if(height != NULL)
    {
        quad.h = height;
    }

    SDL_RenderCopyEx(renderer, thisTexture, rectClip, &quad, degree,center,flip);
}

int BisTexture::getWidth()
{
    return thisWidth;
}

int BisTexture::getHeight()
{
    return thisHeight;
}

void BisTexture::free()
{
    if(thisTexture != NULL)
    {
        SDL_DestroyTexture(thisTexture);
        thisTexture = NULL;
    }

    thisWidth = 0;
    thisHeight = 0;
}
