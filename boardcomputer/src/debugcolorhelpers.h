#pragma once

#include "colorinterface.h"
#include "globals.h"

namespace {
template<Controller &controller>
class FeedbackColor : public virtual ColorInterface { public: int color() const { return controller.feedbackValid ? TFT_DARKGREY : TFT_RED; } };

using FrontFeedbackColor = FeedbackColor<front>;
using BackFeedbackColor = FeedbackColor<back>;
}
