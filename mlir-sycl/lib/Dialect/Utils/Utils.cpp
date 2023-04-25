//===- Utils.cpp ---- Utilities for the SYCL dialect  ---------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements miscellaneous utilities for the SYCL dialect.
//
//===----------------------------------------------------------------------===//

#include "mlir/Dialect/SYCL/Utils.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SYCL/IR/SYCLOps.h"
#include "llvm/ADT/TypeSwitch.h"
#include <optional>

#define DEBUG_TYPE "sycl-utils"

namespace mlir {
namespace sycl {

Optional<AccessorPtrType> getAccessorUsedByOperation(const Operation &op) {
  auto getMemrefOp = [](const Operation &op) {
    return TypeSwitch<const Operation &, Operation *>(op)
        .Case<AffineLoadOp, AffineStoreOp>(
            [](auto &affineOp) { return affineOp.getMemref().getDefiningOp(); })
        .Default([](auto &) { return nullptr; });
  };

  if (auto accSub =
          dyn_cast_or_null<sycl::SYCLAccessorSubscriptOp>(getMemrefOp(op)))
    return accSub.getAcc();

  return std::nullopt;
}

} // namespace sycl
} // namespace mlir
