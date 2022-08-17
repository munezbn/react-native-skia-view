/*
 * Copyright (C) 1994-2022 OpenTV, Inc. and Nagravision S.A.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <react/renderer/core/propsConversions.h>

#include "ReactNativeSkiaViewProps.h"

namespace facebook {
namespace react {

ReactNativeSkiaViewProps::ReactNativeSkiaViewProps(const ReactNativeSkiaViewProps &sourceProps, const RawProps &rawProps)
    : ViewProps(sourceProps, rawProps),
        debug(convertRawProp(
            rawProps,
            "debug",
            sourceProps.debug,
            {})),
        nativeId(convertRawProp(
            rawProps,
            "nativeID",
            sourceProps.nativeId,
            {})),
        mode(convertRawProp(
            rawProps,
            "mode",
            sourceProps.mode,
            {})) {}

} // namespace react
} // namespace facebook
