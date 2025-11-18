#include "LifeTime.h"
#include "State.h"
#include <Arduino.h>

void LifeTime()
{
    button.tick();
    if(state == 3)
    {
        Blink();
    }
}