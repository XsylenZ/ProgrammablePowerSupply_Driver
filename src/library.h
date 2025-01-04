#ifndef PROGRAMMABLE_POWER_SUPPLY_LIBRARY_H
#define PROGRAMMABLE_POWER_SUPPLY_LIBRARY_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

// Supported protocols
typedef enum
{
    PROTOCOL_KA3000V2,
    PROTOCOL_KD3300V4
} protocol_type_t;

// Structure for machine configuration
typedef struct
{
    protocol_type_t protocol; // Protocol type
    int channels; // Number of channels (1 for single-channel, >1 for multi-channel)
    int V_precision; // Number of digits after the decimal point (voltage)
    int I_precision; // Number of digits after the decimal point (current)
} device_config_t;

// Functions to manage global machine configuration
int set_device_config(const device_config_t* config);
const device_config_t* get_device_config(void);

int set_voltage_command(int channel, int voltage, char* buffer, size_t buffer_size);
int set_current_command(int channel, int current, char* buffer, size_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif //PROGRAMMABLE_POWER_SUPPLY_LIBRARY_H
