/*++

Licensed under the Apache-2.0 license.

File Name:

    PinAssignments.h

Abstract:

    Input/output pin assignments for the UTV Holeshot Hero Maker.

    Current boards supported:   Arduino Nano Every

--*/

#ifndef PIN_ASSIGNMENTS_H
#define PIN_ASSIGNMENTS_H

// Each of these values corresponds to a pin on the Arduino Nano Every
enum PinAssignments : uint8_t {
    // Ignition Isolation (digital output)
    IgnitionIsolationPin    = 7,

    // Ignition (digital input)
    IgnitionPin             = 8,

    // LED indicating ready to sense ignition (digital output)
    ReadyLedPin             = 4,

    // LED indicating ignition delay has completed. GO!! (digital output)
    GoLedPin                = 6,

    // Delay control (analog input)
    DelayControlPin         = A1
};

#endif // PIN_ASSIGNMENTS_H
