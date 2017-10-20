#include <napi.h>
#include <SDL.h>
#include <SDL_image.h>

#include "surface.h"
#include "renderer.h"

Napi::FunctionReference Surface::constructor;

void Surface::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function tpl = DefineClass(env, "Surface", {
        InstanceMethod("lock", &Surface::Lock),
        InstanceMethod("unlock", &Surface::Unlock),
        InstanceMethod("createSoftwareRenderer", &Surface::CreateSoftwareRenderer),
        StaticMethod("load", &Surface::Load)
    });

    constructor = Napi::Persistent(tpl);
    constructor.SuppressDestruct();
}

Surface::Surface(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Surface>(info) {
    if(info.Length() < 1) {
        throw Napi::Error::New(info.Env(), "Invalid number of arguments");
    }

    _surface = info[0].As<Napi::External<SDL_Surface>>().Data();
}

Surface::~Surface() {
    printf("Collecting Surface\n");
    SDL_FreeSurface(_surface);
}

Napi::Value Surface::Load(const Napi::CallbackInfo& info) {
    if(info.Length() < 1) {
        throw Napi::Error::New(info.Env(), "Invalid number of arguments");
    }

    std::string filename = info[0].As<Napi::String>().Utf8Value();

    SDL_Surface* sdlSurface = IMG_Load(filename.c_str());

    Napi::External<SDL_Surface> externalSurface = Napi::External<SDL_Surface>::New(info.Env(), sdlSurface);
    
    return constructor.New({ externalSurface });
}

Napi::Value Surface::CreateSoftwareRenderer(const Napi::CallbackInfo& info) {
    SDL_Renderer* sdlRenderer = SDL_CreateSoftwareRenderer(_surface);

    Napi::External<SDL_Renderer> externalRenderer = Napi::External<SDL_Renderer>::New(info.Env(), sdlRenderer);

    return Renderer::constructor.New({ externalRenderer });
}

void Surface::Lock(const Napi::CallbackInfo& info) {
    SDL_LockSurface(_surface);
}

void Surface::Unlock(const Napi::CallbackInfo& info) {
    SDL_UnlockSurface(_surface);
}