mergeInto(LibraryManager.library, {
  emscripten_webnn_create_neural_network_context__deps: ['$WebNN'],
  emscripten_webnn_create_neural_network_context__postset: 'WebNN.initManagers();',
  emscripten_webnn_create_neural_network_context: function() {
    var context = navigator.ml.createNeuralNetworkContext();
    return WebNN["mgrNeuralNetworkContext"].create(context);
  },
});
