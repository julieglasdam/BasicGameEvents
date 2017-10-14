//
//  main.c
//  Pixelman2
//
//  Created by Julie Glasdam on 14/10/2017.
//  Copyright © 2017 Julie Glasdam. All rights reserved.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

#include "main.h"
#include "define.h"

int globalTime = 0;

/* Method checks if a key is pressed and act accordingly
 Parameter: gamestate object
 */
void checkKeyboardEvent(GameState *game) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_A]){
        game->player.direction = 0;
        game->player.x -= 8;
       // changeSprite(game);
    }
    else if(state[SDL_SCANCODE_D]){
        game->player.direction = 1;
        game->player.x += 8;
      //  changeSprite(game);
        
    }
    else if(state[SDL_SCANCODE_W]){
        game->player.direction = 3;
        game->player.y -= 8;
     //   changeSprite(game);
        
    }
    else if(state[SDL_SCANCODE_S]){
        game->player.direction = 2;
        game->player.y += 8;
     //   changeSprite(game);
        
    }
    else {
      //  game->player.currentSprite = 0;
    }
}




/* Check if any keys or buttons are pressed to close window
 The method returns an int to let main know if program should be terminated or not
 Parameters are the window object, and the gamestate object
 */
int processEvents(SDL_Window *window, GameState *game) {
    SDL_Event event;
    int done = 0;
    
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_WINDOWEVENT_CLOSE:{
                if(window){
                    SDL_DestroyWindow(window);
                    window = NULL;
                    done = 1;
                }
            }
                break;
            case SDL_KEYDOWN: {
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        done = 1;
                        break;
                }
            }
                break;
            case SDL_QUIT:
                done = 1;
                break;
        }
    }
    
    checkKeyboardEvent(game);
    return done;
}



/* This method draws the background and presents it to the window
 Parameters: renderer object and gamestate object
 */
void doRender(SDL_Renderer *renderer, GameState *game){
    game->player.currentSprite = 0; // temp
    
    //set the drawing color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    //Clear the screen
    SDL_RenderClear(renderer);
    
    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // temp
    
    //Draw player
    SDL_Rect srcRect = { 157*game->player.currentSprite, 177*game->player.direction, PLAYER_W, PLAYER_H};
    SDL_Rect rect = { game->player.x, game->player.y, PLAYER_W, PLAYER_H };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // temp
    SDL_RenderFillRect(renderer, &rect); // temp
    
  /*  SDL_RenderCopyEx(renderer,                            // renderer
                     game->player.sheet00Texture,         // the texture to apply the rectangle
                     &srcRect,                            // defines which part of texture to use. Leave null to use the whole image
                     &rect,                               // define target
                     0,                                   // the angle of target
                     NULL,                                // the point to rotate. I don't know why this is null
                     0);    */                              // 0 for no flip, 1 for flip
    
    
    //We are done drawing, "present" or show to the screen what we've drawn
    SDL_RenderPresent(renderer);
}

/* Load all textures for the game, assign them to an SDL_Texture object and free the textures
 Parameters: Renderer and GameState object
 */
/*void loadTextures(SDL_Renderer *renderer, GameState *game) {
    // Load texture for the player
    SDL_Surface *sheet00Surface = IMG_Load("textures/spriteTEST13.png");
    if(!sheet00Surface){
        printf("Cannot find 'sheet00LeftTexture'\n");
    }
    
    game->player.sheet00Texture = SDL_CreateTextureFromSurface(renderer, sheet00Surface);
    SDL_FreeSurface(sheet00Surface);
    
}*/





int main(int argc, char *argv[]) {
    int done = 0;
    SDL_Window *window;                    // Declare a window
    SDL_Renderer *renderer;                // Declare a renderer
    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
    
    // Create instance of GameState to utilize when calling methods
    GameState gamestate;
    
    // Set player attributes, before beginning game
    gamestate.player.x = 220;
    gamestate.player.y = 140;
    gamestate.player.currentSprite = 0;
    gamestate.player.direction = 0;
    
    //Create an application window with the following settings:
    window = SDL_CreateWindow("Basic Game Events",                      // window title
                              SDL_WINDOWPOS_UNDEFINED,           // initial x position
                              SDL_WINDOWPOS_UNDEFINED,           // initial y position
                              WINDOW_H,                          // width, in pixels
                              WINDOW_W,                          // height, in pixels
                              0                                  // flags
                              | SDL_WINDOW_RESIZABLE             // enable resize
                              );
    
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // PREVENTSYNC makes animations run smoother
    
    // Load textures
   // loadTextures(renderer, &gamestate);
    
    // Run this as long as program is not exited
    while(!done){
        globalTime++;
        done = processEvents(window, &gamestate);
        doRender(renderer, &gamestate);
    }
    
    // Close and destroy the window
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    
    // Destroy textures
    SDL_DestroyTexture(gamestate.player.sheet00Texture);
    
    // Clean up
    TTF_Quit();
    SDL_Quit();
    return 0;
}
