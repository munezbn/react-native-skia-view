/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <cxxreact/CxxModule.h>

#include "SkiaManager.h"

namespace facebook {
namespace xplat {

using namespace RNSkia;

class RNSkiaModule : public module::CxxModule {
 public:
  RNSkiaModule() {};
  static std::unique_ptr<xplat::module::CxxModule> createModule();

  // Module Implementation
  std::string getName();
  virtual auto getConstants() -> std::map<std::string, folly::dynamic>;
  virtual auto getMethods() -> std::vector<Method>;

  // Module Helpers
  SkiaManager* manager();
  void invalidate();

 private:
  SkiaManager* skiaManager_ { nullptr };
};

} // namespace xplat
} // namespace facebook
