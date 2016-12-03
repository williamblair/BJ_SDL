/*
 * Test Library
 *
 * */

#include "BJ_SDL.h"


/* init SDL and IMG and Mixer */
int BJ_InitSDL(void)
{

  /* init SDL */
  if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ){
    fprintf(stdout, "Error initializing SDL: %s\n", SDL_GetError() );
    return -1;
  }

  /* init SDL_image */
  int flags = IMG_INIT_JPG | IMG_INIT_PNG;
  int initted=IMG_Init(flags);
  if( initted&flags != flags ){
    fprintf(stdout, "Error initializing IMG: %s\n", IMG_GetError());
    return -1;
  }

  /* init SDL_ttf */
  if( TTF_Init() == -1 ){
    fprintf(stdout, "Error initializing TTF: %s\n", TTF_GetError());
    return -1;
  }

  /* TODO - figure out why this with Mix_CloseAudio / Mix_Quit crashes */
  /* init SDL mixer */
  //flags = MIX_INIT_MP3;
  //initted = Mix_Init(flags);
  //if( initted&flags != flags ){
//    fprintf(stdout, "Failed to init Mixer (mp3)!\n%s\n", Mix_GetError());
//    return -1;
//  }

  /* 44.1 khz, signed 16bit, system byte order, stereo audiom 1024 byte chunks */
  if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
    fprintf(stdout, "Failed to init Mixer (audio): %s\n", Mix_GetError());
    return -1;
  }

  return 0;
}

/* quit libraries */
void BJ_QuitSDL(SDL_Surface *s, ...)
{
  /* a list to access all arguments */
  va_list surf_list;
  va_start( surf_list, s );

  SDL_Surface *temp = NULL; // placeholder for each surface
  while( (temp = (SDL_Surface *)va_arg(surf_list, SDL_Surface*)) != NULL )
  {
    SDL_FreeSurface(temp);
    temp = NULL;
  }

  va_end( surf_list );

//  Mix_CloseAudio();
//  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();

  return;
}

/* create an SDL Window and error check */
SDL_Surface *BJ_CreateWindow(unsigned int width, unsigned int height,
                             const char *title) {
  /* Create the window */
  SDL_Surface *w = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);

  /* error check */
  if( w == NULL ) {
    fprintf(stdout, "Error setting video mode: %s\n", SDL_GetError() );
  }
  else {
    /* Set the window title */
    SDL_WM_SetCaption(title, NULL);
  }

  return w;
}

/* fills the window with given color combo */
void BJ_ClearWindow(SDL_Surface *win, int r, int g, int b)
{
  SDL_FillRect(win, NULL, SDL_MapRGB(win->format, r, g, b));
  return;
}

/* load and optimize an image */
SDL_Surface *BJ_LoadImage(const char *f)
{
  /* temp to load image */
  SDL_Surface *temp = NULL;

  /* optimized surface to return */
  SDL_Surface *opt = NULL;

  /* load the image */
  temp = IMG_Load(f);
  if( !temp ){
    fprintf(stdout, "Error opening %s\n%s\n", f, IMG_GetError() );
  }
  /* if loaded successfully */
  else
  {
    /* optimize the image */
    opt = SDL_DisplayFormat(temp);

    /* free the temp image */
    SDL_FreeSurface(temp);

    /* make sure load was successfull and apply transparency */
    if( opt != NULL ){
      Uint32 colorKey = SDL_MapRGB(opt->format, 255, 0, 255);

      /* apply specified transparent color */
      SDL_SetColorKey(opt, SDL_SRCCOLORKEY, colorKey);
    }
  }

  return opt;
}

/* Create and render a TTF font message */
SDL_Surface *BJ_CreateMessage(TTF_Font *f, const char *message,
                              int r, int g, int b)
{
  SDL_Surface *temp = NULL; // the rendered surface to return
  SDL_Color c = {r,g,b}; //  create the color to render in
  temp = TTF_RenderText_Solid(f, "Hello World", c);
  if( !temp ){
    fprintf(stdout, "Error rendering text: %s\n", TTF_GetError());
  }

  return temp;
}

/* apply one surface to another with x and y */
void BJ_ApplySurface(int x, int y, SDL_Surface *src, SDL_Surface *dst)
{
  SDL_Rect offset; // holds coords

  // sets coords
  offset.x = x;
  offset.y = y;

  SDL_BlitSurface(src, NULL, dst, &offset);

  return;
}
