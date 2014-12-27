#ifndef BISTEXTURE_H
#define BISTEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

class BisTexture
{
    public:
        BisTexture();
        ~BisTexture();

        bool loadTexture(std::string path, SDL_Renderer* renderer);
        bool loadAndRenderText(std::string message,TTF_Font* font,SDL_Color color, SDL_Renderer* renderer);
        void setAlpha(Uint8 alpha);
        void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* rectClip = NULL,int width = NULL,int height = NULL, double degree = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

        int getWidth();
        int getHeight();

        void free();
    private:
        SDL_Texture* thisTexture;

        int thisWidth;
        int thisHeight;
};

#endif // BISTEXTURE_H
