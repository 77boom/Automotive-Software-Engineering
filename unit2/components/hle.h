
#ifndef HLE_H
#define HLE_H

#define HLE_INTERFACE_VERSION "AD9ABE01-6C17-478C-8106-6F9D48E4B345"

#ifdef _WIN32
    #include <processthreadsapi.h>
    #include <process.h>

    #define vinterop extern __declspec(dllexport)
#else
    #include <unistd.h>
    #include <pthread.h>
    #include <signal.h>

    #define vinterop extern
#endif // WINDOWS

#endif // HLE_H
