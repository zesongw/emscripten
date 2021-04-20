/*
 * Copyright 2021 The Emscripten Authors.  All rights reserved.
 * Emscripten is available under two separate licenses, the MIT license and the
 * University of Illinois/NCSA Open Source License.  Both these licenses can be
 * found in the LICENSE file.
 */

#pragma once

#include <webnn/webnn.h>

#ifdef __cplusplus
extern "C" {
#endif

WebnnNeuralNetworkContext emscripten_webnn_create_neural_network_context(void);

#ifdef __cplusplus
} // ~extern "C"
#endif