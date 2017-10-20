#ifndef SDL_NODE_TEXTURE_H
#define SDL_NODE_TEXTURE_H

#include <napi.h>
#include <SDL.h>

class Texture : public Napi::ObjectWrap<Texture> {
public:
    static void Init(Napi::Env env, Napi::Object exports);
    static Napi::FunctionReference constructor;

    explicit Texture(const Napi::CallbackInfo& info);
    ~Texture();

    void Lock(const Napi::CallbackInfo& info);
    Napi::Value Query(const Napi::CallbackInfo& info);
    void Unlock(const Napi::CallbackInfo& info);

    inline SDL_Texture* GetTexture() {
        return _texture;
    }
private:
    SDL_Texture* _texture;
};

#endif // SDL_NODE_TEXTURE_H