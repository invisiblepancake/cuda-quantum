/*******************************************************************************
 * Copyright (c) 2022 - 2025 NVIDIA Corporation & Affiliates.                  *
 * All rights reserved.                                                        *
 *                                                                             *
 * This source code and the accompanying materials are made available under    *
 * the terms of the Apache License 2.0 which accompanies this distribution.    *
 ******************************************************************************/

// RUN: cudaq-quake %cpp_std --no-simplify %s | cudaq-opt --add-dealloc | FileCheck %s

#include <cudaq.h>

__qpu__ void magic_func(int N) {
  {
    cudaq::qvector q(N);
    h(q[0]);
  }
  cudaq::qvector w(N);
  x(w[0]);
}

// CHECK-LABEL:   func.func @__nvqpp__mlirgen__function_magic_func.
// CHECK-SAME:       %[[VAL_0:.*]]: i32) attributes
// CHECK:           cc.scope {
// CHECK:             %[[VAL_4:.*]] = quake.alloca !quake.veq<?>[%{{.*}} : i64]
// CHECK:             quake.dealloc %[[VAL_4]] : !quake.veq<?>
// CHECK:             cc.continue
// CHECK:           }
// CHECK:           %[[VAL_12:.*]] = quake.alloca !quake.veq<?>[%{{.*}} : i64]
// CHECK:           quake.dealloc %[[VAL_12]] : !quake.veq<?>
// CHECK:           return

