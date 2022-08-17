/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <functional>
#include <memory>
#include <string>

#include <folly/dynamic.h>

#include <RNSkPlatformContext.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

#include <SkStream.h>

#pragma clang diagnostic pop

#include "SkTypes.h"
#include <jsi/jsi.h>

#include "ReactSkia/utils/RnsLog.h"
#include "ReactSkia/sdk/NotificationCenter.h"

namespace facebook {
  namespace react {
    class CallInvoker;
  }
}

namespace RNSkia {

using namespace facebook;
using namespace std;
using namespace folly;

class PlatformContext : public RNSkPlatformContext {
 public:
  PlatformContext(jsi::Runtime *runtime, std::shared_ptr<react::CallInvoker> callInvoker)
      : RNSkPlatformContext(runtime, callInvoker, 1.0 /*FIXME*/) {
        std::function<void(std::string&, folly::dynamic&)> contextNotificationHandler = std::bind(&PlatformContext::handleNotification, this,
                                                                      std::placeholders::_1,  // std::string
                                                                      std::placeholders::_2);  // folly::dynamic
        notificationEventId_ = NotificationCenter::defaultCenter().addListener("RCTWillInvalidateModulesNotification", contextNotificationHandler);
  }

  ~PlatformContext() {
    NotificationCenter::defaultCenter().removeListener(notificationEventId_);
  }

  void startDrawLoop() override;
  void stopDrawLoop() override;

  virtual void performStreamOperation(
      const std::string &sourceUri,
      const std::function<void(std::unique_ptr<SkStreamAsset>)> &op) override;

  void raiseError(const std::exception &err) override;

  void willInvalidateModules() {
    // We need to do some house-cleaning here
    RNS_LOG_NOT_IMPL;
    invalidate();
  }

 private:
  // FIXME need displaylink ??;
  void handleNotification(string& name, dynamic& param) {
    willInvalidateModules();
  }
  bool drawLoopActive_ {false};
  unsigned int notificationEventId_ = UINT_MAX; // Some undefined ID
};

} // namespace RNSkia
