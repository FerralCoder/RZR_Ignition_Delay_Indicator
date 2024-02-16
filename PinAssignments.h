#ifndef PIN_ASSIGNMENTS_H
#define PIN_ASSIGNMENTS_H

// Each of these values corresponds to a pin on the Arduino Nano Every
enum PinAssignments : uint8_t {
    // Ignition (digital input)
    IgnitionPin     = 8,

    // LED indicating ready to sense ignition (digital out)
    ReadyLedPin     = 4,

    // LED indicating ignition delay has completed. GO!! (digital out)
    GoLedPin        = 6,

    // Delay control (analog in)
    DelayControlPin = A1
};

#endif // PIN_ASSIGNMENTS_H