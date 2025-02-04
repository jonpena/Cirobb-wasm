mkdir -p ./build

# Base compilation flags
EMCC_FLAGS="-s USE_WEBGL2=1 \
    -s USE_GLFW=3 \
    -s WASM=1 \
    -std=c++11 \
    -s LEGACY_GL_EMULATION \
    -s EXPORTED_FUNCTIONS='[\"_main\", \"_setPause\", \"_setCorrectionType\", \"_setTouchDevice\"]' \
    -s EXPORTED_RUNTIME_METHODS='[\"ccall\", \"cwrap\"]'"

# Add optimization flag for production
if [ "$1" != "dev" ]; then
    EMCC_FLAGS="$EMCC_FLAGS -O3"
fi

# Execute compilation
eval "emcc ./src/main.cpp -o ./build/index.js $EMCC_FLAGS"

echo "✅ WASM application build successfully!"


