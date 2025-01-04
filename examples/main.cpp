#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include "../src/library.h"
#include "../src/internal/command_ka3000v2.h"

// Function to configure the serial port
// Function to configure the serial port
int configure_serial_port(int fd) {
    struct termios options;

    // Get current serial port settings
    if (tcgetattr(fd, &options) < 0) {
        perror("tcgetattr failed");
        return -1;
    }

    // Set baud rate
    cfsetispeed(&options, B115200);  // Input baud rate (replace with your baud rate)
    cfsetospeed(&options, B115200);  // Output baud rate (replace with your baud rate)

    // Set 8 data bits, no parity, 1 stop bit
    options.c_cflag &= ~PARENB;   // No parity
    options.c_cflag &= ~CSTOPB;   // 1 stop bit
    options.c_cflag &= ~CSIZE;    // Clear size bits
    options.c_cflag |= CS8;       // 8 data bits

    // Enable receiver, disable modem control, and set local mode
    options.c_cflag |= (CLOCAL | CREAD);

    // Set raw input/output mode
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);  // Disable canonical mode, echo, etc.
    options.c_iflag &= ~(IXON | IXOFF | IXANY);  // Disable software flow control
    options.c_oflag &= ~OPOST;  // Disable output processing

    // Apply the settings
    if (tcsetattr(fd, TCSANOW, &options) < 0) {
        perror("tcsetattr failed");
        return -1;
    }

    return 0;
}

// Function to send data to the serial port
int send_command(int fd, const char* command) {
    fd_set writefds;
    struct timeval timeout;
    int n;

    // Set up the file descriptor set
    FD_ZERO(&writefds);
    FD_SET(fd, &writefds);

    // Set the timeout for select (e.g., 2 seconds)
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    // Use select to check if the file descriptor is ready for writing
    int ret = select(fd + 1, NULL, &writefds, NULL, &timeout);
    if (ret == -1) {
        perror("select");
        return -1;
    } if (ret == 0) {
        std::cerr << "Select timed out, device is not ready to write." << std::endl;
        return -1;
    }

    // Write to the serial port
    n = write(fd, command, strlen(command));
    if (n < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            std::cerr << "Resource temporarily unavailable. Retrying..." << std::endl;
        } else {
            perror("write");
            return -1;
        }
    }

    return 0;  // Command sent successfully
}

std::string read_response(int fd) {
    char buffer[256];  // Temporary buffer for each read
    std::string response;  // Accumulate the full response here
    fd_set readfds;
    struct timeval timeout;

    // Set the timeout (e.g., 5 seconds)
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    while (true) {
        // Set up the file descriptor set
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);

        // Use select to check if the file descriptor is ready for reading
        int ret = select(fd + 1, &readfds, NULL, NULL, &timeout);
        if (ret == -1) {
            perror("select failed");
            break;  // Exit on error
        }
        if (ret == 0) {
            std::cerr << "Select timed out, no more data to read." << std::endl;
            break;  // Exit on timeout
        }

        // If the file descriptor is ready, read the data
        if (FD_ISSET(fd, &readfds)) {
            int bytes_read = read(fd, buffer, sizeof(buffer) - 1);  // Leave space for null terminator
            if (bytes_read > 0) {
                buffer[bytes_read] = '\0';  // Null-terminate the string
                response.append(buffer, bytes_read);  // Append to the full response

                // Check for completion (e.g., newline terminator)
                if (response.find('\n') != std::string::npos) {
                    break;  // Exit if the full response is received
                }
            } else if (bytes_read == 0) {
                std::cerr << "No more data to read." << std::endl;
                break;  // Exit if no data is read
            } else {
                perror("read failed");
                break;  // Exit on read error
            }
        }
    }

    return response;  // Return the accumulated response
}

int main() {
    const size_t command_size = 256;
    // char command[command_size];

    const char* serial_port = "/dev/tty.usbmodem00272313024C1";  // Update with your port

    // Open the serial port
    int fd = open(serial_port, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        perror("Failed to open serial port");
        return -1;
    }

    // Configure the serial port
    if (configure_serial_port(fd) != 0) {
        close(fd);
        return 1;
    }

    // Set a voltage on channel 1
    // float voltage = 12.34;
    // if (send_command_with_value((char *)KA3000V2_VSET1, voltage, command, command_size) == 0) {
    //     std::cout << "Formatted Voltage Command: " << command << std::endl;
    // } else {
    //     std::cerr << "Failed to format voltage command." << std::endl;
    // }

    // Query the set voltage for channel 1
    // if (send_query_command((char *)KA3000V2_IDN_QUERY, command, command_size) == 0) {
    //     std::cout << "Formatted Query Command: " << command << std::endl;
    // } else {
    //     std::cerr << "Failed to format query command." << std::endl;
    // }

    // sleep(5);

    const char* command = "VSET1:12.34\r\n";  // Set voltage on channel 1 to 5.00V

    // while (true)
    // {
    if (send_command(fd, command) != 0) {
        close(fd);
        return 1;
    }

    // Send a command to the KA3305P
    const char* query = "VSET1?\r\n";  // Set voltage on channel 1 to 5.00V

    // while (true)
    // {
        if (send_command(fd, query) != 0) {
            close(fd);
            return 1;
        }

        // Read the response
        std::string response = read_response(fd);
        if (!response.empty()) {
            std::cout << "Received response: " << response << std::endl;
            // break;
        } else {
            std::cerr << "Failed to read response." << std::endl;
        }
    // }
    // Close the serial port
    close(fd);


    return 0;
}
