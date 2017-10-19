#ifndef SDL_NODE_SURFACE_H
#define SDL_NODE_SURFACE_H

#include <napi.h>
#include <SDL.h>

class Surface : public Napi::ObjectWrap<Surface> {
public:
    static void Init(Napi::Env env, Napi::Object exports);
private:
    SDL_Surface* surface;
};

#endif // SDL_NODE_SURFACE_H