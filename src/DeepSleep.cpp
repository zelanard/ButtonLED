#include <Arduino.h>
#include "esp_sleep.h"
#include "DeepSleep.h"
#include "State.h"

RTC_DATA_ATTR int bootCount = 0;

void print_wakeup_reason()
{
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason)
  {
  case ESP_SLEEP_WAKEUP_EXT0:
    Serial.println("Wakeup caused by external signal using RTC_IO");
    break;

  case ESP_SLEEP_WAKEUP_EXT1:
    Serial.println("Wakeup caused by external signal using RTC_CNTL");
    break;

  case ESP_SLEEP_WAKEUP_TIMER:
    Serial.println("Wakeup caused by timer");
    break;

  case ESP_SLEEP_WAKEUP_TOUCHPAD:
    Serial.println("Wakeup caused by touchpad");
    break;

  case ESP_SLEEP_WAKEUP_ULP:
    Serial.println("Wakeup caused by ULP program");
    break;

  default:
    Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason);
    break;
  }
}

void InitDeepSleepTime()
{
  state = 2;
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  print_wakeup_reason();

  Serial.println("Going to sleep now");
  Serial.flush();
  esp_deep_sleep_start();
}

void DeepSleepButtonWakeUp(){
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  print_wakeup_reason();
}

void InitDeepSleep()
{
  state = 1;
  Serial.println("Sleep Button pressed");
  Serial.println("Going to sleep now");
  Serial.flush();
  esp_deep_sleep_start();
}