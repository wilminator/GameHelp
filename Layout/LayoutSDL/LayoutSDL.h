#ifndef __LAYOUTSDL_H__
#define __LAYOUTSDL_H__

#include <SDL/SDL.h>

struct SDL_Resource_Blit_Surface {
    unsigned char resource_type;
    SDL_Surface *surface;
};

#endif //__LAYOUTSDL_H__
