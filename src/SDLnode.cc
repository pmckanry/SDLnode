#include <napi.h>

#include "window.h"
#include "renderer.h"
#include "surface.h"
#include "texture.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    Window::Init(env, exports);
    Renderer::Init(env, exports);
    Surface::Init(env, exports);
    Texture::Init(env, exports);

    return exports;
}

NODE_API_MODULE(SDLnode, InitAll)