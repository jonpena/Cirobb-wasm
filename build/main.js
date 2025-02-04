var Module = {
  canvas: document.getElementById("canvas"),
  onRuntimeInitialized: function () {
    console.log("WASM cargado y listo!");

    document.getElementById("pause").addEventListener("change", function () {
      Module._setPause(this.checked);
    });

    document.getElementById("options").addEventListener("change", function () {
      Module._setCorrectionType(this.value);
    });

    document.getElementById("canvas").addEventListener("click", function (e) {
      if (!("ontouchstart" in window || navigator.maxTouchPoints > 0)) {
        // Solo ejecuta este funcion si no es un dispositivo táctil
        Module._setTouchDevice(true);
      }
    });
  },
};
