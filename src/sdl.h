#ifndef SDL_NODE_H
#define SDL_NODE_H

#include <napi.h>

class SDL {
    public:
        static void Init(Napi::Env env, Napi::Object exports);
        static Napi::Value InitSdl(const Napi::CallbackInfo& info);
        static Napi::Value InitSubSystem(const Napi::CallbackInfo& info);
        static void QuitSubSystem(const Napi::CallbackInfo& info);
        static Napi::Value WasInit(const Napi::CallbackInfo& info);
        static void Quit(const Napi::CallbackInfo& info);
};

#endif // SDL_NODE_H