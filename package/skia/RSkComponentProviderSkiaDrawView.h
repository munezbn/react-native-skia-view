/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "ReactSkia/components/RSkComponentProvider.h"
#include "ReactSkia/utils/RnsUtils.h"

namespace facebook {
namespace react {

class RSkComponentProviderSkiaDrawView : public RSkComponentProvider {
 public:
  RSkComponentProviderSkiaDrawView();

 public:
  ComponentDescriptorProvider GetDescriptorProvider() override;
  std::shared_ptr<RSkComponent> CreateComponent(
      const ShadowView &shadowView) override;
};

#ifdef __cplusplus
extern "C" {
#endif
RNS_USED RSkComponentProvider *RSkComponentProviderSkiaDrawViewCls() {
  return new RSkComponentProviderSkiaDrawView();
}

#ifdef __cplusplus
}
#endif

} // namespace react
} // namespace facebook
