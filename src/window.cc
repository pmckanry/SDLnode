#include <napi.h>
#include <SDL.h>

#include "window.h"

void Window::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function tpl = DefineClass(env, "Window", {
        InstanceMethod("createRenderer", &Window::CreateRenderer),
        InstanceMethod("disableScreenSaver", &Window::DisableScreenSaver),
        InstanceMethod("enableScreenSaver", &Window::EnableScreenSaver),
        InstanceMethod("getRenderer", &Window::GetRenderer),
        InstanceMethod("hide", &Window::Hide),
        InstanceMethod("maximize", &Window::Maximize),
        InstanceMethod("minimize", &Window::Minimize),
        InstanceMethod("setFullscreen", &Window::SetFullscreen),
        InstanceMethod("show", &Window::Show)
    });

    constructor = Napi::Persistent(tpl);
    constructor.SuppressDestruct();

    exports.Set("Window", constructor);
}

Window::Window(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Window>(info) {

}

Window::~Window() {
    printf("Collecting Window\n");
    SDL_DestroyWindow(_window);
}

Napi::Value Window::CreateRenderer(const Napi::CallbackInfo& info) {
    return info.Env().Undefined();
}

void Window::DisableScreenSaver(const Napi::CallbackInfo& info) {
    SDL_DisableScreenSaver();
}

void Window::EnableScreenSaver(const Napi::CallbackInfo& info) {
    SDL_EnableScreenSaver();
}

Napi::Value Window::GetRenderer(const Napi::CallbackInfo& info) {
    return info.Env().Undefined();
}

void Window::Hide(const Napi::CallbackInfo& info) {
    SDL_HideWindow(_window);
}

void Window::Maximize(const Napi::CallbackInfo& info) {
    SDL_MaximizeWindow(_window);
}

void Window::Minimize(const Napi::CallbackInfo& info) {
    SDL_MinimizeWindow(_window);
}

void Window::SetFullscreen(const Napi::CallbackInfo& info) {
    if(info.Length() < 1) {
        throw Napi::Error::New(info.Env(), "Invalid argument for SetFullscreen");
    }
    if(!info[0].IsNumber()) {
        throw Napi::Error::New(info.Env(), "Invalid flag for SetFullscreen");
    }

    int32_t flag = info[0].As<Napi::Number>().Int32Value();

    SDL_SetWindowFullscreen(_window, flag);
}

void Window::Show(const Napi::CallbackInfo& info) {
    SDL_ShowWindow(_window);
}

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