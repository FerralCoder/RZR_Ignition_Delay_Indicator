#include "PinAssignments.h"

#define DELAY_CONTROL_MULTIPLIER    2
#define MIN_IGNITION_DELAY_MS       1000
#define STABILIZATOIN_DELAY_MS      500

void setup()
{
    // IN: Ignition wire
    pinMode(IgnitionPin, INPUT);
    // OUT: Ready LED
    pinMode(ReadyLedPin, OUTPUT);
    // OUT: Go LED
    pinMode(GoLedPin, OUTPUT);
    // IN: ADC from potentiometer to adjust delay (A0)
    pinMode(DelayControlPin, INPUT);
    analogReference(VDD);

    // Insert artificial delay to make sure all signals from the car are stable
    delay(STABILIZATOIN_DELAY_MS);

    // Ready to sense ignition
    digitalWrite(ReadyLedPin, HIGH);
}

void loop()
{
    int  DelayControlVal    = 0;
    long IgnitionDelay_ms   = 0;

    // Read delay control value from potentiometer (range 0 to 1023)
    DelayControlVal = analogRead(DelayControlPin);

    // Calculate delay
    IgnitionDelay_ms = MIN_IGNITION_DELAY_MS + (DelayControlVal * DELAY_CONTROL_MULTIPLIER);

    if (digitalRead(IgnitionPin) == HIGH)
    {
        // Start delay
        delay(IgnitionDelay_ms);

        // Light it up!!
        digitalWrite(GoLedPin, HIGH);
        digitalWrite(ReadyLedPin, LOW);
    }
}
