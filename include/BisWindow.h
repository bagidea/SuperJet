#ifndef BISWINDOW_H
#define BISWINDOW_H

#include <SDL.h>
#include <string>
#include <iostream>

class BisWindow
{
    public:
        BisWindow();

        bool init(int Screen_Width, int Screen_Height, std::string title, Uint8 rendererR = 0x00,Uint8 rendererG = 0x00,Uint8 rendererB = 0x00);
        void render(void method() = NULL);

        SDL_Renderer* getRenderer();

        void free();
    private:
        SDL_Window* thisWindow;
        SDL_Renderer* thisRenderer;

        Uint8 colorR;
        Uint8 colorG;
        Uint8 colorB;

        bool isShow;
};

#endif // BISWINDOW_H
