/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "cxxreact/Instance.h"

#include "RNSkManager.h"
#include "PlatformContext.h"

using namespace std;
using namespace facebook;
using namespace facebook::react;

namespace RNSkia {

class SkiaManager {
 public :
  SkiaManager(shared_ptr<Instance> bridgeInstance);
  shared_ptr<RNSkManager> rnSkManager();
  void invalidate();

 private:
  shared_ptr<RNSkManager> rnSkManager_;
  shared_ptr<PlatformContext> platformContext_;
};

} // namespace RNSkia
