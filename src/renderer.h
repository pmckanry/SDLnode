#ifndef SDL_NODE_RENDERER_H
#define SDL_NODE_RENDERER_H

#include <napi.h>
#include <SDL.h>

class Renderer : public Napi::ObjectWrap<Renderer> {
public:
    static void Init(Napi::Env env, Napi::Object exports);
private:
    SDL_Renderer* renderer;
};

#endif // SDL_NODE_RENDERER_H