#include "library.h"

#include <stdlib.h>
#include <string.h>

int send_command_with_value(char *command, const float value, char *buffer, size_t buffer_size)
{
    if (command == NULL || buffer == NULL)
    {
        fprintf(stderr, "Invalid command or buffer.\n");
        return -1;
    }

    // Format the command with the decimal value
    //TODO: test with how many digits this will work on the KA3305P
    snprintf(buffer, buffer_size, "%s%.3f\r", command, value);
    return 0;
}

int send_query_command(char *command, char *buffer, size_t buffer_size)
{
    if (command == NULL || buffer == NULL)
    {
        fprintf(stderr, "Invalid command or buffer.\n");
        return -1;
    }

    // Send the query command (e.g., VSET1?)
    snprintf(buffer, buffer_size, "%s\r", command);
    return 0;  // Command successfully formatted
}

