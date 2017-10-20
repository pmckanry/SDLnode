#include <napi.h>
#include <SDL.h>

#include "window.h"
#include "renderer.h"
#include "surface.h"

Napi::FunctionReference Window::constructor;

void Window::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function tpl = DefineClass(env, "Window", {
        StaticMethod("createWindow", &Window::CreateWindow),
        InstanceMethod("createRenderer", &Window::CreateRenderer),
        InstanceMethod("disableScreenSaver", &Window::DisableScreenSaver),
        InstanceMethod("enableScreenSaver", &Window::EnableScreenSaver),
        InstanceMethod("getRenderer", &Window::GetRenderer),
        InstanceMethod("hide", &Window::Hide),
        InstanceMethod("maximize", &Window::Maximize),
        InstanceMethod("minimize", &Window::Minimize),
        InstanceMethod("setFullscreen", &Window::SetFullscreen),
        InstanceMethod("setIcon", &Window::SetIcon),
        InstanceMethod("show", &Window::Show),
        InstanceAccessor("title", &Window::Title_Get, &Window::Title_Set),
        InstanceAccessor("size", &Window::Size_Get, &Window::Size_Set),
        InstanceAccessor("position", &Window::Position_Get, &Window::Position_Set)
    });
    
    constructor = Napi::Persistent(tpl);
    constructor.SuppressDestruct();

    exports.Set("Window", tpl);
}

Window::Window(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Window>(info) {
    if(info.Length() < 1) {
        throw Napi::Error::New(info.Env(), "Invalid number of arguments");
    }

    _window = info[0].As<Napi::External<SDL_Window>>().Data();
}

Window::~Window() {
    printf("Collecting Window\n");
    SDL_DestroyWindow(_window);
}

Napi::Value Window::CreateWindow(const Napi::CallbackInfo& info) {
    // Defaults
    std::string title = "";
    int32_t x = 0, y = 0, w = 640, h = 480, flags = SDL_WINDOW_SHOWN;
    
    if(info.Length() > 0) {
        if(!info[0].IsObject()) {
            throw Napi::Error::New(info.Env(), "Invalid argument type - requires Object");
        }
        
        Napi::Object obj = info[0].As<Napi::Object>();
    
        // Overrides
        if(obj.Has("title") && obj.Get("title").IsString()) {
            title = obj.Get("title").As<Napi::String>().Utf8Value();
        }
        if(obj.Has("x") && obj.Get("x").IsNumber()) {
            x = obj.Get("x").As<Napi::Number>().Int32Value();
        }
        if(obj.Has("y") && obj.Get("y").IsNumber()) {
            y = obj.Get("y").As<Napi::Number>().Int32Value();
        }
        if(obj.Has("w") && obj.Get("w").IsNumber()) {
            w = obj.Get("w").As<Napi::Number>().Int32Value();
        }
        if(obj.Has("h") && obj.Get("h").IsNumber()) {
            h = obj.Get("h").As<Napi::Number>().Int32Value();
        }
        if(obj.Has("flags") && obj.Get("flags").IsNumber()) {
            flags = obj.Get("flags").As<Napi::Number>().Int32Value();
        }
    }
    
    SDL_Window* sdlWindow = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
    Napi::External<SDL_Window> externalWindow = Napi::External<SDL_Window>::New(info.Env(), sdlWindow);

    return constructor.New({ externalWindow });
}

Napi::Value Window::CreateRenderer(const Napi::CallbackInfo& info) {
    // Defaults
    int32_t index = 0, flags = -1;
    
    if(info.Length() > 0) {
        if(!info[0].IsObject()) {
            throw Napi::Error::New(info.Env(), "Invalid argument type - requires Object");
        }
        
        Napi::Object obj = info[0].As<Napi::Object>();

        // Overrides
        if(obj.Has("index") && obj.Get("index").IsNumber()) {
            index = obj.Get("index").As<Napi::Number>().Int32Value();
        }
        if(obj.Has("flags") && obj.Get("flags").IsNumber()) {
            flags = obj.Get("flags").As<Napi::Number>().Int32Value();
        }
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(_window, index, flags);

    Napi::External<SDL_Renderer> externalRenderer = Napi::External<SDL_Renderer>::New(info.Env(), renderer);

    return Renderer::constructor.New({ externalRenderer });
}

void Window::DisableScreenSaver(const Napi::CallbackInfo& info) {
    SDL_DisableScreenSaver();
}

void Window::EnableScreenSaver(const Napi::CallbackInfo& info) {
    SDL_EnableScreenSaver();
}

Napi::Value Window::GetRenderer(const Napi::CallbackInfo& info) {
    SDL_Renderer* sdlRenderer = SDL_GetRenderer(_window);

    Napi::External<SDL_Renderer> externalRenderer = Napi::External<SDL_Renderer>::New(info.Env(), sdlRenderer);

    return Renderer::constructor.New({ externalRenderer });
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
        throw Napi::Error::New(info.Env(), "Invalid number of arguments for SetFullscreen");
    }

    int32_t flag = info[0].As<Napi::Number>().Int32Value();

    SDL_SetWindowFullscreen(_window, flag);
}

void Window::SetIcon(const Napi::CallbackInfo& info) {
    if(info.Length() < 1) {
        throw Napi::Error::New(info.Env(), "Invalid number of arguments for SetFullscreen");
    }

    Napi::Object obj = info[0].As<Napi::Object>();

    Surface* surface = Surface::Unwrap(obj);

    SDL_SetWindowIcon(_window, surface->GetSurface());
}

void Window::Show(const Napi::CallbackInfo& info) {
    SDL_ShowWindow(_window);
}


Napi::Value Window::Position_Get(const Napi::CallbackInfo& info) {
    int x, y;
    Napi::Object obj = Napi::Object::New(info.Env());

    SDL_GetWindowPosition(_window, &x, &y);

    obj.Set("x", Napi::Number::New(info.Env(), x));
    obj.Set("y", Napi::Number::New(info.Env(), y));

    return obj;
}

void Window::Position_Set(const Napi::CallbackInfo& info, const Napi::Value& value) {
    Napi::Object obj = value.As<Napi::Object>();
    
    int32_t x = obj.Get("x").As<Napi::Number>().Int32Value();
    int32_t y = obj.Get("y").As<Napi::Number>().Int32Value();

    SDL_SetWindowPosition(_window, x, y);
}

Napi::Value Window::Size_Get(const Napi::CallbackInfo& info) {
    int w, h;
    Napi::Object obj = Napi::Object::New(info.Env());

    SDL_GetWindowSize(_window, &w, &h);

    obj.Set("w", Napi::Number::New(info.Env(), w));
    obj.Set("h", Napi::Number::New(info.Env(), h));

    return obj;
}

void Window::Size_Set(const Napi::CallbackInfo& info, const Napi::Value& value) {
    Napi::Object obj = value.As<Napi::Object>();

    int32_t w = obj.Get("w").As<Napi::Number>().Int32Value();
    int32_t h = obj.Get("h").As<Napi::Number>().Int32Value();

    SDL_SetWindowSize(_window, w, h);
}

Napi::Value Window::Title_Get(const Napi::CallbackInfo& info) {
    const char* title = SDL_GetWindowTitle(_window);

    return Napi::String::New(info.Env(), title);
}

void Window::Title_Set(const Napi::CallbackInfo& info, const Napi::Value& value) {
    std::string title = value.As<Napi::String>().Utf8Value();

    SDL_SetWindowTitle(_window, title.c_str());
}