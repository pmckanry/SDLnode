#ifndef SDL_NODE_TEXTURE_H
#define SDL_NODE_TEXTURE_H

#include <napi.h>
#include <SDL.h>

class Texture : public Napi::ObjectWrap<Texture> {
public:
    static void Init(Napi::Env env, Napi::Object exports);
private:
    SDL_Texture* texture;
};

#endif // SDL_NODE_TEXTURE_H