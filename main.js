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
  },
};
