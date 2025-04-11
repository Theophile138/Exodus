#include "ServoDS3240.h"
#include <Arduino.h>

ServoDS3240::ServoDS3240(int pwmPin, int pwmChannel)
  : pin(pwmPin), channel(pwmChannel) {}

void ServoDS3240::begin() {
    ledcSetup(channel, 50, 16);
    ledcAttachPin(pin, channel);
}

float ServoDS3240::angleToDutyCycle(float angle) {
    float dutyMin = 0.025 * 65535;
    float dutyMax = 0.125 * 65535;
    return dutyMin + (angle / 180.0f) * (dutyMax - dutyMin);
}

void ServoDS3240::setAngle(float angle) {
    float duty = angleToDutyCycle(angle);
    ledcWrite(channel, (uint32_t)duty);
}

void ServoDS3240::detach() {
    ledcDetachPin(pin);
}