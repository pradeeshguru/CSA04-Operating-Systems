#include <windows.h>
#include <iostream>
#include <string>

int main() {
    HANDLE hPipe;
    LPCTSTR pipeName = TEXT("\\\\.\\pipe\\MyPipe");

    // Try to open a named pipe
    hPipe = CreateFile(
        pipeName,   // pipe name
        GENERIC_WRITE,  // write access
        0,              // no sharing
        NULL,           // default security attributes
        OPEN_EXISTING,  // opens existing pipe
        0,              // default attributes
        NULL);          // no template file

    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to connect to pipe." << std::endl;
        return 1;
    }

    std::string message;
    std::cout << "Enter a message to send: ";
    std::getline(std::cin, message);

    // Write to the pipe
    DWORD bytesWritten;
    if (!WriteFile(hPipe, message.c_str(), message.size() + 1, &bytesWritten, NULL)) {
        std::cerr << "Failed to write to pipe." << std::endl;
        CloseHandle(hPipe);
        return 1;
    }

    std::cout << "Message sent: " << message << std::endl;

    CloseHandle(hPipe);
    return 0;
}
#include <windows.h>
#include <iostream>

int main() {
    HANDLE hPipe;
    LPCTSTR pipeName = TEXT("\\\\.\\pipe\\MyPipe");

    // Create a named pipe
    hPipe = CreateNamedPipe(
        pipeName,               // pipe name
        PIPE_ACCESS_INBOUND,    // read access
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, // message type pipe, message-read mode, blocking mode
        PIPE_UNLIMITED_INSTANCES, // max instances
        512,                    // output buffer size
        512,                    // input buffer size
        0,                      // client time-out
        NULL);                  // default security attributes

    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create pipe." << std::endl;
        return 1;
    }

    std::cout << "Waiting for client to connect..." << std::endl;

    // Wait for the client to connect
    if (!ConnectNamedPipe(hPipe, NULL)) {
        std::cerr << "Failed to connect to client." << std::endl;
        CloseHandle(hPipe);
        return 1;
    }

    char buffer[512];
    DWORD bytesRead;
    if (!ReadFile(hPipe, buffer, sizeof(buffer), &bytesRead, NULL)) {
        std::cerr << "Failed to read from pipe." << std::endl;
        CloseHandle(hPipe);
        return 1;
    }

    std::cout << "Message received: " << buffer << std::endl;

    CloseHandle(hPipe);
    return 0;
}

