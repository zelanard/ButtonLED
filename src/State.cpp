#include "State.h"
#include "DeepSleep.h"

RTC_DATA_ATTR int state = 0;
unsigned long lastBlinkTime = 0;
bool blinkState = false;

// parameters: (pin, activeLow, pullupActive)
OneButton button(BUTTON, false, true);
OneButton on_button(ON_BUTTON, false, true);

void onOnButtonClick()
{
    InitDeepSleep();
}

void onButtonClick()
{
    StateCount();
    SwitchState();
}

void SwitchState()
{
    switch (state)
    {
    case 1: // Wake Up On Time
        Serial.println("State 1: RED ON, BLUE OFF");
        digitalWrite(LED_BUILTIN, LOW);
        RED();
        break;

    case 2: // Wake Up On Button
        Serial.println("State 2: RED OFF, BLUE ON");
        BLUE();
        digitalWrite(LED_BUILTIN, LOW);
        break;

    case 3: // Blinking
        Serial.println("State 3: BLINKING");
        // see LifeTime()
        digitalWrite(LED_BUILTIN, LOW);
        break;

    case 4: // Both On
        Serial.println("State 4: BOTH ON");
        BOTH(true);
        digitalWrite(LED_BUILTIN, LOW);
        break;

    case 5: // Go To Sleep Timed
        Serial.println("State 5: BOTH OFF");
        digitalWrite(LED_BUILTIN, LOW);
        InitDeepSleepTime(5); // Sleep for 5 seconds
        break;

    default: // Default
        Serial.println("State 0: Default");
        BOTH(false);
        digitalWrite(LED_BUILTIN, HIGH);
        break;
    }
}

void RED()
{
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_RED, HIGH);
}

void BLUE()
{
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_RED, LOW);
}

void BOTH(bool on)
{
    if (on)
    {
        digitalWrite(LED_BLUE, HIGH);
        digitalWrite(LED_RED, HIGH);
    }
    else
    {
        digitalWrite(LED_BLUE, LOW);
        digitalWrite(LED_RED, LOW);
    }
}

void StateCount()
{
    switch (state)
    {
    case 0:
        state = 3;
        break;
    case 3:
        state = 4;
        break;
    case 4:
        state = 5;
        break;
    
    default:
        state = 0;
        break;
    }
}

void Blink()
{
    unsigned long now = millis();

    if (now - lastBlinkTime >= 500)
    {
        lastBlinkTime = now;

        blinkState = !blinkState;

        if (blinkState)
        {
            RED();
        }
        else
        {
            BLUE();
        }
    }
}