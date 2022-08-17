/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "ReactSkia/utils/RnsLog.h"

#include "RNSkiaModule.h"

using namespace folly;

namespace facebook {
namespace xplat {

std::string RNSkiaModule::getName() {
  return "RNSkia";
}

auto RNSkiaModule::getConstants() -> std::map<std::string, folly::dynamic> {
  RNS_LOG_NOT_IMPL; // Refer SampleCxxModule.cpp
  return {};
}

// Module Methods
auto RNSkiaModule::getMethods() -> std::vector<Method> {
  return {
      Method(
          "install",
          [this] () -> bool {
            if (skiaManager_ != nullptr) { // Already initialized
              return true;
            }
            skiaManager_ = new SkiaManager(getInstance().lock());
            return true;
          },
          SyncTag),
  };
}

// Module Helpers
SkiaManager* RNSkiaModule::manager() {
  return skiaManager_;
}

void RNSkiaModule::invalidate() {
  if(skiaManager_) {
    skiaManager_->invalidate();
    delete skiaManager_;
    skiaManager_ = nullptr;
  }
}

std::unique_ptr<xplat::module::CxxModule> RNSkiaModule::createModule() {
  return std::make_unique<facebook::xplat::RNSkiaModule>();
}

} // namespace xplat
} // namespace facebook
