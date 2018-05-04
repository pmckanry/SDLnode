#include <napi.h>

#include "sdl.h"
#include "window.h"
#include "renderer.h"
#include "surface.h"
#include "texture.h"
#include "rect.h"
#include "point.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    SDL::Init(env, exports);
    Window::Init(env, exports);
    Renderer::Init(env, exports);
    Surface::Init(env, exports);
    Texture::Init(env, exports);
    Rect::Init(env, exports);
    Point::Init(env, exports);

    return exports;
}

NODE_API_MODULE(SDLnode, InitAll)