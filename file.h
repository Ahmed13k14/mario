#ifndef DEF_FILE
#define DEF_FILE
    
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h> // Ajouté

    #define NbSprites 10
    #define Size_Sprite 40
    #define LARGEUR_FENETRE 1200
    #define HAUTEUR_FENETRE 1200

    typedef struct Map {
        int width, height;
        int** LoadedMap;
        int xscroll, yscroll;
    } Map;

    typedef struct Sprites {
        SDL_Texture* sprite;
        int traverser;
    } Sprites;

    SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);
    void LibererMap(Map* map, Sprites* sprites);

#endif
