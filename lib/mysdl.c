#include "mysdl.h"
#include <stdio.h>
#include <stdlib.h>


GLAPI MySDL_Surface* APIENTRY MySDL_CreateRGBSurface(int width, int height, int depth,
	unsigned int Rmask, unsigned int Gmask, unsigned int Bmask, unsigned int Amask)
{
	MySDL_Surface * surface = (MySDL_Surface *)malloc(sizeof(MySDL_Surface));
	if (surface == NULL)
	{
		return surface;
	}


	surface->w = width;
	surface->h = height;
	surface->locked = 0;
	surface->clip_rect.x = 0;
	surface->clip_rect.y = 0;
	surface->clip_rect.w = width;
	surface->clip_rect.h = height;
	surface->pitch = width * 4;
	surface->pixels = malloc(surface->pitch*height);

	surface->refcount = 1;

	return surface;
}

GLAPI void APIENTRY MySDL_FreeSurface(MySDL_Surface *surface)
{
	surface->refcount--;

	if (surface->refcount == 0)
	{
		free(surface);
	}
}

GLAPI int APIENTRY MySDL_MUSTLOCK(MySDL_Surface* surface)
{
	return 0;
}

GLAPI int APIENTRY MySDL_LockSurface(MySDL_Surface *surface)
{
	return 1;
}

GLAPI void APIENTRY MySDL_UnlockSurface(MySDL_Surface *surface)
{

}



