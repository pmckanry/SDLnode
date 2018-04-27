{
    "targets": [
        {
            "target_name": "node-sdl",
            "sources": [ 
                "src/node-sdl.cc" ,
                "src/sdl.cc",
                "src/window.cc",
                "src/renderer.cc",
                "src/texture.cc",
                "src/surface.cc"
            ],
            "include_dirs": [
                "<!@(node -p \"process.cwd()\")/deps/SDL2/include",
                "<!@(node -p \"process.cwd()\")/deps/SDL2_image/include",
                "<!@(node -p \"process.cwd()\")/deps/SDL2_mixer/include",
                "<!@(node -p \"process.cwd()\")/deps/SDL2_ttf/include",
                "<!@(node -p \"require('node-addon-api').include\")"
            ],
            "dependencies": [
                "<!(node -p \"require('node-addon-api').gyp\")"
            ],
            "libraries": [
                "-l<!(node -p \"process.cwd()\")/deps/SDL2/lib/x64/SDL2", 
                "-l<!(node -p \"process.cwd()\")/deps/SDL2/lib/x64/SDL2main", 
                "-l<!(node -p \"process.cwd()\")/deps/SDL2_image/lib/x64/SDL2_image", 
                "-l<!(node -p \"process.cwd()\")/deps/SDL2_ttf/lib/x64/SDL2_ttf", 
                "-l<!(node -p \"process.cwd()\")/deps/SDL2_mixer/lib/x64/SDL_mixer"
            ],
            "cflags!": [ "-fno-exceptions" ],
            "cflags_cc!": [ "-fno-exceptions" ],
            "xcode_settings": {
                "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                "CLANG_CXX_LIBRARY": "libc++",
                "MACOSX_DEPLOYMENT_TARGET": "10.7",
            },
            "msvs_settings": {
                "VCCLCompilerTool": { "ExceptionHandling": 1 },
            },
            "defines": [
                "NAPI_CPP_EXCEPTIONS"
            ]
        }
    ]
}
