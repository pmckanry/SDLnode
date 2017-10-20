#include <napi.h>
#include <SDL.h>

#include "rect.h"

Napi::FunctionReference Rect::constructor;

void Rect::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function tpl = DefineClass(env, "Rect", {
        InstanceAccessor("x", &Rect::X_Get, &Rect::X_Set),
        InstanceAccessor("y", &Rect::Y_Get, &Rect::Y_Set),
        InstanceAccessor("w", &Rect::W_Get, &Rect::W_Set),
        InstanceAccessor("h", &Rect::H_Get, &Rect::H_Set)
    });

    constructor = Napi::Persistent(tpl);
    constructor.SuppressDestruct();

    exports.Set("Rect", tpl);
}

Rect::Rect(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Rect>(info) {
    int32_t x = 0, y = 0, w = 0, h = 0;

    if(info.Length() > 0) {
        if(info[0].IsObject()) {
            Napi::Object obj = info[0].As<Napi::Object>();

            // Overrides
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
        }
        else if(info.Length() < 4) {
            throw Napi::Error::New(info.Env(), "Invalid number of arguments");
        }

        x = info[0].As<Napi::Number>().Int32Value();
        y = info[1].As<Napi::Number>().Int32Value();
        w = info[2].As<Napi::Number>().Int32Value();
        h = info[3].As<Napi::Number>().Int32Value();
    }

    _rect = SDL_Rect {
        x = x,
        y = y,
        w = w,
        h = h
    };
}

Rect::~Rect() {}

Napi::Value Rect::X_Get(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), _rect.x);
}

void Rect::X_Set(const Napi::CallbackInfo& info, const Napi::Value& value) {
    int32_t x = value.As<Napi::Number>().Int32Value();

    _rect.x = x;
}

Napi::Value Rect::Y_Get(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), _rect.y);
}

void Rect::Y_Set(const Napi::CallbackInfo& info, const Napi::Value& value) {
    int32_t y = value.As<Napi::Number>().Int32Value();
    
    _rect.y = y;
}

Napi::Value Rect::W_Get(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), _rect.w);
}

void Rect::W_Set(const Napi::CallbackInfo& info, const Napi::Value& value) {
    int32_t w = value.As<Napi::Number>().Int32Value();
    
    _rect.w = w;
}

Napi::Value Rect::H_Get(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), _rect.h);
}

void Rect::H_Set(const Napi::CallbackInfo& info, const Napi::Value& value) {
    int32_t h = value.As<Napi::Number>().Int32Value();
    
    _rect.h = h;
}