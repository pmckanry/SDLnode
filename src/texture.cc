#include <napi.h>
#include <SDL.h>

#include "texture.h"

Napi::FunctionReference Texture::constructor;

void Texture::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function tpl = DefineClass(env, "Texture", {
        InstanceMethod("query", &Texture::Query)
    });

    constructor = Napi::Persistent(tpl);
    constructor.SuppressDestruct();
}

Texture::Texture(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Texture>(info) {
    if(info.Length() < 1) {
        throw Napi::Error::New(info.Env(), "Invalid number of arguments");
    }

    _texture = info[0].As<Napi::External<SDL_Texture>>().Data();
}

Texture::~Texture() {
    printf("Collecting Texture\n");
    SDL_DestroyTexture(_texture);
}

void Texture::Lock(const Napi::CallbackInfo& info) {
    // TODO
    // SDL_LockTexture(_texture);
}

Napi::Value Texture::Query(const Napi::CallbackInfo& info) {
    int w, h;
    SDL_QueryTexture(_texture, NULL, NULL, &w, &h);

    Napi::Object obj = Napi::Object::New(info.Env());
    obj.Set("w", Napi::Number::New(info.Env(), w));
    obj.Set("h", Napi::Number::New(info.Env(), h));

    return obj;
}

void Texture::Unlock(const Napi::CallbackInfo& info) {
    // TODO
    // SDL_UnlockTexture(_texture);
}