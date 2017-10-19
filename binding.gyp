{
    "targets": [
        {
            "target_name": "SDLnode",
            "sources": [ 
                "src/SDLnode.cc" ,
                "src/sdl.cc",
                "src/window.cc",
                "src/renderer.cc",
                "src/texture.cc",
                "src/surface.cc"
            ],
            "include_dirs": [
                "/usr/include/SDL2",
                "<!@(node -p \"require('node-addon-api').include\")"
            ],
            "dependencies": [
                "<!(node -p \"require('node-addon-api').gyp\")"
            ],
            "libraries": [
                "-lSDL2", "-lSDL2main", "-lSDL2_image", "-lSDL2_ttf"
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