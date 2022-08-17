/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "RSkComponentProviderSkiaDrawView.h"
#include "RSkComponentSkiaDrawView.h"

#include "reactnativeskiaview/ReactNativeSkiaViewComponentDescriptor.h"

namespace facebook {
namespace react {

RSkComponentProviderSkiaDrawView::RSkComponentProviderSkiaDrawView() {}

ComponentDescriptorProvider RSkComponentProviderSkiaDrawView::GetDescriptorProvider() {
  return concreteComponentDescriptorProvider<ReactNativeSkiaViewComponentDescriptor>();
}

std::shared_ptr<RSkComponent> RSkComponentProviderSkiaDrawView::CreateComponent(
    const ShadowView &shadowView) {
  return std::static_pointer_cast<RSkComponent>(
      std::make_shared<RSkComponentSkiaDrawView>(shadowView));
}

} // namespace react
} // namespace facebook
