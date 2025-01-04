#include "library.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MIN_CHANNELS 1
#define MAX_CHANNELS 2
#define SUCCESS 0;
#define FAILED -1;

// Global machine configuration
static device_config_t global_machine_config;

static int set_command_with_value(const char* command, double value, char* buffer, size_t buffer_size, int precision);
static int set_command_with_channel_and_value(const char* command, int channel, int value, char* buffer, size_t size, int v_precision);
static int send_query_command(const char* command, char* buffer, size_t buffer_size);

typedef enum
{
    ERROR_NULL_POINTER = -1001,
    ERROR_INVALID_CHANNELS = -1002,
    ERROR_INVALID_V_PRECISION = -1003,
    ERROR_INVALID_I_PRECISION = -1004
} internal_error_code_t;

int set_device_config(const device_config_t* config)
{
    if (config == NULL)
    {
        errno = ERROR_NULL_POINTER;
        return FAILED;
    }
    if (config->channels < MIN_CHANNELS || config->channels > MAX_CHANNELS)
    {
        errno = ERROR_INVALID_CHANNELS;
        return FAILED;
    }
    if (config->V_precision <= 0)
    {
        errno = ERROR_INVALID_V_PRECISION;
        return FAILED;
    }
    if (config->I_precision <= 0)
    {
        errno = ERROR_INVALID_I_PRECISION;
        return FAILED;
    }
    // If no error, set the global machine_config variable
    global_machine_config.protocol = config->protocol;
    global_machine_config.channels = config->channels;
    global_machine_config.V_precision = config->V_precision;
    global_machine_config.I_precision = config->I_precision;

    return SUCCESS;
}

const device_config_t* get_device_config(void)
{
    return &global_machine_config;
}

int set_voltage_command(const int channel, const int voltage, char* buffer, const size_t buffer_size)
{
    return set_command_with_channel_and_value("VSET", channel, voltage, buffer, buffer_size, global_machine_config.V_precision);
}

int set_current_command(int channel, int current, char* buffer, const size_t buffer_size)
{
    return set_command_with_channel_and_value("ISET", channel, current, buffer, buffer_size, global_machine_config.I_precision);
}




//=================================================================================
//                                  static functions
//=================================================================================

static int set_command_with_value(const char* command, const double value, char* buffer,
                                   size_t buffer_size, const int precision)
{
    if (command == NULL || buffer == NULL)
    {
        errno = ERROR_NULL_POINTER;
        return FAILED;
    }

    // Format the command with the decimal value
    char format[20];
    snprintf(format, sizeof(format), "%%s%%.%df\r", precision);
    snprintf(buffer, sizeof(buffer), format, command, value);
    return SUCCESS;
}
static int set_command_with_channel_and_value(const char* command, const int channel, const int value, char* buffer,
                                       size_t size, int v_precision)
{
    if (command == NULL || buffer == NULL)
    {
        errno = ERROR_NULL_POINTER;
        return FAILED;
    }

    if (channel > global_machine_config.channels)
    {
        errno = ERROR_INVALID_CHANNELS;
        return FAILED;
    }

    // Format the command with the decimal value
    char format[30];
    snprintf(format, sizeof(format), "%%s%%d:%%.%df\r", precision);
    snprintf(buffer, sizeof(buffer), format, command, channel, value);
    return SUCCESS;
}

static int send_query_command(const char* command, char* buffer, size_t buffer_size)
{
    if (command == NULL || buffer == NULL)
    {
        errno = ERROR_NULL_POINTER;
        return FAILED;
    }

    // Send the query command (e.g., VSET1?)
    snprintf(buffer, buffer_size, "%s\r", command);
    return SUCCESS; // Command successfully formatted
}

