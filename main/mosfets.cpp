#include "mosfets.h"

// Arduino includes
#include <Arduino.h>

#ifdef FEATURE_MOSFETS
void init_mosfets()
{
    pinMode(PINS_MOSFET0, OUTPUT);
    pinMode(PINS_MOSFET1, OUTPUT);
    pinMode(PINS_MOSFET2, OUTPUT);

    digitalWrite(PINS_MOSFET0, LOW);
    digitalWrite(PINS_MOSFET1, LOW);
    digitalWrite(PINS_MOSFET2, LOW);
}

void update_mosfets()
{

}
#endif
