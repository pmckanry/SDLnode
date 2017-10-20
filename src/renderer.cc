#include <napi.h>
#include <SDL.h>

#include "renderer.h"
#include "surface.h"
#include "texture.h"
#include "rect.h"

Napi::FunctionReference Renderer::constructor;

void Renderer::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function tpl = DefineClass(env, "Renderer", {
        InstanceMethod("clear", &Renderer::Clear),
        InstanceMethod("copy", &Renderer::Copy),
        InstanceMethod("createTexture", &Renderer::CreateTexture),
        InstanceMethod("drawPoint", &Renderer::DrawPoint),
        InstanceMethod("drawPoints", &Renderer::DrawPoints),
        InstanceMethod("drawLine", &Renderer::DrawLine),
        InstanceMethod("drawLines", &Renderer::DrawLines),
        InstanceMethod("drawRect", &Renderer::DrawRect),
        InstanceMethod("drawRect", &Renderer::DrawRects),
        InstanceMethod("fillRect", &Renderer::FillRect),
        InstanceMethod("fillRects", &Renderer::FillRects),
        InstanceMethod("getOutputSize", &Renderer::GetOutputSize),
        InstanceMethod("getInfo", &Renderer::GetInfo),
        InstanceMethod("isClipEnabled", &Renderer::IsClipEnabled),
        InstanceMethod("isRenderTargetSupported", &Renderer::IsRenderTargetSupported),
        InstanceMethod("present", &Renderer::Present),
        InstanceMethod("readPixels", &Renderer::ReadPixels)
    });

    constructor = Napi::Persistent(tpl);
    constructor.SuppressDestruct();
}

Renderer::Renderer(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Renderer>(info) {
    if(info.Length() < 1) {
        throw Napi::Error::New(info.Env(), "Invalid number of arguments");
    }

    _renderer = info[0].As<Napi::External<SDL_Renderer>>().Data();
}

Renderer::~Renderer() {
    printf("Collecting Renderer\n");
    SDL_DestroyRenderer(_renderer);
}

void Renderer::Clear(const Napi::CallbackInfo& info) {
    SDL_RenderClear(_renderer);
}

void Renderer::Copy(const Napi::CallbackInfo& info) {
    if(info.Length() < 3) {
        throw Napi::Error::New(info.Env(), "Invalid number of arguments");
    }
    
    Texture* texture = Texture::Unwrap(info[0].As<Napi::Object>());
    Rect* srcRect = Rect::Unwrap(info[1].As<Napi::Object>());
    Rect* dstRect = Rect::Unwrap(info[2].As<Napi::Object>());

    SDL_RenderCopy(_renderer, texture->GetTexture(), srcRect->GetRect(), dstRect->GetRect());
}

Napi::Value Renderer::CreateTexture(const Napi::CallbackInfo& info) {
    if(info.Length() < 1) {
        throw Napi::Error::New(info.Env(), "Invalid number of arguments");
    }

    Napi::Object obj = info[0].As<Napi::Object>();

    Surface* surface = Surface::Unwrap(obj);
    
    SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(_renderer, surface->GetSurface());
    Napi::External<SDL_Texture> externalTexture = Napi::External<SDL_Texture>::New(info.Env(), sdlTexture);

    return Texture::constructor.New({ externalTexture });
}

void Renderer::DrawPoint(const Napi::CallbackInfo& info) {
    
}

void Renderer::DrawPoints(const Napi::CallbackInfo& info) {

}

void Renderer::DrawLine(const Napi::CallbackInfo& info) {

}

void Renderer::DrawLines(const Napi::CallbackInfo& info) {

}

void Renderer::DrawRect(const Napi::CallbackInfo& info) {
    if(info.Length() < 1) {
        throw Napi::Error::New(info.Env(), "Invalid number of arguments");
    }

    Rect* rect = Rect::Unwrap(info[0].As<Napi::Object>());

    SDL_RenderDrawRect(_renderer, rect->GetRect());
}

void Renderer::DrawRects(const Napi::CallbackInfo& info) {

}

void Renderer::FillRect(const Napi::CallbackInfo& info) {
    if(info.Length() < 1) {
        throw Napi::Error::New(info.Env(), "Invalid number of arguments");
    }

    Rect* rect = Rect::Unwrap(info[0].As<Napi::Object>());

    SDL_RenderFillRect(_renderer, rect->GetRect());
}

void Renderer::FillRects(const Napi::CallbackInfo& info) {

}

Napi::Value Renderer::GetOutputSize(const Napi::CallbackInfo& info) {
    int w, h;
    Napi::Object obj = Napi::Object::New(info.Env());

    SDL_GetRendererOutputSize(_renderer, &w, &h);

    obj.Set("w", Napi::Number::New(info.Env(), w));
    obj.Set("h", Napi::Number::New(info.Env(), h));

    return obj;
}

Napi::Value Renderer::GetInfo(const Napi::CallbackInfo& info) {
    SDL_RendererInfo renderInfo;
    Napi::Object obj = Napi::Object::New(info.Env());

    SDL_GetRendererInfo(_renderer, &renderInfo);

    obj.Set("name", Napi::String::New(info.Env(), renderInfo.name));
    obj.Set("flags", Napi::Number::New(info.Env(), renderInfo.flags));
    obj.Set("numTextureFormats", Napi::Number::New(info.Env(), renderInfo.num_texture_formats));
    obj.Set("maxTextureWidth", Napi::Number::New(info.Env(), renderInfo.max_texture_width));
    obj.Set("maxTextureHeight", Napi::Number::New(info.Env(), renderInfo.max_texture_height));
    // TODO
    //obj.Set("textureFormats", Napi::Array::New(info.Env()));

    return obj;
}

Napi::Value Renderer::IsClipEnabled(const Napi::CallbackInfo& info) {
    bool sdlIsClipEnabled = SDL_RenderIsClipEnabled(_renderer);

    return Napi::Boolean::New(info.Env(), sdlIsClipEnabled);
}

Napi::Value Renderer::IsRenderTargetSupported(const Napi::CallbackInfo& info) {
    bool sdlRenderTargetSupported = SDL_RenderTargetSupported(_renderer);

    return Napi::Boolean::New(info.Env(), sdlRenderTargetSupported);
}

void Renderer::Present(const Napi::CallbackInfo& info) {
    SDL_RenderPresent(_renderer);
}

Napi::Value Renderer::ReadPixels(const Napi::CallbackInfo& info) {
    return info.Env().Undefined();
}