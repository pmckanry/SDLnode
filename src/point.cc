#include <napi.h>
#include <SDL.h>

#include "point.h"

Napi::FunctionReference Point::constructor;

void Point::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function tpl = DefineClass(env, "Point", {
        InstanceAccessor("x", &Point::X_Get, &Point::X_Set),
        InstanceAccessor("y", &Point::Y_Get, &Point::Y_Set)
    });

    constructor = Napi::Persistent(tpl);
    constructor.SuppressDestruct();

    exports.Set("Point", tpl);
}

Point::Point(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Point>(info) {
    int32_t x = 0, y = 0;

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
        }
        else if(info.Length() < 2) {
            throw Napi::Error::New(info.Env(), "Invalid number of arguments");
        }
        else {
            x = info[0].As<Napi::Number>().Int32Value();
            y = info[1].As<Napi::Number>().Int32Value();
        }
    }

    _point = SDL_Point {
        x = x,
        y = y
    };
}

Point::~Point() {}

Napi::Value Point::X_Get(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), _point.x);
}

void Point::X_Set(const Napi::CallbackInfo& info, const Napi::Value& value) {
    int32_t x = value.As<Napi::Number>().Int32Value();

    _point.x = x;
}

Napi::Value Point::Y_Get(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), _point.y);
}

void Point::Y_Set(const Napi::CallbackInfo& info, const Napi::Value& value) {
    int32_t y = value.As<Napi::Number>().Int32Value();
    
    _point.y = y;
}