//
//  main.h
//  BasicGameEvents
//
//  Created by Julie Glasdam on 14/10/2017.
//  Copyright © 2017 Julie Glasdam. All rights reserved.
//
#define main_h

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>

typedef struct {
    int x, y, w, h;
    int currentSprite;
    int direction;
    short life;
    char *name;
    SDL_Texture *sheet00Texture;
} Player;

/* Create instances of all structs, so they can be easy referenced,
 by calling GameState*/
typedef struct {
    Player player;
} GameState;

