
//===- Utils.h - SYCL MLIR Dialect Utilities ---------------------------*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains utilities for the Polygeist transformation passes.
//
//===----------------------------------------------------------------------===//

#ifndef MLIR_DIALECT_SYCL_UTILS_H
#define MLIR_DIALECT_SYCL_UTILS_H

#include "mlir/Dialect/SYCL/IR/SYCLTypes.h"

namespace mlir {
namespace sycl {

/// Return the accessor used by \p op if found, and nullptr otherwise.
Optional<AccessorPtrType> getAccessorUsedByOperation(const Operation &op);

} // namespace sycl
} // namespace mlir

#endif // MLIR_DIALECT_SYCL_UTILS_H
