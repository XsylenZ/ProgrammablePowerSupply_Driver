#ifndef COMMAND_KD3305P_H
#define COMMAND_KD3305P_H

// List of commands supported by the Korad KD3305P

// Set Voltage Commands
#define CMD_VSET1       "VSET1:"     // Set voltage for channel 1
#define CMD_VSET2       "VSET2:"     // Set voltage for channel 2

// Query Voltage Commands (getter commands)
#define CMD_VSET1_QUERY "VSET1?"     // Query set voltage for channel 1
#define CMD_VSET2_QUERY "VSET2?"     // Query set voltage for channel 2
#define CMD_VOUT1_QUERY "VOUT1?"     // Query output voltage for channel 1
#define CMD_VOUT2_QUERY "VOUT2?"     // Query output voltage for channel 2

// Set Current Commands
#define CMD_ISET1       "ISET1:"     // Set current for channel 1
#define CMD_ISET2       "ISET2:"     // Set current for channel 2

// Query Current Commands (getter commands)
#define CMD_ISET1_QUERY "ISET1?"     // Query set current for channel 1
#define CMD_ISET2_QUERY "ISET2?"     // Query set current for channel 2
#define CMD_IOUT1_QUERY "IOUT1?"     // Query output current for channel 1
#define CMD_IOUT2_QUERY "IOUT2?"     // Query output current for channel 2

// Enable Output Commands
#define CMD_OUTPUT1_ON  "OUT:ON"   // Turn on output for channel 1
#define CMD_OUTPUT2_ON  "OUT2:ON"   // Turn on output for channel 2
#define CMD_OUTPUT1_OFF "OUT1:OFF"  // Turn off output for channel 1
#define CMD_OUTPUT2_OFF "OUT2:OFF"  // Turn off output for channel 2

// Query Output Status Commands
#define CMD_OUTPUT1_STATUS "OUT1?"  // Query output status for channel 1 (ON/OFF)
#define CMD_OUTPUT2_STATUS "OUT2?"  // Query output status for channel 2 (ON/OFF)

// Other Commands
#define CMD_IDN         "*IDN?"     // Query the device identification

#endif // COMMAND_KD3305P_H
