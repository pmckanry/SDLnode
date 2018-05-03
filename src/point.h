#ifndef SDL_NODE_POINT_H
#define SDL_NODE_POINT_H

#include <napi.h>
#include <SDL.h>

class Point : public Napi::ObjectWrap<Point> {
public:
    static void Init(Napi::Env env, Napi::Object exports);
    static Napi::FunctionReference constructor;

    explicit Point(const Napi::CallbackInfo& info);
    ~Point();

    Napi::Value X_Get(const Napi::CallbackInfo& info);
    void X_Set(const Napi::CallbackInfo& info, const Napi::Value& value);
    Napi::Value Y_Get(const Napi::CallbackInfo& info);
    void Y_Set(const Napi::CallbackInfo& info, const Napi::Value& value);

    inline SDL_Point* GetPoint() {
        return &_point;
    }

private:
    SDL_Point _point;
};

#endif // SDL_NODE_POINT_H