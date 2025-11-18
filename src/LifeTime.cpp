#include "LifeTime.h"
#include "State.h"
#include <Arduino.h>

void LifeTime()
{
    button.tick();
    on_button.tick();
    
    if(state == 3)
    {
        Blink();
    }
}