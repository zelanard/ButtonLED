#pragma once
#include <Arduino.h>
#include <OneButton.h>

const uint8_t BUILT_IN_LED = 2;
const uint8_t LED_BLUE = 21;
const uint8_t BUTTON = 32;
const uint8_t LED_RED = 5;

extern RTC_DATA_ATTR int state;
extern unsigned long lastBlinkTime;
extern bool blinkState;

// Declare the OneButton instance (defined in State.cpp)
extern OneButton button;

// Functions
void SwitchState();
void StateCount();
void Blink();
void RED();
void BLUE();
void BOTH(bool);

// Callback for OneButton
void onButtonClick();