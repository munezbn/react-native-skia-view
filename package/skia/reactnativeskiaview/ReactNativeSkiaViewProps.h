/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <react/renderer/components/view/ViewProps.h>

namespace facebook {
namespace react {

// TODO (T28334063): Consider for codegen.
class ReactNativeSkiaViewProps final : public ViewProps {
 public:
  ReactNativeSkiaViewProps() = default;
  ReactNativeSkiaViewProps(const ReactNativeSkiaViewProps &sourceProps, const RawProps &rawProps);

#pragma mark - Props
  const bool debug{};
  const int nativeId{};
  const std::string mode{};
};

} // namespace react
} // namespace facebook
