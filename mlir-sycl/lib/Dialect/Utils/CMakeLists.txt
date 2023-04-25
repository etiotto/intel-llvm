add_mlir_dialect_library(MLIRSYCLUtils
  Utils.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Dialect/SYCL

  LINK_LIBS PUBLIC
  MLIRSYCLDialect
  )
