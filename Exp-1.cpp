#include <windows.h>
#include <stdio.h>

void create_process() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char commandLine[] = "C:\\Windows\\System32\\notepad.exe";  // Example executable path

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Create a new process
    if (!CreateProcess(NULL,    // No module name (use command line)
                       commandLine,    // Command line
                       NULL,           // Process handle not inheritable
                       NULL,           // Thread handle not inheritable
                       FALSE,          // Set handle inheritance to FALSE
                       0,              // No creation flags
                       NULL,           // Use parent's environment block
                       NULL,           // Use parent's starting directory 
                       &si,            // Pointer to STARTUPINFO structure
                       &pi)            // Pointer to PROCESS_INFORMATION structure
       ) 
    {
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return;
    }

    // Print parent and child PIDs
    printf("Parent process ID: %lu\n", GetCurrentProcessId());
    printf("Child process ID: %lu\n", pi.dwProcessId);

    // Wait until child process exits
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

int main() {
    create_process();
    return 0;
}

