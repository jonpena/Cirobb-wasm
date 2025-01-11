mkdir -p ./dist

if [ "$1" = "dev" ]; then
    # Development build
    emcc ./src/main.cpp \
        -o ./dist/index.js \
        -s USE_WEBGL2=1 \
        -s USE_GLFW=3 \
        -s WASM=1 \
        -std=c++11 \
        -s LEGACY_GL_EMULATION \
        --shell-file ./index.html
    # -s EXPORTED_FUNCTIONS='_main','_sumar'
else
    # Production build
    emcc ./src/main.cpp \
        -o ./dist/index.js \
        -s USE_WEBGL2=1 \
        -s USE_GLFW=3 \
        -s WASM=1 \
        -O3 \
        -std=c++11 \
        -s LEGACY_GL_EMULATION \
        --shell-file ./index.html
fi

# Copiar index.html a la carpeta dist
cp ./index.html ./dist/
cp ./style.css ./dist/

echo "✅ WASM application build completed!"


