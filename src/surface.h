#ifndef SDL_NODE_SURFACE_H
#define SDL_NODE_SURFACE_H

#include <napi.h>
#include <SDL.h>

class Surface : public Napi::ObjectWrap<Surface> {
public:
    static void Init(Napi::Env env, Napi::Object exports);
    static Napi::FunctionReference constructor;
    static Napi::Value LoadImage(const Napi::CallbackInfo& info);

    Surface(const Napi::CallbackInfo& info);
    ~Surface();

    Napi::Value CreateSoftwareRenderer(const Napi::CallbackInfo& info);
    void Lock(const Napi::CallbackInfo& info);
    void Unlock(const Napi::CallbackInfo& info);

    inline SDL_Surface* GetSurface() {
        return _surface;
    }
private:
    SDL_Surface* _surface;
};

#endif // SDL_NODE_SURFACE_H