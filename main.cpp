#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <sstream>

#include <BisWindow.h>;
#include <BisTexture.h>
#include <BisSmoke.h>
#include <BisJetParticle.h>
#include <BisBomb.h>
#include <BisBombEffect.h>

using namespace std;

const int Screen_Width = 800;
const int Screen_Height = 480;

BisWindow window;

bool StartGame = false;
bool IsPlayGame = false;
bool GameOver = false;
bool BackToMenu = false;
bool quit = false;

bool fadeIn = false;

Uint8 powerFade = 255;
BisTexture fadeBlack;

TTF_Font* gameFont = NULL;
BisTexture gameText;
SDL_Color colorF1 = {0xFF,0xFF,0xFF,0xFF};

//MenuGame
bool popCredit = false;
int chooseMenu = 0;
Uint8 aBG = 255;
int aVelo = 0;
double degreeBall = 0.0;
BisTexture backgroundMenu;
BisTexture ballMenu;
BisTexture topMenu;
BisTexture craditMenu;
BisTexture CursorMenu;

//GamePlay
int HP = 20;
int Score = 0;

int bgXGame1 = 0;
int bgXGame2 = 0;
BisTexture backGroundGamePlay;
BisTexture GameOverTexture;
int building1 = 0;
int building2 = 0;
int building3 = 0;
BisTexture buildingTexture;
int playerY = 200;
int playerVeloY = 0;
double playerDegree = 0.0;
SDL_Point centerPlayer;
BisTexture PlayerJet;
const int particleJetMax = 20;
BisJetParticle* particleJet[particleJetMax];
BisTexture bgBar;
BisTexture topBar;
BisTexture barBar;
BisTexture ScoreBar;
BisTexture bombTexture;
const int numBomb = 3;
BisBomb* bomb[numBomb];
BisTexture BombEffectTexture;
BisBombEffect* eff[numBomb];

const int smokeMax = 20;
BisSmoke* smoke[smokeMax];

BisTexture smTexture;

//Sounds
Mix_Music* musicMenu = NULL;
Mix_Music* musicGame = NULL;
Mix_Music* musicGameOver = NULL;

Mix_Chunk* damageSound = NULL;
Mix_Chunk* sfSound = NULL;
Mix_Chunk* startGameSound = NULL;
Mix_Chunk* creditSound = NULL;

bool CheckCollision2D(int aX, int aY, int bX, int bY);

bool init()
{
    HWND win = GetForegroundWindow();
    ShowWindow(win, SW_HIDE);

    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        cout << "SDL Init Fail!" << SDL_GetError() << endl;
    }else{
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            cout << "Set HINT Fail Error:" << SDL_GetError() << endl;
            success = false;
        }

        if(!window.init(Screen_Width, Screen_Height, "SuperJet Version 1 - BagIdea"))
        {
            cout << "Init Window Fail!" << endl;
            success = false;
        }
    }

    return success;
}

