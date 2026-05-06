
#ifndef HLE_H
#define HLE_H

#define HLE_INTERFACE_VERSION "CB63A754-0EB2-4ABB-999F-082BAA16180B"

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
