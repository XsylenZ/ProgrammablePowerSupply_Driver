#ifndef COMMAND_GENERAL_H
#define COMMAND_GENERAL_H

// General list of commands supported by the Korad power supplies

#define CMD_LOCK           "LOCK"    // Lock front panel 0 = unlock, 1 = lock
#define CMD_ISET           "ISET"    // Current set
#define CMD_VSET           "VSET"    // Voltage set
#define CMD_VOUT           "VOUT"    // Output voltage
#define CMD_OUTPUT         "OUT"       // Turn 1 = on, 0 = off output
#define CMD_BEEP           "BEEP"      // Turns 1 = on, 0 = off the beep
#define CMD_STATUS         "STATUS"   // Contents 8 bits in the following format
                                            // Bit Item Description
                                            // 0 CH1 0=CC mode, 1=CV mode
                                            // 1 CH2 0=CC mode, 1=CV mode
                                            // 2,3,4,5 N/A
                                            // 6 Output 0=Off, 1=On
                                            // 7 N/A


#define CMD_IDN            "*IDN"      // Contents KORAD KD3005P V2.0 (Manufacturer, model name,)
#define CMD_RCL            "RCL"       // Recall saved panel setting from memory nr 1 - 5
#define CMD_SAV            "SAV"       // Save panel setting to memory nr 1 - 5
#define CMD_TRACK          "TRACK"     // Mode 0 = INDEP, 1 = SER, 2 = PARA
#define CMD_OCP            "OCP"       // Turn 1 = on, 0 = off the OCP
#define CMD_OCPSTE         "OCPSTE"    // Set current protection
#define CMD_OVP            "OVP"       // Turn 1 = on, 0 = off the OVP
#define CMD_OVPSTE         "OVPSTE"    // Set voltage protection

#endif // COMMAND_GENERAL_H
