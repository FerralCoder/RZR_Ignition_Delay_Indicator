/*++

Licensed under the Apache-2.0 license.

File Name:

    UTV_Holeshot_Hero_Maker.ino

Abstract:

    Main code for the UTV Holeshot Hero Maker.

    Current support:    Polaris RZR Pro XP (tested on 2022 model)

--*/

#include "PinAssignments.h"

// This specifies the minimum indicator delay in ms when the control dial is set at 0.
#define MIN_IGNITION_DELAY_MS       500

// This controls the range of delay that is possible. The full range in ms is:
// MIN_IGNITION_DELAY_MS to (MIN_IGNITION_DELAY_MS + (1023 * DELAY_CONTROL_MULTIPLIER))
#define DELAY_CONTROL_MULTIPLIER    3

// This is the delay in ms before we enter the ready state and begin the control loop.
// This delay is intended to ensure that the ignition pin from the car has reached stable state.
// Probably not absolutely necessary, but this provides extra insurance to avoid triggering early.
#define STABILIZATION_DELAY_MS      250


void setup()
{
    // Configure input/output pins

    // Out: Ignition isolation signal
    pinMode(IgnitionIsolationPin, OUTPUT);
    // Make sure to set this low at first to gate the incoming Ignition signal. Pin should already
    // be this way by default. This is needed so we don't have current leaking from IgnitionPin and
    // partially powering the uC. IgnitionPin drives 12v even when accessory power is off (and
    // therefore this device is off).
    digitalWrite(IgnitionIsolationPin, LOW);

    // IN: Ignition wire
    pinMode(IgnitionPin, INPUT);
    // OUT: Ready LED
    pinMode(ReadyLedPin, OUTPUT);
    // OUT: Go LED
    pinMode(GoLedPin, OUTPUT);
    // IN: ADC from potentiometer to adjust delay (A0)
    pinMode(DelayControlPin, INPUT);
    analogReference(VDD);

    // Insert delay to make sure the ignition signal from the car is stable
    delay(STABILIZATION_DELAY_MS);

    // Now that we are set up, ungate the IgnitionPin so we can sample it
    digitalWrite(IgnitionIsolationPin, HIGH);

    // Ready to sense ignition
    digitalWrite(ReadyLedPin, HIGH);
}

void loop()
{
    int  DelayControlVal    = 0;
    long IgnitionDelay_ms   = 0;

    if (digitalRead(IgnitionPin) == LOW)
    {
        // Read delay control value from potentiometer (ADC range 0 to 1023)
        DelayControlVal = analogRead(DelayControlPin);

        // Calculate delay
        IgnitionDelay_ms = MIN_IGNITION_DELAY_MS + (DelayControlVal * DELAY_CONTROL_MULTIPLIER);

        // Start delay
        delay(IgnitionDelay_ms);

        // Light it up!!
        digitalWrite(GoLedPin, HIGH);
        digitalWrite(ReadyLedPin, LOW);
    }
}
