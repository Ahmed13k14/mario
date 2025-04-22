#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "game.h"

#define LARGEUR_FENETRE 1200
#define HAUTEUR_FENETRE 1200

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);

int main(int argc, char *argv[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *menuTexture = NULL;
    SDL_Event event;
    int running = 1;

    if (init(&window, &renderer, LARGEUR_FENETRE, HAUTEUR_FENETRE) != 0) {
        return EXIT_FAILURE;
    }

    menuTexture = IMG_LoadTexture(renderer, "menu.jpg");
    if (!menuTexture) {
        printf("Erreur chargement image: %s\n", IMG_GetError());
        return EXIT_FAILURE;
    }

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = 0;
                        break;
                    case SDLK_1:
                        jouer(renderer);
                        break;
                    case SDLK_2:
                        printf("Crédits : Elias\n");
                        break;
                }
            }
        }
        
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(menuTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur SDL_Init: %s\n", SDL_GetError());
        return -1;
    }

    *window = SDL_CreateWindow("Super Mario Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    if (!*window) {
        printf("Erreur SDL_CreateWindow: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer) {
        printf("Erreur SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return -1;
    }

    return 0;
}
