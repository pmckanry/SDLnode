#include <napi.h>
#include <SDL.h>

#include "sdl.h"

void SDL::Init(Napi::Env env, Napi::Object exports) {
    Napi::Object obj = Napi::Object::New(env);

    obj.Set(Napi::String::New(env, "init"), Napi::Function::New(env, SDL::InitSdl));
    obj.Set(Napi::String::New(env, "initSubSystem"), Napi::Function::New(env, SDL::InitSubSystem));
    obj.Set(Napi::String::New(env, "quit"), Napi::Function::New(env, SDL::Quit));
    obj.Set(Napi::String::New(env, "quitSubSystem"), Napi::Function::New(env, SDL::QuitSubSystem));
    obj.Set(Napi::String::New(env, "wasInit"), Napi::Function::New(env, SDL::WasInit));

    exports.Set(Napi::String::New(env, "SDL"), obj);
}
Napi::Value SDL::InitSdl(const Napi::CallbackInfo& info) {
    if(info.Length() < 1) {
        throw Napi::Error::New(info.Env(), "Invalid number of arguments");
    }

    uint32_t flags = info[0].As<Napi::Number>().Uint32Value();

    return Napi::Number::New(info.Env(), SDL_Init(flags));
}
Napi::Value SDL::InitSubSystem(const Napi::CallbackInfo& info) {
    if(info.Length() < 1) {
        throw Napi::Error::New(info.Env(), "Invalid number of arguments");
    }

    uint32_t flags = info[0].As<Napi::Number>().Uint32Value();

    return Napi::Number::New(info.Env(), SDL_InitSubSystem(flags));
}
void SDL::QuitSubSystem(const Napi::CallbackInfo& info) {
    if(info.Length() < 1) {
        throw Napi::Error::New(info.Env(), "Invalid number of arguments");
    }

    uint32_t flags = info[0].As<Napi::Number>().Uint32Value();

    SDL_QuitSubSystem(flags);
}
Napi::Value SDL::WasInit(const Napi::CallbackInfo& info) {
    if(info.Length() < 1) {
        throw Napi::Error::New(info.Env(), "Invalid number of arguments");
    }

    uint32_t flags = info[0].As<Napi::Number>().Uint32Value();

    return Napi::Number::New(info.Env(), SDL_WasInit(flags));
}
void SDL::Quit(const Napi::CallbackInfo& info) {
    SDL_Quit();
}