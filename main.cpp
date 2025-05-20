#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

const int Ccao_MH = 600;
const int Crong_MH = 800;

struct Bird {
    SDL_Texture* texture = nullptr;
    SDL_Rect rect;
    float vtoc = 0;
    int lives = 3;
};

struct Pipe {
    SDL_Texture* texture = nullptr;
    SDL_Rect ongtren,ongduoi;
    int gap = 200;
    int speed = 3;
};

struct Vatpham {
    SDL_Texture* texture = nullptr;
    SDL_Rect rect;
    bool tontai = false;
    float speed = 3.0f;
};

bool Vacham(const SDL_Rect& a, const SDL_Rect& b) {
    return !(a.x+a.w<b.x||b.x+b.w<a.x||a.y+a.h<b.y||b.y+b.h<a.y);
}

int main(int argc, char* argv[]) {
      srand((unsigned int)time(nullptr));
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
     if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) return 1;
    if (TTF_Init() == -1) return 1;

     SDL_Window* window = SDL_CreateWindow("Flappy Bird ++", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Crong_MH, Ccao_MH, SDL_WINDOW_SHOWN);
    if (!window) return 1;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return 1;

    SDL_Surface* bgSurface = IMG_Load("assets/background.png");
     SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
      SDL_FreeSurface(bgSurface);

    SDL_Surface* birdSurface = IMG_Load("assets/bird.png");
      SDL_Texture* birdTexture = SDL_CreateTextureFromSurface(renderer, birdSurface);
     SDL_FreeSurface(birdSurface);

    Bird bird;
     bird.texture = birdTexture;
      bird.rect = { 60, Ccao_MH/ 2 - 10, 40, 40 };

     SDL_Surface* itemSurface = IMG_Load("assets/item.png");
      SDL_Texture* itemTexture = SDL_CreateTextureFromSurface(renderer, itemSurface);
    SDL_FreeSurface(itemSurface);

    Vatpham item;
    item.texture = itemTexture;
      item.tontai = false;

    SDL_Surface* pipeSurface = IMG_Load("assets/pipe.png");
    SDL_Texture* pipeTexture = SDL_CreateTextureFromSurface(renderer, pipeSurface);
    SDL_FreeSurface(pipeSurface);

    const int So_pipe = 3  ;
    Pipe pipes[So_pipe];
    for (int i = 0; i < So_pipe; i++) {
        pipes[i].texture = pipeTexture;
        pipes[i].gap = 200;
        pipes[i].speed = 3;
        int startpipe = Crong_MH + i * 300;
        int height = rand() % (Ccao_MH - pipes[i].gap - 100) + 30;
        pipes[i].ongtren = { startpipe, 0, 60, height };
        pipes[i].ongduoi = { startpipe, height + pipes[i].gap, 60, Ccao_MH - (height + pipes[i].gap) };
    }

    TTF_Font* font = TTF_OpenFont("assets/arial.ttf", 24);
    SDL_Color black = { 0, 0, 0, 255 };

    int score = 0, level = 1,k=0;
    bool quit = false;
    SDL_Event e;
    Uint32 lastTick = SDL_GetTicks();
    Uint32  battu_Time = 0;

    Uint32 Item_lastime = SDL_GetTicks();

    bool tangtoc = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {

            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_SPACE) {
                    bird.vtoc = -6;
                }
                if (e.key.keysym.sym == SDLK_i) {
                    bird.vtoc = -10;
                }if (e.key.keysym.sym == SDLK_j) {
                    bird.vtoc = 6;}
                    if (e.key.keysym.sym == SDLK_q) {
                            if(score < 280){
                cout << "GAME OVER! YOU LOSTTT! SCORE: " << score << endl;}
                else cout << "CONGRAT! YOU WONNN! OVER GOAL:" << score << endl;

                quit = true;}

                if (e.key.keysym.sym == SDLK_LSHIFT || e.key.keysym.sym == SDLK_RSHIFT) {
                    tangtoc = true;
                }

            }

            if (e.type == SDL_KEYUP) {
                if (e.key.keysym.sym == SDLK_LSHIFT || e.key.keysym.sym == SDLK_RSHIFT) {
                    tangtoc = false;
                    bird.rect.x = 60;
                }
            }
        }

        Uint32 currentTick = SDL_GetTicks();
        float delta = (currentTick - lastTick) / 1000.0f;
        lastTick = currentTick;

        bird.vtoc += 9.8f * delta *2;
        bird.rect.y += int(bird.vtoc);

        if (tangtoc) {
            bird.rect.x += 15;
            if (bird.rect.x + bird.rect.w > Crong_MH)
                bird.rect.x = 600 - bird.rect.w;
        }

        for (int i = 0; i < So_pipe; i++) {
            pipes[i].ongtren.x -= pipes[i].speed;
            pipes[i].ongduoi.x -= pipes[i].speed;
        }


        if (item.tontai) {
            item.rect.x -= int(item.speed);
            if (item.rect.x + item.rect.w < 0) item.tontai = false;
        }


        if (!item.tontai && currentTick - Item_lastime > 10000) {
            int pipeIndex = rand() % So_pipe;
            item.tontai = true;
            item.rect.w = 30;
            item.rect.h = 30;
            item.rect.x = pipes[pipeIndex].ongtren.x + (pipes[pipeIndex].ongtren.w / 2) - 30/2;
            item.rect.y = pipes[pipeIndex].ongtren.h + (pipes[pipeIndex].gap / 2) - 30/2;
            Item_lastime = currentTick;
        }

        for (int i = 0; i < So_pipe; i++) {
            if (pipes[i].ongtren.x + pipes[i].ongtren.w < 0) {
                int maxX = pipes[0].ongtren.x;
                for (int j = 1; j < So_pipe; j++)
                    if (pipes[j].ongtren.x > maxX) maxX = pipes[j].ongtren.x;

                pipes[i].ongtren.x = maxX + 300;
                pipes[i].ongduoi.x = pipes[i].ongtren.x;

                int height = rand() % (Ccao_MH - pipes[i].gap - 100) + 15;
                pipes[i].ongtren.h = height;
                pipes[i].ongduoi.y = height + pipes[i].gap;
                pipes[i].ongduoi.h = Ccao_MH - pipes[i].ongduoi.y;

                score++;

                if (score >= k+level*10) {
                    for (int j = 0; j < So_pipe; ++j)
                        pipes[j].speed += 1;
                        k+= level*10;
                        level++;

                }
            }
        }

         if (bird.rect.y < 0 || bird.rect.y + bird.rect.h > Ccao_MH) {
                if(score < 280){
                cout << "GAME OVER! YOU LOSTTT! SCORE: " << score << endl;}
                else cout << "CONGRAT! YOU WONNN! OVER GOAL:" << score << endl;

                quit = true;}

        if (SDL_GetTicks() > battu_Time) {
            for (int i = 0; i < So_pipe; i++) {
                if (Vacham(bird.rect, pipes[i].ongtren) || Vacham(bird.rect, pipes[i].ongduoi)) {
                    bird.lives--;
                    if (bird.lives == 0) {
                            if(score < 280){
                        cout << "GAME OVER! YOU LOSTTT!  SCORE: " << score << endl;}
                    else cout << "CONGRAT! YOU WON! OVER GOAL:" << score << endl;
                        quit = true;
                    }
                    else {
                        bird.rect.y = Ccao_MH/ 2;
                        bird.vtoc = 0;
                        battu_Time = SDL_GetTicks() + 1000;
                    }
                }
            }
        }

        if (item.tontai && Vacham(bird.rect, item.rect)) {
            bird.lives++;
            item.tontai = false;
        }

        if (SDL_GetTicks() < battu_Time)
            SDL_SetTextureAlphaMod(bird.texture, 128);
        else
            SDL_SetTextureAlphaMod(bird.texture, 255);

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bgTexture, NULL, NULL);

        if (item.tontai)
            SDL_RenderCopy(renderer, item.texture, NULL, &item.rect);

        SDL_RenderCopy(renderer, bird.texture, NULL, &bird.rect);

        for (int i = 0; i < So_pipe; i++) {
            SDL_RenderCopy(renderer, pipes[i].texture, NULL, &pipes[i].ongtren);
            SDL_RenderCopy(renderer, pipes[i].texture, NULL, &pipes[i].ongduoi);
        }

        string scoreText = "SCORE: " + to_string(score);
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(),black);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
     SDL_Rect scoreRect = { 10, 10, scoreSurface->w, scoreSurface->h };
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
      SDL_FreeSurface(scoreSurface);
   SDL_DestroyTexture(scoreTexture);

        string livesText = "LIVES: " + to_string(bird.lives);
         SDL_Surface* livesSurface = TTF_RenderText_Solid(font, livesText.c_str(), black);
    SDL_Texture* livesTexture = SDL_CreateTextureFromSurface(renderer, livesSurface);
    SDL_Rect livesRect = { 10, 40, livesSurface->w, livesSurface->h };
     SDL_RenderCopy(renderer, livesTexture, NULL, &livesRect);
        SDL_FreeSurface(livesSurface);
        SDL_DestroyTexture(livesTexture);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyTexture(bgTexture);
    SDL_DestroyTexture(bird.texture);
    SDL_DestroyTexture(item.texture);
    SDL_DestroyTexture(pipeTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
