mergeInto(LibraryManager.library, {
  emscripten_webnn_create_context__deps: ['$WebNN'],
  emscripten_webnn_create_context__postset: 'WebNN.initManagers();',
  emscripten_webnn_create_context: function(optionsPtr) {
    var options = {
      'devicePreference': 'default',
      'powerPreference': 'default'
    };

    var DevicePreference = [
      'default',
      'gpu',
      'cpu',
    ];
    var PowerPreference = [
      'default',
      'high-performance',
      'low-power',
    ];
    if (optionsPtr !== 0) {
      options = {
          'devicePreference': DevicePreference[
            {{{ makeGetValue('optionsPtr', C_STRUCTS.WNNContextOptions.devicePreference, 'i32', false, true) }}}],
          'powerPreference': PowerPreference[
            {{{ makeGetValue('optionsPtr', C_STRUCTS.WNNContextOptions.powerPreference, 'i32', false, true) }}}]
      };
    }
    var context = navigator['ml'].createContextSync(options);
    return WebNN.mgrContext.create(context);
  },
});