bool loadMedia()
{
    bool success = true;

    gameFont = TTF_OpenFont("font/gameFont.ttf", 28);
    if(gameFont == NULL)
    {
        cout << "Load gameFont.ttf Fail!" << endl;
        success = false;
    }

    if(!fadeBlack.loadTexture("images/fadeBlack.png", window.getRenderer()))
    {
        cout << "Load fadeBlack.png Fail!" << endl;
        success = false;
    }

    //Menu
    if(!backgroundMenu.loadTexture("images/MenuBackground.png", window.getRenderer()))
    {
        cout << "Load MenuBackground.png Fail!" << endl;
        success = false;
    }

    if(!buildingTexture.loadTexture("images/building.png", window.getRenderer()))
    {
        cout << "Load building.png Fail!" << endl;
        success = false;
    }

    if(!ballMenu.loadTexture("images/MenuBall.png", window.getRenderer()))
    {
        cout << "Load MenuBall.png Fail!" << endl;
        success = false;
    }

    if(!topMenu.loadTexture("images/MenuTop.png", window.getRenderer()))
    {
        cout << "Load MenuTop.png Fail!" << endl;
        success = false;
    }

    if(!craditMenu.loadTexture("images/MenuCradit.png", window.getRenderer()))
    {
        cout << "Load MenuCradit.png Fail!" << endl;
        success = false;
    }

    if(!CursorMenu.loadTexture("images/MenuCursor.png", window.getRenderer()))
    {
        cout << "Load MenuCursor.png Fail!" << endl;
        success = false;
    }

    if(!smTexture.loadTexture("images/SM.png", window.getRenderer()))
    {
        cout << "Load SM.png Fail!" << endl;
        success = false;
    }

    if(!backGroundGamePlay.loadTexture("images/GameBackground.jpg", window.getRenderer()))
    {
        cout << "Load GameBackground.jpg Fail!" << endl;
        success = false;
    }

    if(!PlayerJet.loadTexture("images/PlayerJet.png", window.getRenderer()))
    {
        cout << "Load PlayerJet.png Fail!" << endl;
        success = false;
    }

    if(!bgBar.loadTexture("images/bgBar.png", window.getRenderer()))
    {
        cout << "Load bgBar.png Fail!" << endl;
        success = false;
    }

    if(!barBar.loadTexture("images/bar.jpg", window.getRenderer()))
    {
        cout << "Load bar.jpg Fail!" << endl;
        success = false;
    }

    if(!ScoreBar.loadTexture("images/scoreBar.png", window.getRenderer()))
    {
        cout << "Load scoreBar.png Fail!" << endl;
        success = false;
    }

    if(!topBar.loadTexture("images/topBar.png", window.getRenderer()))
    {
        cout << "Load topBar.png Fail!" << endl;
        success = false;
    }

    if(!bombTexture.loadTexture("images/Bomb.png", window.getRenderer()))
    {
        cout << "Load Bomb.png Fail!" << endl;
        success = false;
    }

    if(!BombEffectTexture.loadTexture("images/BombEff.png", window.getRenderer()))
    {
        cout << "Load BombEff.png Fail!" << endl;
        success = false;
    }

    musicMenu = Mix_LoadMUS("sounds/music.wav");
    if(musicMenu == NULL)
    {
        cout << "Load music.wav Fail!" << endl;
        success = false;
    }

    musicGame = Mix_LoadMUS("sounds/music2.wav");
    if(musicGame == NULL)
    {
        cout << "Load music2.wav Fail!" << endl;
        success = false;
    }

    musicGameOver = Mix_LoadMUS("sounds/gameover.wav");
    if(musicGameOver == NULL)
    {
        cout << "Load gameover.wav Fail!" << endl;
        success = false;
    }

    damageSound = Mix_LoadWAV("sounds/damage.wav");
    if(damageSound == NULL)
    {
        cout << "Load damage.wav Fail!" << endl;
        success = false;
    }

    sfSound = Mix_LoadWAV("sounds/sf.wav");
    if(sfSound == NULL)
    {
        cout << "Load sf.wav Fail!" << endl;
        success = false;
    }

    startGameSound = Mix_LoadWAV("sounds/startGame.wav");
    if(startGameSound == NULL)
    {
        cout << "Load startGame.wav Fail!" << endl;
        success = false;
    }

    creditSound = Mix_LoadWAV("sounds/credit.wav");
    if(creditSound == NULL)
    {
        cout << "Load credit.wav Fail!" << endl;
        success = false;
    }

    if(!GameOverTexture.loadTexture("images/gameover.png", window.getRenderer()))
    {
        cout << "Load gameover.png Fail!" << endl;
        success = false;
    }

    return success;
}

