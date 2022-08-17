/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <iostream>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

#include <SkSurface.h>
#include <SkCanvas.h>
#include "include/core/SkPaint.h"

#pragma clang diagnostic pop

#include <RNSkLog.h>

#include "RNSkDrawViewImpl.h"

namespace RNSkia {

RNSkDrawViewImpl::RNSkDrawViewImpl(std::shared_ptr <RNSkia::RNSkPlatformContext> context)
    : RNSkia::RNSkDrawView(context),
      context_(context){}

void RNSkDrawViewImpl::setSize(int width, int height) {
  width_ = width;
  height_ = height;
  // Unlike other platform, We do not need seperate rendrer
  requestRedraw(); // Redraw
}

void RNSkDrawViewImpl::sizeChanged(int width, int height) {
  if(width == 0 && height == 0) { // We are doing cleanup
    return;
  }
  width_ = width;
  height_ = height;

  // Redraw after size change
  requestRedraw();
}

void RNSkDrawViewImpl::commit() {
  if(layer_ == nullptr) {
    RNS_LOG_WARN("View doesn't have valid layer yet");
    return;
  }
  // Invalidate the view and notify RNS-Shell compositor to refresh render tree.
  layer_->client().notifyFlushBegin();
  layer_->invalidate(RnsShell::LayerPaintInvalidate);
  layer_->client().notifyFlushRequired();
}

void RNSkDrawViewImpl::drawPicture(const sk_sp <SkPicture> picture) {
  if(width_ == -1 && height_ == -1) {
    RNS_LOG_WARN("Cannot draw picture when width and height is -1");
    return;
  }
  picture_ = picture;
  commit();
}

} // namespace RNSkia
