mergeInto(LibraryManager.library, {
  emscripten_webnn_create_context__deps: ['$WebNN'],
  emscripten_webnn_create_context__postset: 'WebNN.initManagers();',
  emscripten_webnn_create_context: function() {
    var context = navigator.ml.createContext();
    return WebNN.mgrContext.create(context);
  },
});
