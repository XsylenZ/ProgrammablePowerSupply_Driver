#ifndef POWER_SUPPLY_LIBRARY_H
#define POWER_SUPPLY_LIBRARY_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

// Supported protocols
typedef enum
{
    PSL_PROTOCOL_KA3000V2,
    PSL_PROTOCOL_KD3300V4
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
int psl_set_device_config(const device_config_t* config);
const device_config_t* psl_get_device_config(void);

const char* psl_get_command(void);

int psl_set_voltage_command(int channel, double voltage);
int psl_set_current_command(int channel, double current);

int psl_set_all_output_command(int state);
int psl_set_single_output_command(int channel, int state);


#ifdef __cplusplus
}
#endif

#endif //POWER_SUPPLY_LIBRARY_H
