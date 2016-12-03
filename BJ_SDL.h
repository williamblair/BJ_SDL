/*
 * Test library header
 * */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

#include <stdio.h>
#include <stdarg.h> // for variable length free surface func

#ifndef BJ_SDL_INCLUDED
#define BJ_SDL_INCLUDED

/* Init SDL, SDL_image
 * returns -1 on failure, 0 on success
 * */
int BJ_InitSDL(void);

/* Free any number of SDL_Surfaces, Quit SDL and IMG */
void BJ_QuitSDL(SDL_Surface *s, ...);

/* Create a SDL_Surface window
 * returns NULL on failure */
SDL_Surface *BJ_CreateWindow(unsigned int width, unsigned int height,
                             const char *title);

/* fills the window with given color combo */
void BJ_ClearWindow(SDL_Surface *win, int r, int g, int b);

/* load and optimize an image
 * for transparency bg should be 255,0,255 */
SDL_Surface *BJ_LoadImage(const char *f);

/* Create and render a TTF font message */
SDL_Surface *BJ_CreateMessage(TTF_Font *f, const char *message,
                              int r, int g, int b);

/* apply one surface to another with x and y and width and height */
void BJ_ApplySurface(int x, int y, SDL_Surface *src, SDL_Surface *dst);

#endif
