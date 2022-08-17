/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <RNSkDrawView.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

#include <SkPicture.h>
#include <SkRefCnt.h>

#pragma clang diagnostic pop

#include "rns_shell/compositor/layers/Layer.h"

namespace RNSkia {

class RNSkDrawViewImpl : public RNSkia::RNSkDrawView {
 public:
  RNSkDrawViewImpl(std::shared_ptr <RNSkia::RNSkPlatformContext> context);

  void setSize(int width, int height);
  void sizeChanged(int width, int height);

  float getPixelDensity() {
    return getPlatformContext()->getPixelDensity();
  }
  void setLayer(RnsShell::Layer *layer){
    if(layer != layer_)
      layer_ = layer;
  }
  sk_sp <SkPicture> picture() { return picture_; }

 protected:
  float getScaledWidth() override { return width_ * context_->getPixelDensity(); };
  float getScaledHeight() override { return height_ * context_->getPixelDensity(); };

  void drawPicture(const sk_sp <SkPicture> picture) override;

 private:
  RnsShell::Layer *layer_ {nullptr};
  mutable sk_sp <SkPicture> picture_;
  void commit();

  float width_ = -1;
  float height_ = -1;

  std::shared_ptr<RNSkia::RNSkPlatformContext> context_;
};

} // namespace RNSkia
