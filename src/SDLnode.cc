#include <node_api.h>



napi_value Init(napi_env env, napi_value exports) {
    return exports;
}

NAPI_MODULE(SDLnode, Init)