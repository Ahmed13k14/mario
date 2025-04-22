#include <SDL2/SDL_image.h>
#include "file.h"

/* Charge une image dans une SDL_Texture avec l'option SDL_TEXTUREACCESS_TARGET */
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *surface = IMG_Load(path);
    if (surface == NULL) {
        fprintf(stderr, "Erreur IMG_Load (%s) : %s\n", path, IMG_GetError());
        return NULL;
    }

    SDL_Texture *tmp = SDL_CreateTextureFromSurface(renderer, surface);
    if (tmp == NULL) {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                             SDL_TEXTUREACCESS_TARGET, surface->w, surface->h);
    if (texture == NULL) {
        fprintf(stderr, "Erreur SDL_CreateTexture (target) : %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(tmp);
        return NULL;
    }

    SDL_SetRenderTarget(renderer, texture); // On rend la texture modifiable
    SDL_SetTextureBlendMode(tmp, SDL_BLENDMODE_NONE); // Gestion de transparence (à adapter)
    SDL_RenderCopy(renderer, tmp, NULL, NULL); // Copie de tmp vers texture modifiable

    // Nettoyage
    SDL_DestroyTexture(tmp);
    SDL_FreeSurface(surface);
    SDL_SetRenderTarget(renderer, NULL); // On remet le renderer à sa cible normale

    return texture;
}

/* Libère la mémoire utilisée par la Map et les Sprites */
void LibererMap(Map* map, Sprites* sprites)
{
    if (map != NULL && map->LoadedMap != NULL) {
        for (int i = 0; i < map->height; i++) {
            free(map->LoadedMap[i]);
        }
        free(map->LoadedMap);
        map->LoadedMap = NULL;
    }// test

    if (sprites != NULL) {
        for (int i = 0; i < NbSprites; i++) {
            if (sprites[i].sprite != NULL) {
                SDL_DestroyTexture(sprites[i].sprite);
            }
        }
    }
}
