/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "SkiaManager.h"

namespace RNSkia {

SkiaManager::SkiaManager(shared_ptr<Instance> bridgeInstance) {
  shared_ptr<CallInvoker> callInvoker = bridgeInstance->getJSCallInvoker();
  jsi::Runtime *jsRuntime = reinterpret_cast<jsi::Runtime*>(bridgeInstance->getJavaScriptContext());

  // Create platform context
  platformContext_ = make_shared<PlatformContext>(jsRuntime, callInvoker);

  // Create RNSkManager
  rnSkManager_ = make_shared<RNSkManager>(jsRuntime, callInvoker, platformContext_);
}

shared_ptr<RNSkManager> SkiaManager::rnSkManager() {
  return rnSkManager_;
}

void SkiaManager::invalidate() {
  if(rnSkManager_ != nullptr) {
    rnSkManager_->invalidate();
  }
  rnSkManager_ = nullptr;
  platformContext_ = nullptr;
}

} // namespace RNSkia
