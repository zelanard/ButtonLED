#pragma once
#include <Arduino.h>
#include "esp_sleep.h"
#include "DeepSleep.h"

#define uS_TO_S_FACTOR 1000000ULL /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  5          /* Time ESP32 will go to sleep (in seconds) */
#define WAKEUP_GPIO              GPIO_NUM_34     // Only RTC IO are allowed - ESP34 Pin example

void print_wakeup_reason();
void InitDeepSleepTime(int);

void DeepSleepButtonWakeUp();
void InitDeepSleep();