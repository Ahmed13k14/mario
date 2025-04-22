#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "file.h"
#include "game.h"

//test
// Affiche l’écran de crédits avec "credits.png"
void afficherCredits(SDL_Renderer *renderer) {
    SDL_Texture *creditTexture = loadImage("credits.png", renderer);
    if (!creditTexture) {
        SDL_Log("Erreur chargement credits.png");
        return;
    }

    bool inCredits = true;
    SDL_Event event;

    while (inCredits) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, creditTexture, NULL, NULL);
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                inCredits = false;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    inCredits = false;
                }
            }
        }

        SDL_Delay(10);
    }

    SDL_DestroyTexture(creditTexture);
}

int main(int argc, char *argv[]) {
    // Initialisation SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Erreur SDL_Init : %s", SDL_GetError());
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        SDL_Log("Erreur IMG_Init : %s", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // Création de la fenêtre
    SDL_Window *window = SDL_CreateWindow("Menu du Jeu",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        LARGEUR_FENETRE, HAUTEUR_FENETRE, 0);

    if (!window) {
        SDL_Log("Erreur création fenêtre : %s", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Création du renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Erreur création renderer : %s", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Chargement du menu principal
    SDL_Texture *menuTexture = loadImage("menu.jpg", renderer);
    if (!menuTexture) {
        SDL_Log("Erreur chargement menu.jpg");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    case SDLK_1:
                        jouer(renderer);
                        break;
                    case SDLK_2:
                        afficherCredits(renderer); // Affiche credits.png
                        break;
                    default:
                        break;
                }
            }
        }

        SDL_Delay(10);
    }

    SDL_DestroyTexture(menuTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