void close()
{
    int i;

    //MainMenu
    for(i = 0; i < smokeMax; i++)
    {
        if(smoke[i] != NULL)
        {
            delete smoke[i];
            smoke[i] = NULL;
        }
    }

    fadeBlack.free();
    backgroundMenu.free();
    ballMenu.free();
    topMenu.free();
    craditMenu.free();
    CursorMenu.free();
    smTexture.free();

    //GamePlay
    for(i = 0; i < particleJetMax; i++)
    {
        if(particleJet[i] != NULL)
        {
            delete particleJet[i];
            particleJet[i] = NULL;
        }
    }

    for(i = 0; i < numBomb; i++)
    {
        if(bomb[i] != NULL)
        {
            delete bomb[i];
            bomb[i] = NULL;
        }
    }

    for(i = 0; i < numBomb; i++)
    {
        if(eff[i] != NULL)
        {
            delete eff[i];
            eff[i] = NULL;
        }
    }

    bgBar.free();
    topBar.free();
    barBar.free();
    ScoreBar.free();
    bombTexture.free();
    backGroundGamePlay.free();
    buildingTexture.free();
    PlayerJet.free();
    BombEffectTexture.free();
    TTF_CloseFont(gameFont);
    gameFont = NULL;
    gameText.free();

    Mix_FreeMusic(musicMenu);
    Mix_FreeMusic(musicGame);
    Mix_FreeMusic(musicGameOver);
    Mix_FreeChunk(damageSound);
    Mix_FreeChunk(sfSound);
    Mix_FreeChunk(startGameSound);
    Mix_FreeChunk(creditSound);
    musicMenu = NULL;
    musicGame = NULL;
    musicGameOver = NULL;
    damageSound = NULL;
    sfSound = NULL;
    startGameSound = NULL;
    creditSound = NULL;

    GameOverTexture.free();

    window.free();

    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void keyboardEvent(SDL_Event e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP:
                if(StartGame && IsPlayGame)
                {
                    playerVeloY -= 5;
                }else{
                    if(!popCredit && !StartGame){chooseMenu--;Mix_PlayChannel(-1,sfSound,0);}
                }
                break;
            case SDLK_DOWN:
                if(StartGame && IsPlayGame)
                {
                    playerVeloY += 5;
                }else{
                    if(!popCredit && !StartGame){chooseMenu++;Mix_PlayChannel(-1,sfSound,0);}
                }
                break;
            case SDLK_RETURN:
                if(!StartGame && powerFade <= 100)
                {
                    if(chooseMenu == 0)
                    {
                        Mix_PlayChannel(-1,startGameSound,0);
                        StartGame = true;
                        GameOver = false;
                        fadeIn = true;
                    }
                    if(chooseMenu == 1)
                    {
                        Mix_PlayChannel(-1,creditSound,0);
                        if(!popCredit)
                        {
                            popCredit = true;
                        }else{
                            popCredit = false;
                        }
                    }
                    else if(chooseMenu == 2)
                    {
                        quit = true;
                    }
                }
                else if(GameOver && powerFade == 255)
                {
                    Mix_PlayMusic(musicMenu, -1);

                    int i;

                    StartGame = false;
                    IsPlayGame = false;
                    GameOver = false;
                    HP = 20;
                    fadeIn = false;

                    for(i = 0; i < particleJetMax; i++)
                    {
                        if(particleJet[i] != NULL)
                        {
                            delete particleJet[i];
                            particleJet[i] = NULL;
                        }
                    }

                    for(i = 0; i < numBomb; i++)
                    {
                        if(bomb[i] != NULL)
                        {
                            delete bomb[i];
                            bomb[i] = NULL;
                        }
                    }

                    for(i = 0; i < numBomb; i++)
                    {
                        if(eff[i] != NULL)
                        {
                            delete eff[i];
                            eff[i] = NULL;
                        }
                    }
                }
                break;
        }
    }
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP:
                if(StartGame && IsPlayGame)
                {
                    playerVeloY += 5;
                }
                break;
            case SDLK_DOWN:
                if(StartGame && IsPlayGame)
                {
                    playerVeloY -= 5;
                }
                break;
        }
    }

    if(chooseMenu < 0)
    {
        chooseMenu = 2;
    }
    else if(chooseMenu > 2)
    {
        chooseMenu = 0;
    }
}

void sceneMainMenu()
{
    int bgFade = aVelo;
    if(rand()%11 == 0)
    {
        bgFade = -5+(rand()%+21);
        aVelo = bgFade;
    }

    if(aBG-bgFade < 0)
    {
        aBG = 0;
    }
    else if(aBG+bgFade > 255)
    {
        aBG = 255;
    }else{
        aBG += bgFade;
    }

    backgroundMenu.setAlpha(aBG);
    backgroundMenu.render(0,0,window.getRenderer());
    ballMenu.render((Screen_Width/2)-(ballMenu.getWidth()/2), 100, window.getRenderer(), NULL, NULL, NULL, degreeBall);

    degreeBall += 0.2;

    for(int i = 0; i < smokeMax; i++)
    {
        if(smoke[i] == NULL)
        {
            smoke[i] = new BisSmoke((rand()%Screen_Width)-(smTexture.getWidth()/2),Screen_Height,smTexture);
        }else{
            if(smoke[i]->getDead())
            {
                delete smoke[i];
                smoke[i] = new BisSmoke((rand()%Screen_Width)-(smTexture.getWidth()/2),Screen_Height,smTexture);
            }
        }

        smoke[i]->move();
        smoke[i]->render(window.getRenderer());
    }

    topMenu.render(0,0,window.getRenderer());

    if(popCredit)
    {
        craditMenu.render(0,0,window.getRenderer());
    }else{
        if(chooseMenu == 0)
        {
            CursorMenu.render((Screen_Width/2)-(CursorMenu.getWidth()/2),290,window.getRenderer());
        }
        else if(chooseMenu == 1)
        {
            CursorMenu.render((Screen_Width/2)-(CursorMenu.getWidth()/2),345,window.getRenderer());
        }
        else if(chooseMenu == 2)
        {
            CursorMenu.render((Screen_Width/2)-(CursorMenu.getWidth()/2),400,window.getRenderer());
        }
    }
}

