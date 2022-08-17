/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "include/core/SkPaint.h"
#include "cxxreact/ModuleRegistry.h"
#include "ReactSkia/LegacyNativeModules/LegacyNativeModuleRegistry.h"
#include "ReactSkia/ReactSkiaApp.h"
#include "RNSkiaModule.h"

#include "rns_shell/compositor/layers/PictureLayer.h"

#include "reactnativeskiaview/ReactNativeSkiaViewProps.h"

#include "RSkComponentSkiaDrawView.h"

namespace facebook {
namespace react {
using namespace xplat;

RSkComponentSkiaDrawView::RSkComponentSkiaDrawView(const ShadowView &shadowView)
    : RSkComponent(shadowView),
      nativeId_(0),
      debugMode_(false),
      drawingMode_(RNSkia::RNSkDrawingMode::Default) {
  auto skiaModule = ReactSkiaApp::currentBridge()->moduleForName(std::string("RNSkia"));

  RNS_LOG_TODO("Listen to notifications about module invalidation default notification center : RCTWillInvalidateModulesNotification");

  SkiaManager* skiaManager = reinterpret_cast<RNSkiaModule*>(skiaModule)->manager();
  manager_ = skiaManager->rnSkManager().get();
}

void RSkComponentSkiaDrawView::willInvalidateModules() {
  skiaDrawViewImpl_ = nullptr;
  manager_ = nullptr;
}


void RSkComponentSkiaDrawView::handleCommand(std::string commandName, folly::dynamic args){
  RNS_LOG_WARN("[RSkComponentSkiaDrawView][handleCommand] commandName : "<< commandName);
  RNS_LOG_NOT_IMPL;
  return;
}

void RSkComponentSkiaDrawView::setDrawingMode(std::string mode) {
  drawingMode_ = mode.compare("continuous") == 0 ? RNSkia::RNSkDrawingMode::Continuous : RNSkia::RNSkDrawingMode::Default;

  if(skiaDrawViewImpl_ != nullptr) {
    skiaDrawViewImpl_->setDrawingMode(drawingMode_);
  }
}

void RSkComponentSkiaDrawView::setDebugMode(bool debugMode) {
  debugMode_ = debugMode;
  if(skiaDrawViewImpl_ != nullptr) {
    skiaDrawViewImpl_->setShowDebugOverlays(debugMode);
  }
}

void RSkComponentSkiaDrawView::setNativeId(size_t nativeId) {
  nativeId_ = nativeId;
  if(skiaDrawViewImpl_ != nullptr && manager_ != nullptr)
    manager_->registerSkiaDrawView(nativeId_, skiaDrawViewImpl_);
}

RnsShell::LayerInvalidateMask  RSkComponentSkiaDrawView::updateComponentProps(const ShadowView &newShadowView,bool forceUpdate) {
  RnsShell::LayerInvalidateMask invalidateMask = RnsShell::LayerInvalidateNone;

  auto component = getComponentData();
  auto const &newSkDrawViewProps = *std::static_pointer_cast<ReactNativeSkiaViewProps const>(newShadowView.props);
  auto const &oldSkDrawViewProps = *std::static_pointer_cast<ReactNativeSkiaViewProps const>(getComponentData().props);

  RNS_LOG_INFO("========== DebugMode : " << newSkDrawViewProps.debug << " NativeId : " << newSkDrawViewProps.nativeId << " DrawingMode : " << newSkDrawViewProps.mode << " ==========" );

  if(nativeId_ != newSkDrawViewProps.nativeId)
    setNativeId(newSkDrawViewProps.nativeId);

  if(oldSkDrawViewProps.mode != newSkDrawViewProps.mode)
    setDrawingMode(newSkDrawViewProps.mode);

  if(debugMode_ != newSkDrawViewProps.debug)
    setDebugMode(newSkDrawViewProps.debug);

  if(skiaDrawViewImpl_ == nullptr && manager_ != nullptr) { // FIXME move this block to appropriate place
    skiaDrawViewImpl_ = std::make_shared<RNSkia::RNSkDrawViewImpl>(manager_->getPlatformContext());

    if(nativeId_ != 0) {
      manager_->setSkiaDrawView(nativeId_, skiaDrawViewImpl_);
    }
    skiaDrawViewImpl_->setDrawingMode(drawingMode_);
    skiaDrawViewImpl_->setShowDebugOverlays(debugMode_);
  }

  return invalidateMask;
}

void RSkComponentSkiaDrawView::OnPaint(SkCanvas *canvas) {
  static int count = 1;
  Rect frame = getComponentData().layoutMetrics.frame;
  skiaDrawViewImpl_->setSize(frame.size.width, frame.size.height);
  skiaDrawViewImpl_->setLayer(layer().get()); // TODO Do it only once. Cant do it in constructor as layer wont be available at that time.
  RNS_LOG_TODO(std::this_thread::get_id() << " " << count<<"] Layer " << layer().get() <<" Draw Picture Here with Frame  [" << frame.origin.x << "," << frame.origin.y << "," << frame.size.width << "," << frame.size.height << "]");
  if(skiaDrawViewImpl_->picture()) {
    RNS_LOG_INFO("SkPicture ( "  << skiaDrawViewImpl_->picture().get() << " )For " <<
              skiaDrawViewImpl_->picture()->approximateOpCount() << " operations and size : " << skiaDrawViewImpl_->picture()->approximateBytesUsed());
    skiaDrawViewImpl_->picture()->playback(canvas);
  } else {
    RNS_LOG_DEBUG("Picture object is not avaialable yet.");
  }
  count++;
}

} // namespace react
} // namespace facebook
