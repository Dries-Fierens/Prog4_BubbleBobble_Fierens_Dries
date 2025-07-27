#include "Locator.h"

NullAudio Locator::nullService_{};
Audio* Locator::service_{ &Locator::nullService_ };