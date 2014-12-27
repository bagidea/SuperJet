#include "BisWindow.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>

using namespace std;

BisWindow::BisWindow()
{
    thisWindow = NULL;
    thisRenderer = NULL;

    isShow = false;
}

bool BisWindow::init(int Screen_Width, int Screen_Height, string title, Uint8 rendererR,Uint8 rendererG,Uint8 rendererB)
{
    thisWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Screen_Width, Screen_Height, SDL_WINDOW_HIDDEN);
    if(thisWindow != NULL)
    {
        thisRenderer = SDL_CreateRenderer(thisWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(thisRenderer == NULL)
        {
            cout << "Renderer Create Fail! Error:" << SDL_GetError() << endl;
            SDL_DestroyWindow(thisWindow);
            thisWindow = NULL;
        }else{
            SDL_ShowWindow(thisWindow);
            isShow = true;
        }
    }else{
        cout << "Window Create Fail! Error:" << SDL_GetError() << endl;
    }

    colorR = rendererR;
    colorG = rendererG;
    colorB = rendererB;

    int imgFlag = IMG_INIT_JPG | IMG_INIT_PNG;
    if(!(IMG_Init(imgFlag) & imgFlag))
    {
        cout << "IMG INIT Fail! Error:" << IMG_GetError() << endl;
    }

    if(TTF_Init() == -1)
    {
        cout << "TTF INIT Fail! Error:" << TTF_GetError() << endl;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,2, 2048) < 0)
    {
        cout << "Open Audio Mix Error : " << Mix_GetError() << endl;
    }

    SDL_Surface* icon = IMG_Load("images/icon.png");
    SDL_SetWindowIcon(thisWindow, icon);
    SDL_FreeSurface(icon);

    return thisWindow != NULL && thisRenderer != NULL;
}

void BisWindow::render(void method())
{
    SDL_SetRenderDrawColor(thisRenderer, colorR, colorG, colorB, 0xFF);
    SDL_RenderClear(thisRenderer);

    if(method != NULL)
    {
        method();
    }

    SDL_RenderPresent(thisRenderer);
}

SDL_Renderer* BisWindow::getRenderer()
{
    return thisRenderer;
}

void BisWindow::free()
{
    if(thisWindow != NULL)
    {
        SDL_DestroyWindow(thisWindow);
        thisWindow = NULL;
    }

    if(thisRenderer != NULL)
    {
        SDL_DestroyRenderer(thisRenderer);
        thisRenderer = NULL;
    }

    colorR = 0;
    colorG = 0;
    colorB = 0;

    isShow = false;
}

