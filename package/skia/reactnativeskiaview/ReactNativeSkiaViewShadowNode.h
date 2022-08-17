/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "react/renderer/components/view/ConcreteViewShadowNode.h"

#include "reactnativeskiaview/ReactNativeSkiaViewProps.h"
#include "reactnativeskiaview/ReactNativeSkiaViewState.h"

namespace facebook {
namespace react {

extern const char ReactNativeSkiaViewComponentName[];

/*
 * `ShadowNode` for <ReactNativeSkiaView> component.
 */
class ReactNativeSkiaViewShadowNode final : public ConcreteViewShadowNode<
                                    ReactNativeSkiaViewComponentName,
                                    ReactNativeSkiaViewProps,
                                    ViewEventEmitter,
                                    ReactNativeSkiaViewState> {

 public:
  using ConcreteViewShadowNode::ConcreteViewShadowNode;

  static ShadowNodeTraits BaseTraits() {
    auto traits = ConcreteViewShadowNode::BaseTraits();
    traits.set(ShadowNodeTraits::Trait::LeafYogaNode);
    return traits;
  }

  static ReactNativeSkiaViewState initialStateData(
      ShadowNodeFragment const &fragment,
      ShadowNodeFamilyFragment const &familyFragment,
      ComponentDescriptor const &componentDescriptor) {
    return {};
  }

#pragma mark - LayoutableShadowNode

  void layout(LayoutContext layoutContext) override;

 private:
  void updateStateIfNeeded();
};

} // namespace react
} // namespace facebook
