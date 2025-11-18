#include "Setup.h"
#include "State.h"
#include <Arduino.h>

void Init()
{
    pinMode(LED_BLUE, OUTPUT);
    pinMode(BUILT_IN_LED, OUTPUT);
    pinMode(BUTTON, INPUT_PULLUP);
    pinMode(LED_RED, OUTPUT);

    button.attachClick(onButtonClick);
    Serial.begin(115200);
    delay(1000); // Wait for Serial to initialize
    Serial.println("Initialization complete.");
    SwitchState();
}