#include "Setup.h"
#include "State.h"
#include <Arduino.h>
#include "DeepSleep.h"
#include "driver/rtc_io.h"

void Init()
{
    pinMode(LED_BLUE, OUTPUT);
    pinMode(BUILT_IN_LED, OUTPUT);
    pinMode(BUTTON, INPUT_PULLUP);
    pinMode(LED_RED, OUTPUT);
    pinMode(ON_BUTTON, INPUT_PULLUP);

    esp_sleep_enable_ext0_wakeup(WAKEUP_GPIO, 1);
    rtc_gpio_pullup_dis(WAKEUP_GPIO);
    rtc_gpio_pulldown_en(WAKEUP_GPIO);

    button.attachClick(onButtonClick);
    on_button.attachClick(onOnButtonClick);

    Serial.begin(115200);
    delay(1000); // Wait for Serial to initialize
    Serial.println("Initialization complete.");
    if(state == 2){
        DeepSleepButtonWakeUp();
    }
    SwitchState();
}