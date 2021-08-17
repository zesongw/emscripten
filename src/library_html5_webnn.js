mergeInto(LibraryManager.library, {
  emscripten_webnn_create_context__deps: ['$WebNN'],
  emscripten_webnn_create_context__postset: 'WebNN.initManagers();',
  emscripten_webnn_create_context: function(optionsPtr) {
    var options = {
      "devicePreference": "default",
      "powerPreference": "default"
    };

    var DevicePreference = [
      'default',
      'gpu',
      'cpu',
    ];
    var PowerPreference = [
      'default',
      'high_performance',
      'low_power',
    ];
    if (optionsPtr !== 0) {
      options = {
          "devicePreference": DevicePreference[
            {{{ makeGetValue('optionsPtr', C_STRUCTS.MLContextOptions.devicePreference, 'i32', false, true) }}}],
          "powerPreference": DevicePreference[
            {{{ makeGetValue('optionsPtr', C_STRUCTS.MLContextOptions.powerPreference, 'i32', false, true) }}}]
      };
    }
    var context = navigator.ml.createContext(options);
    return WebNN.mgrContext.create(context);
  },
});
