#ifndef _MY_SDL_H
#define _MY_SDL_H

#include <gl.h>

typedef struct _SDL_Rect {
	signed short x, y;
	unsigned short w, h;
} MySDL_Rect;


typedef struct _MySDL_Surface {
	int w;
	int h;
	unsigned short pitch;		
	void *pixels;				
	MySDL_Rect clip_rect;
	unsigned int locked;			
	int refcount;
}MySDL_Surface;



GLAPI MySDL_Surface* APIENTRY MySDL_CreateRGBSurface(int width, int height, int depth,
	unsigned int Rmask, unsigned int Gmask, unsigned int Bmask, unsigned int Amask);

GLAPI void APIENTRY MySDL_FreeSurface(MySDL_Surface *surface);

GLAPI int APIENTRY MySDL_MUSTLOCK(MySDL_Surface* surface);

GLAPI int APIENTRY MySDL_LockSurface(MySDL_Surface *surface);

GLAPI void APIENTRY MySDL_UnlockSurface(MySDL_Surface *surface);




#endif

