#ifndef SDL_NODE_RENDERER_H
#define SDL_NODE_RENDERER_H

#include <napi.h>
#include <SDL.h>

class Renderer : public Napi::ObjectWrap<Renderer> {
public:
    static void Init(Napi::Env env, Napi::Object exports);
    static Napi::FunctionReference constructor;

    explicit Renderer(const Napi::CallbackInfo& info);
    ~Renderer();

    void Clear(const Napi::CallbackInfo& info);
    void Copy(const Napi::CallbackInfo& info);
    Napi::Value CreateTexture(const Napi::CallbackInfo& info);
    void DrawPoint(const Napi::CallbackInfo& info);
    void DrawPoints(const Napi::CallbackInfo& info);
    void DrawLine(const Napi::CallbackInfo& info);
    void DrawLines(const Napi::CallbackInfo& info);
    void DrawRect(const Napi::CallbackInfo& info);
    void DrawRects(const Napi::CallbackInfo& info);
    void FillRect(const Napi::CallbackInfo& info);
    void FillRects(const Napi::CallbackInfo& info);
    Napi::Value GetOutputSize(const Napi::CallbackInfo& info);
    Napi::Value GetInfo(const Napi::CallbackInfo& info);
    Napi::Value IsClipEnabled(const Napi::CallbackInfo& info);
    Napi::Value IsRenderTargetSupported(const Napi::CallbackInfo& info);
    void Present(const Napi::CallbackInfo& info);
    Napi::Value ReadPixels(const Napi::CallbackInfo& info);
    
private:
    SDL_Renderer* _renderer;
};

#endif // SDL_NODE_RENDERER_H