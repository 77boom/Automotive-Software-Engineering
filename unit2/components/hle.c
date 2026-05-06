/**
 * This file contains the main interop layer
 * for targeting the virtual ECU through HLE
 **/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdarg.h>
#include "hle.h"
#include "init.h"
#include "irq.h"
#include "xpc56el.h"
#include "stdarg.h"

#ifndef _WIN32
volatile pthread_t worker_thread;
volatile int worker_thread_id = 0;
#endif

volatile bool is_thread_ready = false;
volatile bool is_paused = false;
#define MESSAGE_BUFFER_LEN 512
char *message_buffer = 0;
volatile int message_buffer_index = 0;

FILE* logfile = NULL;

#define LOG_MSG(fmt, ...) // logging disabled
/*#define LOG_MSG(fmt, ...) if (logfile == NULL) { init_log(); } \
                          fprintf(logfile, fmt, ##__VA_ARGS__); \
                          fprintf(logfile, "\n"); \
                          fflush(logfile);*/

void init_log()
{
    logfile = fopen("hle.log", "a");
}

/*
void print_to_file(char *fmt, ...)
{
    FILE *file = fopen("hle_log.txt", "a");
    va_list args;
    va_start(args, fmt);
    fprintf(file, fmt, args);
    va_end(args);
    fprintf(file, "\n");
    fflush(file);
    fclose(file);
}*/

void dbgprintf(const char *fmt, ...)
{
    while (message_buffer_index != 0)
        ;
    va_list args;
    va_start(args, fmt);
    message_buffer_index = snprintf(message_buffer, MESSAGE_BUFFER_LEN, fmt, args);
    va_end(args);
}

#ifndef _WIN32
void usr1_pause(int sig)
{
    if (sig == SIGUSR1)
    {
        sigset_t set;
        int s;

        sigemptyset(&set);
        sigaddset(&set, SIGUSR2);

        int awaited_sig;
        s = sigwait(&set, &awaited_sig);
        LOG_MSG("SIGUSR2 -> thread continues");
        /*if (s != 0)
            LOG_MSG("sigwait failed: %d", s);*/

        //LOG_MSG("Received %d in thread %d\n", awaited_sig, gettid());
    }
}
#endif

void init()
{
    LOG_MSG("init");
#ifndef _WIN32
    if (is_thread_ready)
        return;
    struct sigaction act;

    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = usr1_pause;

    if (sigaction(SIGUSR1, &act, NULL) == -1)
    {
        LOG_MSG("unable to install handler for SIGUSR1\n");
    }

    /* Block SIGUSR2 so that the working thread can wait for it */
    sigset_t set;
    int s;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR2);
    s = pthread_sigmask(SIG_BLOCK, &set, NULL);

    if (s != 0)
    {
        LOG_MSG("pthread_sigmask failed %d", s);
    }

    is_thread_ready = true;
    LOG_MSG("is_thread_ready = %d", is_thread_ready);
#endif
}

vinterop void read_message_buffer(char *target, int *length)
{
    LOG_MSG("read_message_buffer");

    /*length = message_buffer_index;
    memcpy(target, message_buffer, message_buffer_index);
    message_buffer_index = 0;*/
}

uint64_t spawn_thread(void function(void *))
{
    LOG_MSG("spawn_thread");

#ifdef _WIN32
    return _beginthread(function, 0, NULL);
#else
    pthread_create((pthread_t*) &worker_thread, NULL, (void * (*)(void *)) function, NULL);
    return (uint64_t)worker_thread;
#endif
}

vinterop void pause_thread(uint64_t thread_handle)
{
    LOG_MSG("pause_thread");
#ifdef _WIN32
    SuspendThread((HANDLE)thread_handle);
#else
    pthread_kill(worker_thread, SIGUSR1);

#endif
}

vinterop void continue_thread(uint64_t thread_handle)
{
    LOG_MSG("continue_thread");
#ifdef _WIN32
    ResumeThread((HANDLE)thread_handle);
#else
    pthread_kill(worker_thread, SIGUSR2);
#endif
}

vinterop void terminate_thread(uint64_t thread_handle, uint32_t exit_code)
{
    LOG_MSG("terminate_thread");
#ifdef _WIN32
    TerminateThread((HANDLE)thread_handle, exit_code);
#else
    pthread_kill(worker_thread, SIGKILL);
    worker_thread = 0;
#endif
}

void main_entry(void *pParams)
{
    LOG_MSG("main_entry");

    main();
    // TODO: handle end of main?

    LOG_MSG("main function ended");
}

vinterop uint64_t bootstrap_main(char *out_interface_version, uint8_t len)
{
    if (len < strlen(HLE_INTERFACE_VERSION))
    {
        return 0;
    }
    LOG_MSG("bootstrap_main");

    init();

    memcpy(out_interface_version, HLE_INTERFACE_VERSION, strlen(HLE_INTERFACE_VERSION)); // copy without null termination
    message_buffer = calloc(512, 1);
    message_buffer_index = 0;

    return spawn_thread(main_entry);
}

vinterop void v_read(VRegisters *vreg)
{
    LOG_MSG("v_read");

    memcpy(vreg, &VREG, sizeof(VRegisters));
}

vinterop void irq_trig(uint8_t type)
{
    LOG_MSG("irq_trig");

    switch (type)
    {
    case IRQ_PIT_CH0:
        if (IRQ.pit_ch0)
            IRQ.pit_ch0();
        break;
    case IRQ_PIT_CH1:
        if (IRQ.pit_ch1)
            IRQ.pit_ch1();
        break;
    case IRQ_PIT_CH2:
        if (IRQ.pit_ch2)
            IRQ.pit_ch2();
        break;
    case IRQ_PIT_CH3:
        if (IRQ.pit_ch2)
            IRQ.pit_ch3();
        break;
    case IRQ_CAN_RX:
        IRQ.can_rcv();
        break;
    }
}

vinterop void v_write(VRegisters *vreg)
{
    LOG_MSG("v_write");

    memcpy(&VREG, vreg, sizeof(VRegisters));
}
