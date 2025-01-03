#ifndef PROGRAMMABLE_POWER_SUPPLY_LIBRARY_H
#define PROGRAMMABLE_POWER_SUPPLY_LIBRARY_H

#include <stdio.h>

/// Function to send a command to the device buffer
/// @param command
/// @param value
/// @param buffer
/// @param buffer_size
/// @return
int send_command_with_value(char *command, const float value, char *buffer, size_t buffer_size);

/// Function to send a query command to the device buffer
/// @param command
/// @param buffer
/// @param buffer_size
/// @return
int send_query_command(char *command, char *buffer, size_t buffer_size);

#endif //PROGRAMMABLE_POWER_SUPPLY_LIBRARY_H