void sceneGamePlay()
{
    backGroundGamePlay.render(bgXGame1,0,window.getRenderer());
    backGroundGamePlay.render(bgXGame2,0,window.getRenderer());

    bgXGame1 -= 10;
    bgXGame2 -= 10;

    if(-bgXGame1 >= backGroundGamePlay.getWidth())
    {
        bgXGame1 = bgXGame2+backGroundGamePlay.getWidth();
    }

    if(-bgXGame2 >= backGroundGamePlay.getWidth())
    {
        bgXGame2 = bgXGame1+backGroundGamePlay.getWidth();
    }

    playerY += playerVeloY;
    if(playerY < 0 || playerY >= Screen_Height-PlayerJet.getHeight())
    {
        playerY -= playerVeloY;
    }

    if(playerVeloY != 0)
    {
        playerDegree += playerVeloY;
        if(playerDegree < -10)
        {
            playerDegree = -10;
        }
        else if(playerDegree > 10)
        {
            playerDegree = 10;
        }
    }else{
        if(playerDegree < 0)
        {
            playerDegree++;
        }
        else if(playerDegree > 0)
        {
            playerDegree--;
        }
    }

    PlayerJet.render(100,playerY,window.getRenderer(), NULL,NULL,NULL,playerDegree,&centerPlayer);

    for(int i = 0; i < numBomb; i++)
    {
        if(bomb[i] == NULL)
        {
            bomb[i] = new BisBomb(Screen_Width,(rand()%Screen_Height)-(bombTexture.getHeight()/2),bombTexture);
        }else{
            if( bomb[i]->getX() < -bomb[i]->getWidth())
            {
                delete bomb[i];
                bomb[i] = new BisBomb(Screen_Width,(rand()%Screen_Height)-(bombTexture.getHeight()/2),bombTexture);
            }

            //HisTest Bomb And Player
            if(CheckCollision2D(100,playerY,bomb[i]->getX(), bomb[i]->getY()))
            {
                if(!GameOver){Mix_PlayChannel(-1,damageSound,0);}

                for(int a = 0; a < numBomb; a++)
                {
                    if(eff[a] == NULL)
                    {
                        eff[a] = new BisBombEffect(bomb[i]->getX(),bomb[i]->getY(),BombEffectTexture);
                        break;
                    }
                }

                HP--;
                if(HP <= 0 && !GameOver)
                {
                    Mix_PlayMusic(musicGameOver, -1);

                    HP = 0;
                    GameOver = true;
                    fadeIn = true;
                }

                delete bomb[i];
                bomb[i] = new BisBomb(Screen_Width,(rand()%Screen_Height)-(bombTexture.getHeight()/2),bombTexture);
            }
        }

         if(powerFade == 0 || GameOver)
        {
            bomb[i]->move();
        }

        bomb[i]->render(window.getRenderer());
    }

    for(int i = 0; i < numBomb; i++)
    {
        if(eff[i] != NULL)
        {
            eff[i]->render(window.getRenderer());

            if(eff[i]->getDead())
            {
                delete eff[i];
                eff[i] = NULL;
            }
         }
    }

    for(int i = 0; i < particleJetMax; i++)
    {
        if(particleJet[i] == NULL)
        {
            particleJet[i] = new BisJetParticle(Screen_Width,(rand()%Screen_Height)-(smTexture.getHeight()/2),smTexture);
        }else{
            if( particleJet[i]->getDead())
            {
                delete particleJet[i];
                particleJet[i] = new BisJetParticle(Screen_Width,(rand()%Screen_Height)-(smTexture.getHeight()/2),smTexture);
            }
        }

         particleJet[i]->move();
         particleJet[i]->render(window.getRenderer());
    }

    buildingTexture.render(building1,340,window.getRenderer());
    buildingTexture.render(building2,340,window.getRenderer());
    buildingTexture.render(building3,340,window.getRenderer());

    building1 -= 30;
    building2 -= 30;
    building3 -= 30;

    if(-building1 >= buildingTexture.getWidth())
    {
        building1 = building3+buildingTexture.getWidth();
    }

    if(-building2 >= buildingTexture.getWidth())
    {
        building2 = building1+buildingTexture.getWidth();
    }

    if(-building3 >= buildingTexture.getWidth())
    {
        building3 = building2+buildingTexture.getWidth();
    }

    bgBar.render(0,0,window.getRenderer());
    if(HP > 0)
    {
        barBar.render(88,40,window.getRenderer(),NULL,((double)HP/20.0)*(double)barBar.getWidth(),NULL);
    }
    topBar.render(0,0,window.getRenderer());
    ScoreBar.render(480,15,window.getRenderer());

    stringstream score_str;
    score_str << "Score: " << Score/30;
    gameText.loadAndRenderText(score_str.str(),gameFont, colorF1, window.getRenderer());
    gameText.render(630,30,window.getRenderer());

    if(!GameOver){Score++;}
}

