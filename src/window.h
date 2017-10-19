#ifndef SDL_NODE_WINDOW_H
#define SDL_NODE_WINDOW_H

#include <napi.h>
#include <SDL.h>

class Window : public Napi::ObjectWrap<Window> {
public:
    static void Init(Napi::Env env, Napi::Object exports);
    static Napi::FunctionReference constructor;

    explicit Window(const Napi::CallbackInfo& info);
    ~Window();
    
    Napi::Value CreateRenderer(const Napi::CallbackInfo& info);
    void DisableScreenSaver(const Napi::CallbackInfo& info);
    void EnableScreenSaver(const Napi::CallbackInfo& info);
    Napi::Value GetRenderer(const Napi::CallbackInfo& info);
    void Hide(const Napi::CallbackInfo& info);
    void Maximize(const Napi::CallbackInfo& info);
    void Minimize(const Napi::CallbackInfo& info);
    void SetFullscreen(const Napi::CallbackInfo& info);
    void Show(const Napi::CallbackInfo& info);
    /*
    Napi::Value Icon_Get(const Napi::CallbackInfo& info);
    void Icon_Set(const Napi::CallbackInfo& info, const Napi::Value& value);
    Napi::Value Position_Get(const Napi::CallbackInfo& info);
    void Position_Set(const Napi::CallbackInfo& info, const Napi::Value& value);
    Napi::Value Size_Get(const Napi::CallbackInfo& info);
    void Size_Set(const Napi::CallbackInfo& info, const Napi::Value& value);
    Napi::Value Title_Get(const Napi::CallbackInfo& info);
    void Title_Set(const Napi::CallbackInfo& info, const Napi::Value& value);
    */
private:
    SDL_Window* _window;
};

#endif // SDL_NODE_WINDOW_H