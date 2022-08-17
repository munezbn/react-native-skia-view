/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <RNSkManager.h>

#include "RNSkDrawView.h"
#include "RNSkDrawViewImpl.h"
#include "ReactSkia/components/RSkComponent.h"
#include "ReactSkia/utils/RnsUtils.h"



namespace facebook {
namespace react {

using namespace std;

class RSkComponentSkiaDrawView final : public RSkComponent {
 public:
  RSkComponentSkiaDrawView(const ShadowView &shadowView);
  ~RSkComponentSkiaDrawView() = default;
  RnsShell::LayerInvalidateMask updateComponentProps(const ShadowView &newShadowView,bool forceUpdate) override;
  void handleCommand(std::string commandName, folly::dynamic args) override;

  void setDrawingMode(std::string mode);
  void setDebugMode(bool debugMode);
  void setNativeId(size_t nativeId);

 protected:
  void OnPaint(SkCanvas *canvas) override;

 private:
  size_t nativeId_;
  bool debugMode_;
  RNSkia::RNSkDrawingMode drawingMode_;

  RNSkia::RNSkManager* manager_{nullptr};
  shared_ptr<RNSkia::RNSkDrawViewImpl> skiaDrawViewImpl_;

  void willInvalidateModules();
};

} // namespace react
} // namespace facebook
