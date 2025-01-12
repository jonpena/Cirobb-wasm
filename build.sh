mkdir -p ./build

if [ "$1" = "dev" ]; then
    # Development build
    emcc ./src/main.cpp \
        -o ./build/index.js \
        -s USE_WEBGL2=1 \
        -s USE_GLFW=3 \
        -s WASM=1 \
        -std=c++11 \
        -s LEGACY_GL_EMULATION \
        -s EXPORTED_FUNCTIONS='["_main", "_setPause", "_setCorrectionType"]'
else
    # Production build
    emcc ./src/main.cpp \
        -o ./build/index.js \
        -s USE_WEBGL2=1 \
        -s USE_GLFW=3 \
        -s WASM=1 \
        -O3 \
        -std=c++11 \
        -s LEGACY_GL_EMULATION \
        # --shell-file ./index.html
fi

echo "✅ WASM application build successfully!"


