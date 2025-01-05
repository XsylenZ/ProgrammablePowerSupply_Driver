#include "power_supply_library.h"
#include "internal/command_ka3000v2.h"
#include "internal/command_kd3300v4.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define PSL_MIN_CHANNELS (1)
#define PSL_MAX_CHANNELS (2)
#define PSL_SUCCESS (0)
#define PSL_FAILED (-1)
#define PSL_BUFFER_SIZE (30)

// Global machine configuration
static device_config_t global_device_config;
static char global_buffer[PSL_BUFFER_SIZE];

static int set_command_with_int(const char* command, int value);
static int set_command_with_channel_and_int(const char* command, int channel, int value);
static int set_command_with_double(const char* command, double value, int precision);
static int set_command_with_channel_and_double(const char* command, int channel, double value, int precision);
static int set_query_command(const char* command);
static int set_query_command_with_channel(const char* command, int channel);

typedef enum
{
    ERROR_NULL_POINTER = -1001,
    ERROR_INVALID_CHANNELS = -1002,
    ERROR_INVALID_V_PRECISION = -1003,
    ERROR_INVALID_I_PRECISION = -1004
} internal_error_code_t;

int psl_set_device_config(const device_config_t* config)
{
    if (config == NULL)
    {
        errno = ERROR_NULL_POINTER;
        return PSL_FAILED;
    }
    if (config->channels < PSL_MIN_CHANNELS || config->channels > PSL_MAX_CHANNELS)
    {
        errno = ERROR_INVALID_CHANNELS;
        return PSL_FAILED;
    }
    if (config->V_precision <= 0)
    {
        errno = ERROR_INVALID_V_PRECISION;
        return PSL_FAILED;
    }
    if (config->I_precision <= 0)
    {
        errno = ERROR_INVALID_I_PRECISION;
        return PSL_FAILED;
    }
    // If no error, set the global machine_config variable
    global_device_config.protocol = config->protocol;
    global_device_config.channels = config->channels;
    global_device_config.V_precision = config->V_precision;
    global_device_config.I_precision = config->I_precision;

    return PSL_SUCCESS;
}

const device_config_t* psl_get_device_config(void)
{
    return &global_device_config;
}

const char* psl_get_command(void)
{
    return global_buffer;
}

int psl_set_voltage_command(const int channel, const double voltage)
{
    return set_command_with_channel_and_double(CMD_VSET, channel, voltage, global_device_config.V_precision);
}

int psl_set_current_command(int channel, double current)
{
    return set_command_with_channel_and_double(CMD_ISET, channel, current, global_device_config.I_precision);
}

int psl_set_all_output_command(const int state)
{
    int result = PSL_FAILED;
    switch (global_device_config.protocol)
    {
        case PSL_PROTOCOL_KA3000V2:
            result = set_command_with_int(CMD_OUTPUT, state);
            break;
        case PSL_PROTOCOL_KD3300V4:
            result = set_command_with_channel_and_int(CMD_OUTPUT, 12, state);
            break;
    }
    return result;
}

int psl_set_single_output_command(const int channel, const int state)
{
    int result = PSL_FAILED;
    switch (global_device_config.protocol)
    {
        case PSL_PROTOCOL_KA3000V2:
            /* This command is not available for KA3000v2 series */
        break;
        case PSL_PROTOCOL_KD3300V4:
            result = set_command_with_channel_and_int(CMD_OUTPUT, channel, state);
        break;
    }
    return result;
}

//=================================================================================
//                                  static functions
//=================================================================================

static int set_command_with_int(const char* command, const int value)
{
    snprintf(global_buffer, sizeof(global_buffer), "%s%d\r", command, value);
    return PSL_SUCCESS;
}

static int set_command_with_channel_and_int(const char* command, const int channel, const int value)
{
    if (channel > global_device_config.channels)
    {
        errno = ERROR_INVALID_CHANNELS;
        return PSL_FAILED;
    }

    char format[PSL_BUFFER_SIZE];
    snprintf(format, sizeof(format), "%s%d:", command, channel);
    return set_command_with_int(format, value);
}

static int set_command_with_double(const char* command, const double value, const int precision)
{
    char format[PSL_BUFFER_SIZE];
    snprintf(format, sizeof(format), "%%s%%.%df\r", precision);
    snprintf(global_buffer, sizeof(global_buffer), format, command, value);
    return PSL_SUCCESS;
}

static int set_command_with_channel_and_double(const char* command, const int channel, const double value, const int precision)
{
    if (channel > global_device_config.channels)
    {
        errno = ERROR_INVALID_CHANNELS;
        return PSL_FAILED;
    }

    char format[PSL_BUFFER_SIZE];
    snprintf(format, sizeof(format), "%s%d:", command, channel);
    return set_command_with_double(format, value, precision);
}

static int set_query_command(const char* command)
{
    // Send the query command (e.g., STATUS?)
    snprintf(global_buffer, sizeof(global_buffer), "%s?\r", command);
    return PSL_SUCCESS;
}

static int set_query_command_with_channel(const char* command, const int channel)
{
    char format[PSL_BUFFER_SIZE];
    snprintf(format, sizeof(format), "%s%d", command, channel);
    return set_query_command(format);
}

