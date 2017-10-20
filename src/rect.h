#ifndef SDL_NODE_RECT_H
#define SDL_NODE_RECT_H

#include <napi.h>
#include <SDL.h>

class Rect : public Napi::ObjectWrap<Rect> {
public:
    static void Init(Napi::Env env, Napi::Object exports);
    static Napi::FunctionReference constructor;

    explicit Rect(const Napi::CallbackInfo& info);
    ~Rect();

    Napi::Value X_Get(const Napi::CallbackInfo& info);
    void X_Set(const Napi::CallbackInfo& info, const Napi::Value& value);
    Napi::Value Y_Get(const Napi::CallbackInfo& info);
    void Y_Set(const Napi::CallbackInfo& info, const Napi::Value& value);
    Napi::Value W_Get(const Napi::CallbackInfo& info);
    void W_Set(const Napi::CallbackInfo& info, const Napi::Value& value);
    Napi::Value H_Get(const Napi::CallbackInfo& info);
    void H_Set(const Napi::CallbackInfo& info, const Napi::Value& value);

    inline SDL_Rect* GetRect() {
        return &_rect;
    }

private:
    SDL_Rect _rect;
};

#endif // SDL_NODE_RECT_H