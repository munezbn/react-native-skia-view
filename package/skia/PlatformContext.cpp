/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <thread>
#include <utility>

#include <RNSkMeasureTime.h>
#include "PlatformContext.h"

namespace RNSkia {

void PlatformContext::performStreamOperation(const std::string &sourceUri,
                                            const std::function<void(std::unique_ptr<SkStreamAsset>)> &op) {
  RNS_LOG_NOT_IMPL;
  RNSkMeasureTime("PlatformContext::performStreamOperation");
  auto loader = [=]() {
    RNS_LOG_TODO("Creare a stream request for " << sourceUri << ", and perform requested operation on data of recived length");
    auto bytes = nullptr;
    auto dataLength = 0;
    auto skData = SkData::MakeWithCopy(bytes, dataLength);
    auto stream = SkMemoryStream::Make(skData);

    op(std::move(stream));
  };

  // Fire and forget the thread - will be resolved on completion
  std::thread(loader).detach();
}

void PlatformContext::raiseError(const std::exception &err) {
  std::string errorString = err.what();
  RNS_LOG_ERROR("Platform Context Error : " << errorString);
}

void PlatformContext::startDrawLoop() {
  RNS_LOG_NOT_IMPL; // Something like displayLink ?
  if (drawLoopActive_) {
    return;
  }
  drawLoopActive_ = true;
  notifyDrawLoop(false);
}

void PlatformContext::stopDrawLoop() {
  RNS_LOG_NOT_IMPL; // Something like displayLink ?
  if (drawLoopActive_) {
    drawLoopActive_ = false;
  }
}

} // namespace RNSkia