void update()
{
    int i;
    //Update Event
    if(!IsPlayGame)
    {
        sceneMainMenu();
    }
    else if(StartGame && IsPlayGame)
    {
        sceneGamePlay();
    }

    bool alphaUpdate = true;
    if(!fadeIn)
    {
        if(powerFade - 3 > 0)
        {
            if(!GameOver)
            {
                powerFade -= 3;
            }
        }else{
            powerFade = 0;
            alphaUpdate = false;
        }
    }else{
        if(powerFade + 3 < 255)
        {
            powerFade += 3;
        }else{
            powerFade = 255;
            alphaUpdate = false;

            if(StartGame)
            {
                if(!GameOver)
                {
                    Mix_PlayMusic(musicGame,-1);

                    IsPlayGame = true;
                    fadeIn = false;
                    bgXGame1 = 0;
                    bgXGame2 = backGroundGamePlay.getWidth();
                    playerY = 200;
                    building1 = 0;
                    building2 = buildingTexture.getWidth();
                    building2 = buildingTexture.getWidth()*2;
                    Score = 0;

                    for(i = 0; i < smokeMax; i++)
                    {
                        if(smoke[i] != NULL)
                        {
                            delete smoke[i];
                            smoke[i] = NULL;
                        }
                    }
                }
            }
        }
    }

    if(alphaUpdate)
    {
        fadeBlack.setAlpha(powerFade);
    }
    fadeBlack.render(0,0,window.getRenderer(),NULL,Screen_Width, Screen_Height);

    if(GameOver && powerFade == 255)
    {
        GameOverTexture.render((Screen_Width/2)-((GameOverTexture.getWidth()/2)+5), 170, window.getRenderer());
        stringstream score_str;
        score_str << Score/30;
        gameText.loadAndRenderText(score_str.str(),gameFont, colorF1, window.getRenderer());
        gameText.render((Screen_Width/2)-(gameText.getWidth()/2),240,window.getRenderer(),NULL,gameText.getWidth(),gameText.getHeight());
    }
}

bool CheckCollision2D(int aX, int aY, int bX, int bY)
{
    int aT,aB,aL,aR,bT,bB,bL,bR;

    aT = aY;
    aB = aY+PlayerJet.getHeight();
    aL = aX;
    aR = aX+PlayerJet.getWidth();

    bT = bY;
    bB = bY+50;
    bL = bX;
    bR = bX+50;

    if(!(aB < bT || aT > bB || aR < bL || aL > bR))
    {
        return true;
    }

    return false;
}

int main(int argc, char* args[])
{
    if(!init())
    {
        cout << "Init Fail!" << endl;
    }else{
        if(!loadMedia())
        {
                cout << "LoadMedia Fail!" << endl;
        }else{
            Mix_PlayMusic(musicMenu, -1);

            centerPlayer = {PlayerJet.getWidth()/3,PlayerJet.getHeight()/2};

            SDL_Event e;

            while(!quit)
            {
                while(SDL_PollEvent(&e))
                {
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }

                    keyboardEvent(e);
                }

                window.render(update);
            }
        }
    }

    close();
    return 0;
}
