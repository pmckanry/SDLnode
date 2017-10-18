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
            ]
        }
    ]
}