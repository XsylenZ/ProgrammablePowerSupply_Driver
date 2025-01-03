#ifndef COMMAND_KA3000V2_H
#define COMMAND_KA3000V2_H

// List of commands supported by the Korad KA3000 series
// KA3000 Series Remote Control Syntax V2.0

// LOCK the front panel
#define KA3000V2_LOCK            "LOCK"      // Lock front panel 0 = unlock, 1 = lock

// Set Current Commands
#define KA3000V2_ISET1           "ISET1:"    // Set current for channel 1
#define KA3000V2_ISET2           "ISET2:"    // Set current for channel 2

// Query Current Commands (getter commands)
#define KA3000V2_ISET1_QUERY     "ISET1?"    // Query set current for channel 1
#define KA3000V2_ISET2_QUERY     "ISET2?"    // Query set current for channel 2
#define KA3000V2_IOUT1_QUERY     "IOUT1?"    // Query output current for channel 1
#define KA3000V2_IOUT2_QUERY     "IOUT2?"    // Query output current for channel 2

// Set Voltage Commands
#define KA3000V2_VSET1           "VSET1:"    // Set voltage for channel 1
#define KA3000V2_VSET2           "VSET2:"    // Set voltage for channel 2

// Query Voltage Commands (getter commands)
#define KA3000V2_VSET1_QUERY     "VSET1?"    // Query set voltage for channel 1
#define KA3000V2_VSET2_QUERY     "VSET2?"    // Query set voltage for channel 2
#define KA3000V2_VOUT1_QUERY     "VOUT1?"    // Query output voltage for channel 1
#define KA3000V2_VOUT2_QUERY     "VOUT2?"    // Query output voltage for channel 2

// Enable Output Commands
#define KA3000V2_OUTPUT          "OUT"       // Turn 1 = on, 0 = off output

// Query Output Status Commands
//TODO: check if this command works, according to the manual this one does not exsist
#define KA3000V2_OUTPUT_QUERY    "OUT?"      // Query output status (ON/OFF)

// Turns on or off the beep
#define KA3000V2_BEEP            "BEEP"      // Turns 1 = on, 0 = off the beep

// Returns the power supply status
#define KA3000V2_STATUS_QUERY    "STATUS?"   // Contents 8 bits in the following format
                                            // Bit Item Description
                                            // 0 CH1 0=CC mode, 1=CV mode
                                            // 1 CH2 0=CC mode, 1=CV mode
                                            // 2,3,4,5 N/A
                                            // 6 Output 0=Off, 1=On
                                            // 7 N/A

// Returns the KA3005P identification
#define KA3000V2_IDN_QUERY       "*IDN?"      // Contents KORAD KD3005P V2.0 (Manufacturer, model name,)

// Recalls a panel setting
#define KA3000V2_RCL             "RCL"       // Recall saved panel setting from memory nr 1 - 5

// Stores the panel setting
#define KA3000V2_SAV             "SAV"       // Save panel setting to memory nr 1 - 5

// Sets the output of the power supply working on indepent or tracking
#define KA3000V2_TRACK           "TRACK"     // Mode 0 = INDEP, 1 = SER, 2 = PARA

// Turns on or off the OCP
#define KA3000V2_OCP             "OCP"       // Turn 1 = on, 0 = off the OCP

// Sets the value of current protection
#define KA3000V2_OCPSTE1         "OCPSTE1:"  // Set current protection for channel 1
#define KA3000V2_OCPSTE2         "OCPSTE2:"  // Set current protection for channel 2

// Turns on or off the OVP
#define KA3000V2_OVP             "OVP"       // Turn 1 = on, 0 = off the OVP

// Sets the value of voltage protection
#define KA3000V2_OVPSTE1         "OVPSTE1:"  // Set voltage protection for channel 1
#define KA3000V2_OVPSTE2         "OVPSTE2:"  // Set voltage protection for channel 2

#endif // COMMAND_KA3000V2_H
