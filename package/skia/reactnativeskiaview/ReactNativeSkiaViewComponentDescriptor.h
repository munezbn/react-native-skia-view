/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "react/renderer/core/ConcreteComponentDescriptor.h"
#include "ReactNativeSkiaViewShadowNode.h"

namespace facebook {
namespace react {

class ReactNativeSkiaViewComponentDescriptor
    : public ConcreteComponentDescriptor<ReactNativeSkiaViewShadowNode> {
 public:
  ReactNativeSkiaViewComponentDescriptor(ComponentDescriptorParameters const &parameters)
      : ConcreteComponentDescriptor<ReactNativeSkiaViewShadowNode>(parameters) {}
};

} // namespace react
} // namespace facebook
