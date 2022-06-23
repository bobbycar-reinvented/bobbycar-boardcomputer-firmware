#pragma once

namespace soft_pwm_limiter {

extern bool trigger;

void update();

float limit(float pwm);

} // namespace soft_pwm_limiter
